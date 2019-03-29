#include "missionlistwidget.h"
#include "ui_missionlistwidget.h"
#include "selectdatedialog.h"
#include <QDebug>
MissionListWidget::MissionListWidget(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::MissionListWidget();
	ui->setupUi(this);
	this->setWindowTitle(QStringLiteral("�����б�"));
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
		/* ��ÿ���ͨ�� */
		ulRet = IMOS_GetChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);

		ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, selectDateDialog.stUrlInfo.szDecoderTag);

		/* ����xp�ӿڴ򿪵㲥�ط�ý������������IMOS_GetRecordFileURL�ĳ��λ�� */
		//���stUrlInfo.szDecoderTag��"guobiao"�Ļ�,Ҫѡ��UDP(XP_PROTOCOL_UDP)���лط�
		ulRet = IMOS_OpenVodStream(&g_stLoginInfo.stUserLoginIDInfo,
			missionItem->szXpCode,
			selectDateDialog.stUrlInfo.szURL,
			selectDateDialog.stUrlInfo.stVodSeverIP.szServerIp,
			selectDateDialog.stUrlInfo.stVodSeverIP.usServerPort,
			g_stXPCfgInfo.enProtl);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			qDebug() << "error in OpenVodStream";
			/* �ͷ�δ��ʹ�õ�ͨ�� */
			IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
		}

		/* ����ͨ���������ĳ��̱�ʶ */
		ulRet = IMOS_SetDecoderTag(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, selectDateDialog.stUrlInfo.szDecoderTag);
		/*���ý���֡�ص�*/
		ulRet = IMOS_SetDecodeVideoDataCB(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode, DecoderVideoOutput_Recall, false, (LONG_REAL)missionItem);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			qDebug() << "error in SetDecodeVideoDataCB";
			return;
		}
		/* ����xp�ӿڿ�ʼ���� */
		ulRet = IMOS_StartPlay(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			/* �ͷ�δ��ʹ�õ�ͨ�� */
			qDebug() << "error in StartPlay";
			IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, missionItem->szXpCode);
			return;
		}
		/* ����xp�ӿ����ò����ٶȣ������ٶ�ö��ΪXP_PLAY_STATUS_E */
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
