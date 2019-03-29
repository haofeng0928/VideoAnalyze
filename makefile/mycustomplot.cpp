#include "mycustomplot.h"
#include <QDebug>

MyCustomPlot::MyCustomPlot(QObject *)
	: QCustomPlot()
{
	tickPosition.resize(tickCounts);
	connect(this->xAxis, SIGNAL(ticksRequest()), this, SLOT(generateTick()));
	this->setMouseTracking(true);
	this->setFocusPolicy(Qt::StrongFocus);
	this->setCursor(Qt::CrossCursor);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

	this->setBackground(QBrush(QColor(0x262626)));
	this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables | QCP::iSelectLegend);
	connect(this, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
	initAxis();
	this->legend->setVisible(true);
	this->legend->setSelectableParts(QCPLegend::spItems);
	this->legend->setBrush(QBrush(Qt::black));
	this->legend->setTextColor(Qt::white);
	timeText = new QCPItemText(this);
	timeText->setText(QString(""));
	timeText->setTextAlignment(Qt::AlignLeft);
	timeText->setColor(Qt::white);
	this->replot();
	this->realTimeGraph = NULL;
	this->state = 0;
	this->startSec = -1;
	this->isUpdate = true;
	this->realTimeVideoWidget = new VideoPlay(NULL);
	pNode = NULL;
	warningLevel = -1;//设置预警的界限。
}
MyCustomPlot::~MyCustomPlot()
{
	if (this->state == 1)
		this->stopDrawGraph();
	delete realTimeVideoWidget;
}
void MyCustomPlot::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		emit selecteCP(this);
		event->accept();
	}
	QCustomPlot::mousePressEvent(event);
}
void MyCustomPlot::mouseMoveEvent(QMouseEvent *event)
{
	double xCoord = this->xAxis->pixelToCoord(event->pos().x());
	timeText->setText(getTimeStrByCoord(xCoord));
	timeText->position->setPixelPoint(event->pos() + QPoint(30, 10));
	this->replot();
	QCustomPlot::mouseMoveEvent(event);
}
void MyCustomPlot::selectionChanged()
{
	for (int i = 0; i < this->graphCount(); ++i)
	{
		QCPGraph *graph = this->graph(i);
		QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
		if (item->selected() || graph->selected())
		{
			item->setSelected(true);
			graph->setSelected(true);
		}
	}
}

