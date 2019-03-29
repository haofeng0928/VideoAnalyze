#include "missionlistwidget.h"
#include "ui_missionlistwidget.h"
#include "selectdatedialog.h"
#include <QDebug>
MissionListWidget::MissionListWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::MissionListWidget();
	ui->setupUi(this);
	this->setWindowTitle(QStringLiteral("任务列表"));
	this->setWindowFlags(Qt::Drawer);
	updateTimer = new QTimer();
	updateTimer->setInterval(1000);
	connect(updateTimer, SIGNAL(timeout()), this, SLOT(updateItems()));
	updateTimer->start();
}
void MissionListWidget::updateItems()
{
	for (int i = 0; i < missionList.size(); i++)
	{
		if (missionList.at(i)->state == 1)
		{
			missionList.at(i)->times++;
			if (missionList.at(i)->times % 5 == 0)
			{
				if (missionList.at(i)->times_sec == missionList.at(i)->lastSec)
				{
					missionList.at(i)->missionComplete();
					continue;
				}
				else
				{
					missionList.at(i)->times_sec = missionList.at(i)->lastSec;
					missionList.at(i)->times = 0;
				}
			}
			missionList.at(i)->setProgressBar();
			missionList.at(i)->setLastTime();
		}
	}
}
MissionListWidget::~MissionListWidget()
{
	delete ui;
}
void MissionListWidget::startNewMission(TreeData * pNode)
{
	SelectDateDialog selectDateDialog(pNode, this);
	if (selectDateDialog.exec() == QDialog::Accepted)
	{
		MissionItem *missionItem = addMissionItem(pNode->text, selectDateDialog.startDate);
		missionItem->startSec = selectDateDialog.startSec;
		missionItem->wholeSec = selectDateDialog.wholeSec;
		missionItem->endSec = missionItem->startSec + missionItem->wholeSec;
		memcpy(missionItem->graphData->szResCode, pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);

		ULONG ulRet = ERR_COMMON_SUCCEED;
		/* 获得空闲通道 */
		ulRet = IMOS_GetChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);

		ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, selectDateDialog.stUrlInfo.szDecoderTag);

		/* 调用xp接口打开点播回放媒体流，参数由IMOS_GetRecordFileURL的出参获得 */
		//如果stUrlInfo.szDecoderTag是"guobiao"的话,要选择UDP(XP_PROTOCOL_UDP)进行回放
		ulRet = IMOS_OpenVodStream(&g_stLoginInfo.stUserLoginIDInfo,
			missionItem->szXpCode,
			selectDateDialog.stUrlInfo.szURL,
			selectDateDialog.stUrlInfo.stVodSeverIP.szServerIp,
			selectDateDialog.stUrlInfo.stVodSeverIP.usServerPort,
			g_stXPCfgInfo.enProtl);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			qDebug() << "error in OpenVodStream";
			/* 释放未被使用的通道 */
			IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
		}

		/* 设置通道解码器的厂商标识 */
		ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, selectDateDialog.stUrlInfo.szDecoderTag);
		/*设置解码帧回调*/
		ulRet = IMOS_SetDecodeVideoDataCB(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, DecoderVideoOutput_Recall, false, (LONG_REAL)missionItem);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			qDebug() << "error in SetDecodeVideoDataCB";
			return;
		}
		/* 调用xp接口开始播放 */
		ulRet = IMOS_StartPlay(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			/* 释放未被使用的通道 */
			qDebug() << "error in StartPlay";
			IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
			return;
		}
		/* 调用xp接口设置播放速度，播放速度枚举为XP_PLAY_STATUS_E */
		ulRet = IMOS_SetPlaySpeed(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, XP_PLAY_STATUS_8_FORWARD);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			return;
		}
	}
}
MissionItem *MissionListWidget::addMissionItem(QString cameraName, QDate date)
{
	MissionItem * mission = new MissionItem();
	connect(mission, SIGNAL(stopMissionSignal(MissionItem *)), this, SLOT(removeMissionItem(MissionItem *)));
	mission->setCameraName(cameraName);
	mission->setDate(date);
	missionList.append(mission);

	QListWidgetItem *item = new QListWidgetItem();
	ui->listWidget->addItem(item);
	ui->listWidget->setItemWidget(item, mission);
	item->setSizeHint(QSize(item->sizeHint().width(), mission->rect().height()));
	this->show();
	return mission;
}
void MissionListWidget::removeMissionItem(MissionItem *item)
{
	item->stopMission();
	int index = missionList.indexOf(item);
	QListWidgetItem *listWidgetItem = ui->listWidget->takeItem(index);
	ui->listWidget->removeItemWidget(listWidgetItem);
	delete item;
	missionList.remove(index);
}
void MissionListWidget::closeEvent(QCloseEvent *event)
{
	this->hide();
}
