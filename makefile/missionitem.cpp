#include "missionitem.h"
#include "ui_missionitem.h"
#include <QTime>
#include <QDebug>
#include <QFile>
MissionItem::MissionItem(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::MissionItem();
	ui->setupUi(this);
	ui->progressBar->setValue(0);
	connect(ui->stopButton, &QToolButton::clicked, [this]() {	emit stopMissionSignal(this);});
	this->state = 0;
	graphData = new GraphData();
	this->lastSec = -1;
	this->lastValue = 0;
	times_sec = lastSec;
	times = 0;
}
void MissionItem::stopMission()
{
	IMOS_StopPlay(&g_stLoginInfo.stUserLoginIDInfo, this->szXpCode);
	IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, this->szXpCode);
}
void MissionItem::missionComplete()
{
	IMOS_StopPlay(&g_stLoginInfo.stUserLoginIDInfo, this->szXpCode);
	IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, this->szXpCode);
	ui->lastTimeLabel->setText(QStringLiteral("Íê³É"));
	ui->progressBar->setValue(100);
	this->state = 3;
	graphData->start.setDate(startDate);
	graphData->start.setTime(QTime(startSec / 3600, startSec / 60 % 60, startSec % 60));
	graphData->end.setDate(startDate);
	graphData->end.setTime(QTime(endSec / 3600, endSec / 60 % 60, endSec % 60));
	graphData->placeText = ui->cameraNameLabel->text();
	QString dataFileName = graphData->placeText + "_" + graphData->start.toString("yyyyMMddhhmmss") + graphData->end.toString("yyyyMMddhhmmss");
	QFile fileToStore("./data/" + dataFileName);
	fileToStore.open(QIODevice::ReadWrite);
	QDataStream out(&fileToStore);
	out << *graphData;
	fileToStore.close();
}
void MissionItem::setCameraName(QString cameraName)
{
	ui->cameraNameLabel->setText(cameraName);
}
void MissionItem::setProgressBar()
{
	int percent = (lastSec + 1) * 100 / wholeSec;
	ui->progressBar->setValue(percent);
}
void MissionItem::setLastTime()
{
	int secsLost = (wholeSec - lastSec) / 8;
	QTime time;
	time.setHMS(secsLost / 3600, secsLost / 60 % 60, secsLost % 60);
	ui->lastTimeLabel->setText(time.toString("hh:mm:ss"));
}
void MissionItem::setDate(QDate &date)
{
	ui->dateLabel->setText(date.toString("yyyy-MM-dd"));
	startDate = date;
}
void MissionItem::outPutToFile()
{

}
void MissionItem::addDate(int sec, double value)
{
	if (sec - lastSec == 1)
	{
		graphData->data[sec + startSec] = value;
	}
	else if (sec - lastSec > 1)
	{
		for (int i = 0; i < sec - lastSec; i++)
			graphData->data[lastSec + i + 1 + startSec] = lastValue;
	}
	else
		return;
	lastSec = sec;
	lastValue = value;
}
MissionItem::~MissionItem()
{
	delete ui;
}
