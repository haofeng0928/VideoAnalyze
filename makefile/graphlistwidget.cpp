#include "graphlistwidget.h"
#include "ui_graphlistwidget.h"
#include "graphdata.h"
GraphListWidget::GraphListWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::GraphListWidget();
	ui->setupUi(this);
	initCPs();
	realTimeTimer = new QTimer();
	realTimeTimer->setInterval(1000);
	connect(realTimeTimer, SIGNAL(timeout()), this, SLOT(updateGraph()));
	realTimeTimer->start();
}
void GraphListWidget::updateGraph()
{
	for each(MyCustomPlot *cp in CPs)
	{
		if (cp->startSec != -1)
		{
			cp->addDatePerSec();
		}
	}
}
void GraphListWidget::drawHistoryGraphSlot(QListWidgetItem * item)
{
	qDebug() << item->text();
	TreeData *pNode = item->data(QListWidgetItem::UserType).value<TreeData *>();
	if (curCP == NULL)//绘制窗口未被选中不进行绘制
	{
		QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("未选择绘制窗口"));
		return;
	}
	if ((curCP->pNode != pNode) && (curCP->pNode != NULL))
	{
		QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("该窗口被其他任务占用"));
		return;
	}
	curCP->pNode = pNode;
	QString dateFilePath("./data/" + item->text());
	QFile dateFile(dateFilePath);
	dateFile.open(QIODevice::ReadOnly);
	QDataStream in(&dateFile);
	GraphData * graphData = new GraphData();
	in >> *graphData;
	dateFile.close();
	//判断是否已经绘制
	QMapIterator<QCPGraph*, GraphData*> iter(curCP->map);
	while (iter.hasNext()) {
		iter.next();
		qDebug() << iter.key()->name() << dateFilePath.split(QChar('_')).last();
		if (iter.key()->name().contains(dateFilePath.split(QChar('_')).last()))
		{
			return;
		}
	}
	//绘制曲线
	curCP->addGraph();
	int colorNum = -1;
	for (int i = 0; i < 10; i++)
	{
		QSet<int>::const_iterator isExist = curCP->colorSet.find(i);
		if (isExist == curCP->colorSet.constEnd())
		{
			colorNum = i;
			break;
		}
		else
		{
			continue;
		}
	}

	QPen pen = curCP->graph()->pen();
	pen.setColor(QColor::fromHsv(36 * colorNum, 255, 255));
	curCP->colorSet.insert(colorNum);
	curCP->graph()->setPen(pen);
	pen = curCP->graph()->selectedPen();
	pen.setWidth(1);
	curCP->graph()->setSelectedPen(pen);
	curCP->graph()->setData(sequenceVector, graphData->data.mid(0, 86400));
	curCP->graph()->setName(dateFilePath.split(QChar('_')).at(1));
	curCP->xAxis->rescale();
	curCP->replot();
	curCP->map.insert(curCP->graph(), graphData);
}
void GraphListWidget::realTimeGraph(TreeData * pNode)
{
	if (curCP == NULL)//绘制窗口未被选中不进行绘制
	{
		QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("未选择绘制窗口"));
		return;
	}
	ULONG ulRet = ERR_COMMON_SUCCEED;
	/* 判断设备是否为摄像机 */
	if (IMOS_TYPE_CAMERA != pNode->m_nodeInfo.ulResType)
	{
		return;
	}
	/* 判断设备是否离线 */
	if (IMOS_DEV_STATUS_OFFLINE == pNode->m_nodeInfo.ulResStatus)
	{
		return;
	}
	//判断窗口是否可用
	if (curCP->state != 0)
	{
		curCP->stopDrawGraph();
	}
	char szXpCode[IMOS_RES_CODE_LEN] = { 0 };
	ulRet = IMOS_GetChannelCode(&pNode->m_stUseLoginInfo, szXpCode);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		return;
	}
	memcpy(curCP->szMonitorCode, szXpCode, IMOS_RES_CODE_LEN - 1);//保存摄像机编号到绘制窗口
																  //如果需要，设置码流回调等，可选

	curCP->realTimeVideoWidget->setWindowTitle(pNode->text);
	IMOS_SetPlayWnd(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, (HWND)curCP->realTimeVideoWidget->winId());
	ulRet = IMOS_SetDecodeVideoDataCB(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, DecoderVideoOutput_Real, true, (LONG_REAL)curCP);//将指定的绘制窗口传入用户参数中
																																	/* 调用SDK接口开始实时监控，操作码为0 */
	ulRet = IMOS_StartMonitor(&pNode->m_stUseLoginInfo,
		pNode->m_nodeInfo.szResCode,
		szXpCode,
		IMOS_FAVORITE_STREAM_ANY,
		0);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		//释放占用的通道
		IMOS_FreeChannelCode(&pNode->m_stUseLoginInfo, szXpCode);
		return;
	}
	curCP->pNode = pNode;
	curCP->startDrawGraph();
}
GraphListWidget::~GraphListWidget()
{
	delete ui;
	for (int i = 0; i < CPs.size(); i++)
	{
		delete CPs.at(i);
	}
	this->realTimeTimer->stop();
	delete realTimeTimer;
}
void GraphListWidget::initCPs()
{
	sequenceVector.resize(86400);
	for (int i = 0; i < 86400; i++)
	{
		sequenceVector[i] = i;
	}
	bluePen.setWidth(3);
	bluePen.setColor(Qt::blue);
	gridLayout = NULL;
	curCP = NULL;
	lastCP = NULL;
	curCPRows = 0;
	gridLayout = new QGridLayout(this);
	for (int i = 0; i < DEMO_MAX_PLAYS; i++)
	{
		MyCustomPlot *tmp = new MyCustomPlot(this);
		tmp->hide();
		connect(tmp, SIGNAL(resetCPs(int)), this, SLOT(resetCPs(int)));
		connect(tmp, SIGNAL(selecteCP(MyCustomPlot *)), this, SLOT(selectCP(MyCustomPlot *)));
		connect(tmp, SIGNAL(full(MyCustomPlot *)), this, SLOT(fullSlot(MyCustomPlot *)));
		CPs.append(tmp);
	}
	resetCPs(1);
}
void GraphListWidget::fullSlot(MyCustomPlot *cp)
{
	static bool isFull = false;
	static int lastCPRows = 0;
	if (isFull)
	{
		isFull = !isFull;
		gridLayout->removeWidget(cp);
		cp->hide();
		delete gridLayout;
		gridLayout = new QGridLayout(this);
		gridLayout->setMargin(3);
		curCPRows = lastCPRows;
		lastCPRows = 1;
		for (int i = 0; i < curCPRows * curCPRows; i++)
		{
			gridLayout->addWidget(CPs.at(i), i / curCPRows, i%curCPRows, 1, 1);
			CPs.at(i)->show();
		}
		this->update();
	}
	else
	{
		isFull = !isFull;
		for (int i = 0; i < curCPRows * curCPRows; i++)
		{
			gridLayout->removeWidget(CPs.at(i));
			CPs.at(i)->hide();
		}
		delete gridLayout;
		gridLayout = new QGridLayout(this);
		gridLayout->setMargin(3);
		lastCPRows = curCPRows;
		curCPRows = 1;
		gridLayout->addWidget(cp, 0, 0, 1, 1);
		cp->show();
		this->update();
	}
}
void GraphListWidget::selectCP(MyCustomPlot *cp)
{
	if (cp == curCP) return;
	curCP = cp;
	this->update();
}

void GraphListWidget::resetCPs(int rows)//改变窗口数量
{
	if (rows == curCPRows) return;
	if (gridLayout != NULL)
	{
		for (int i = 0; i < curCPRows * curCPRows; i++)
		{
			gridLayout->removeWidget(CPs.at(i));
			CPs.at(i)->hide();
		}
		delete gridLayout;
	}
	gridLayout = new QGridLayout(this);
	gridLayout->setMargin(3);
	for (int i = 0; i < rows * rows; i++)
	{
		gridLayout->addWidget(CPs.at(i), i / rows, i%rows, 1, 1);
		CPs.at(i)->show();
	}
	curCPRows = rows;
	this->update();
}
void GraphListWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.eraseRect(this->rect());
	if (curCP != NULL && (CPs.indexOf(curCP) < curCPRows * curCPRows))//被选择的窗口要小于显示的窗口才进行轮廓的绘制
	{
		painter.setPen(bluePen);
		painter.drawRect(curCP->pos().x() - 3, curCP->pos().y() - 3, curCP->width() + 3, curCP->height() + 3);
	}
}