void MyCustomPlot::initAxis()
{
	this->xAxis->grid()->setVisible(false);
	this->yAxis->grid()->setVisible(false);
	QPen axisBasePen;
	axisBasePen.setColor(Qt::white);
	axisBasePen.setWidth(1);
	this->xAxis->setBasePen(axisBasePen);
	this->yAxis->setBasePen(axisBasePen);
	this->xAxis->setTickLabelColor(Qt::white);
	this->yAxis->setTickLabelColor(Qt::white);
	QPen tickPen;
	tickPen.setWidth(2);
	tickPen.setColor(Qt::white);
	this->xAxis->setTickPen(tickPen);
	this->yAxis->setTickPen(tickPen);
	tickPen.setWidth(1);

	this->xAxis->setSubTickCount(0);
	this->yAxis->setSubTickCount(0);

	this->xAxis->setAutoTicks(false);
	this->xAxis->setAutoTickLabels(false);
	this->yAxis->setRange(-5, 15);
	this->xAxis->setRange(0, 86399);
	this->xAxis->setRangeLower(0);
	this->axisRect()->setRangeZoom(this->xAxis->orientation());
	this->axisRect()->setRangeDrag(this->xAxis->orientation());
}
void MyCustomPlot::contextMenuRequest(QPoint pos)
{
	this->playSec = this->xAxis->pixelToCoord(pos.x());
	QMenu *menu = new QMenu(this);
	menu->setAttribute(Qt::WA_DeleteOnClose);
	if ((this->selectedGraphs().size()) > 0)
	{
		if(this->selectedGraphs().at(0) == realTimeGraph)
			menu->addAction(QStringLiteral("从此处播放视频"), this, SLOT(playVideoSlot_realTime()));
		else
		{
			menu->addAction(QStringLiteral("从此处播放视频"), this, SLOT(playVideoSlot_history()));
			menu->addAction(QStringLiteral("删除该曲线"), this, SLOT(removeHistoryGraph()));
		}
	}
	if (this->state == 1)
	{
		bool isChecked = false;
		QMenu *setWarningLevel = new QMenu(menu);
		setWarningLevel->setTitle(QStringLiteral("设置预警阈值"));
		menu->addMenu(setWarningLevel);
		for (int i = 10; i >= 1; i--)
		{
			isChecked = (warningLevel == i) ? true : false;
			QAction *action = setWarningLevel->addAction(QStringLiteral("阈值：") + QString::number(i), [this, i]() {this->warningLevel = i; });
			action->setCheckable(true);
			action->setChecked(isChecked);
		}
		isChecked = (warningLevel == -1) ? true : false;
		QAction * action = setWarningLevel->addAction(QStringLiteral("取消预警"), [this]() {this->warningLevel = -1; });
		action->setCheckable(true);
		action->setChecked(isChecked);
	}
	QMenu *divideMenu = new QMenu(menu);
	divideMenu->setTitle(QStringLiteral("分屏"));
	menu->addMenu(divideMenu);
	divideMenu->addAction(QStringLiteral("一分屏"), [this]() {emit resetCPs(1); });
	divideMenu->addAction(QStringLiteral("四分屏"), [this]() {emit resetCPs(2); });
	divideMenu->addAction(QStringLiteral("九分屏"), [this]() {emit resetCPs(3); });
	divideMenu->addAction(QStringLiteral("十六分屏"), [this]() {emit resetCPs(4); });
	divideMenu->addAction(QStringLiteral("二十五分屏"), [this]() {emit resetCPs(5); });
	if (this->state == 1)
	{
		menu->addAction(QStringLiteral("播放实时视频"), this, SLOT(realTimeVideoPlay()));
	}
	menu->addAction(QStringLiteral("全屏/退出全屏"), [this]() {emit full(this); });
	//menu->addAction(QStringLiteral("暂停/继续绘制"), this, SLOT(pauseDrawGraph()));
	if(this->state == 1)
		menu->addAction(QStringLiteral("停止绘制"), this, SLOT(stopDrawGraph()));
	menu->popup(this->mapToGlobal(pos));
}
void MyCustomPlot::videoPlayWidgetClosed(VideoPlay *videoPlayWidget)
{
	graphVideoPlayMap.remove(graphVideoPlayMap.key(videoPlayWidget));
}
void MyCustomPlot::removeHistoryGraph()
{
	QCPGraph *graph = selectedGraphs().at(0);
	int colorNum = graph->pen().color().hslHue() / 36;
	colorSet.remove(colorNum);
	this->removeGraph(graph);
	delete map.value(graph);
	map.remove(graph);
	if (map.size() == 0)
	{
		pNode = NULL;
	}
	QMapIterator<QCPGraph*, VideoPlay*> iter(graphVideoPlayMap);
	while (iter.hasNext()) {
		iter.next();
		if (iter.key() == graph)
		{
			delete iter.value();
			return;
		}
	}

	this->replot();
}
void MyCustomPlot::realTimeVideoPlay()
{
	this->realTimeVideoWidget->show();
}
void MyCustomPlot::playVideoSlot_history()
{
	QCPGraph *graph = selectedGraphs().at(0);
	GraphData *graphData = map.value(graph);


	QMapIterator<QCPGraph*, VideoPlay*> iter(graphVideoPlayMap);
	while (iter.hasNext()) {
		iter.next();
		if (iter.key() == graph)
		{
			QDateTime timeToPlay(map.value(graph)->start.date(), QTime::fromMSecsSinceStartOfDay(this->playSec * 1000));
			string dateTimeString = timeToPlay.toString("yyyy-MM-dd hh:mm:ss").toStdString();
			IMOS_SetPlayedTime(&g_stLoginInfo.stUserLoginIDInfo, iter.value()->szMonitorCode, dateTimeString.c_str());
			return;
		}
	}

	VideoPlay *videoPlayWidget = new VideoPlay();
	videoPlayWidget->setWindowTitle(pNode->text);
	connect(videoPlayWidget, SIGNAL(widgetClosed(VideoPlay *)), this, SLOT(videoPlayWidgetClosed(VideoPlay *)));
	videoPlayWidget->resize(640, 360);
	videoPlayWidget->show();
	videoPlayWidget->setWorkMode(1);

	ULONG ulRet = ERR_COMMON_SUCCEED;
	REC_QUERY_INFO_S stRecQueryInfo = { 0 };
	QUERY_PAGE_INFO_S stQueryPageInfo = { 0 };
	RSP_PAGE_INFO_S stRspPageInfo = { 0 };
	ULONG ulBeginNum = 0;
	ULONG ulTotalNum = 0;
	int iItemIndex = 0;

	QString startDateStr = graphData->start.toString("yyyy-MM-dd hh:mm:ss");
	QString endDateStr = graphData->end.toString("yyyy-MM-dd hh:mm:ss");

	sprintf(stRecQueryInfo.stQueryTimeSlice.szBeginTime, "%s", startDateStr.toStdString().c_str());
	sprintf(stRecQueryInfo.stQueryTimeSlice.szEndTime, "%s", endDateStr.toStdString().c_str());
	strncpy(stRecQueryInfo.szCamCode, pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);
	//分配查询结果内存，每次查DEMO_QUERY_PAGE_NUM条
	RECORD_FILE_INFO_S *pstRecordList = (RECORD_FILE_INFO_S *)malloc(DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));
	if (NULL == pstRecordList)
	{
		return;
	}
	memset(pstRecordList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));

	GET_URL_INFO_S stGetUrlInfo = { 0 };
	URL_INFO_S stUrlInfo = { 0 };
	do
	{
		stQueryPageInfo.ulPageFirstRowNumber = ulBeginNum;
		stQueryPageInfo.ulPageRowNum = DEMO_QUERY_PAGE_NUM;

		/* 调用SDK接口进行录像检索，分页查询 */
		ulRet = IMOS_RecordRetrieval(&g_stLoginInfo.stUserLoginIDInfo,
			&stRecQueryInfo,
			&stQueryPageInfo,
			&stRspPageInfo,
			pstRecordList);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			free(pstRecordList);
			return;
		}
		for (ULONG i = 0; i < stRspPageInfo.ulRowNum; i++)
		{
			strncpy(stGetUrlInfo.szCamCode, stRecQueryInfo.szCamCode, IMOS_RES_CODE_LEN);
			strncpy(stGetUrlInfo.stRecTimeSlice.szBeginTime, pstRecordList[i].szStartTime, IMOS_TIME_LEN);
			strncpy(stGetUrlInfo.stRecTimeSlice.szEndTime, pstRecordList[i].szEndTime, IMOS_TIME_LEN);
			strncpy(stGetUrlInfo.szFileName, pstRecordList[i].szFileName, IMOS_FILE_NAME_LEN);
			strncpy(stGetUrlInfo.szClientIp, g_stLoginInfo.stUserLoginIDInfo.szUserIpAddress, IMOS_IPADDR_LEN);
			iItemIndex++;
			qDebug() << iItemIndex << stRecQueryInfo.szCamCode << pstRecordList[i].szStartTime << pstRecordList[i].szEndTime << pstRecordList[i].szFileName;
		}
		ulTotalNum = stRspPageInfo.ulTotalRowNum;
		ulBeginNum += stRspPageInfo.ulRowNum;
		memset(pstRecordList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));
		memset(&stRspPageInfo, 0, sizeof(RSP_PAGE_INFO_S));

	} while (ulTotalNum > ulBeginNum);
	free(pstRecordList);
	/* 调用xp接口获取录像文件的URL信息 */
	ulRet = IMOS_GetRecordFileURL(&g_stLoginInfo.stUserLoginIDInfo, &stGetUrlInfo, &stUrlInfo);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		return;
	}
	/* 获得空闲通道 */
	char szXpCode[IMOS_RES_CODE_LEN] = { 0 };
	ulRet = IMOS_GetChannelCode(&g_stLoginInfo.stUserLoginIDInfo, szXpCode);
	ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, stUrlInfo.szDecoderTag);
	/* 调用xp接口打开点播回放媒体流，参数由IMOS_GetRecordFileURL的出参获得 */
	//如果stUrlInfo.szDecoderTag是"guobiao"的话,要选择UDP(XP_PROTOCOL_UDP)进行回放
	ulRet = IMOS_OpenVodStream(&g_stLoginInfo.stUserLoginIDInfo,
		szXpCode,
		stUrlInfo.szURL,
		stUrlInfo.stVodSeverIP.szServerIp,
		stUrlInfo.stVodSeverIP.usServerPort,
		g_stXPCfgInfo.enProtl);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		/* 释放未被使用的通道 */
		IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, szXpCode);
	}
	/* 设置通道解码器的厂商标识 */
	ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, stUrlInfo.szDecoderTag);
	ulRet = IMOS_SetPlayWnd(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, (HWND)videoPlayWidget->winId());
	/* 调用xp接口开始播放 */
	ulRet = IMOS_StartPlay(&g_stLoginInfo.stUserLoginIDInfo, szXpCode);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		/* 释放未被使用的通道 */
		IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, szXpCode);
		return;
	}
	IMOS_SetRenderScale(&g_stLoginInfo.stUserLoginIDInfo, szXpCode, XP_RENDER_SCALE_PROPORTION);
	memcpy(videoPlayWidget->szMonitorCode, szXpCode, IMOS_RES_CODE_LEN);
	QDateTime timeToPlay(graphData->start.date(), QTime::fromMSecsSinceStartOfDay(this->playSec * 1000));
	string dateTimeString = timeToPlay.toString("yyyy-MM-dd hh:mm:ss").toStdString();
	IMOS_SetPlayedTime(&g_stLoginInfo.stUserLoginIDInfo, videoPlayWidget->szMonitorCode, dateTimeString.c_str());
	graphVideoPlayMap.insert(graph, videoPlayWidget);
}
void MyCustomPlot::playVideoSlot_realTime()
{
	QCPGraph *Graph = selectedGraphs().at(0);
}
void MyCustomPlot::generateTick()
{
	QCPRange range = this->xAxis->range();
	static int base = range.lower;
	int interval = range.size() / (tickCounts - 1);
	if (interval < 1)
		interval = 1;
	if (qAbs(base - range.lower) > interval)
		base = range.lower;
	for (int i = 0; i < tickPosition.size(); i++)
	{
		tickPosition[i] = base + interval * i;
	}

	this->xAxis->setTickVector(tickPosition);
	this->xAxis2->setTickVector(tickPosition);

	createTimeString();
	xAxis->setTickVectorLabels(tickLabelStr);
}
QString MyCustomPlot::getTimeStrByCoord(int sec)
{
	QTime tmp(0, 0, 0);
	if (86400 > sec)
	{
		if (sec < 0)
			return QString("");
		return tmp.addSecs(sec).toString("hh:mm:ss");
	}
	else
	{
		return QString("");
	}
}
void MyCustomPlot::createTimeString()
{
	tickLabelStr.clear();

	for (int i = 0; i < tickPosition.size(); i++)
	{
		tickLabelStr.append(getTimeStrByCoord(tickPosition.at(i)));
	}
}
void MyCustomPlot::stopDrawGraph()
{
	IMOS_StopMonitor(&g_stLoginInfo.stUserLoginIDInfo, szMonitorCode, 0);
	IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, szMonitorCode);
	this->removeGraph(realTimeGraph);
	realTimeGraph = NULL;
	this->replot();
	this->state = 0;
	this->startSec = -1;
	this->isUpdate = true;
	this->realTimeVideoWidget->hide();
	pNode = NULL;
}
void MyCustomPlot::pauseDrawGraph()
{
	if (this->state == 0)
	{
		return;
	}
	if (this->state == 2)
	{
		this->state = 1;
	}
	else
	{
		this->state = 2;
	}
}

void MyCustomPlot::startDrawGraph()
{
	this->state = 1;
	this->value = 0;
	this->addGraph();
	this->realTimeGraph = this->graph();
	QPen pen(this->realTimeGraph->pen());
	pen.setColor(Qt::white);
	this->realTimeGraph->setPen(pen);
	this->realTimeGraph->setName(QStringLiteral("实时"));
}
void MyCustomPlot::addDatePerSec()
{
	qDebug() << this->warningLevel;
	if (realTimeGraph == NULL)
		return;
	int curSec = ((renderTime - startRenderTime) / 1000 + startSec) % 86400;
	realTimeGraph->addData(curSec, value);
	this->isUpdate = true;
	this->replot();
}