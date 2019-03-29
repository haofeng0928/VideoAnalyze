#pragma once

#include <QWidget>
#include "IMOS.h"
namespace Ui { class MissionItem; };
#include <opencv2/core.hpp>
using namespace cv;
#include <QVector>
#include <QTimer>
#include "graphdata.h"
#include <QDate>
class MissionItem : public QWidget
{
	Q_OBJECT

public:
	MissionItem(QWidget *parent = Q_NULLPTR);
	~MissionItem();
	void setCameraName(QString cameraName);
	void setProgressBar();
	void setLastTime();
	void setDate(QDate &date);
	QDate startDate;
	int state;//当前任务的状态 0:未开始，1：运行 2: 暂停 3.已完成
	DLONG startRenderTime;//记录开始的renderTime值，在第一次回调中更改
	int startSec;
	int wholeSec;
	int endSec;
	Mat blackFrame;
	Mat frontFrame;
	Mat currentFrame;
	void addDate(int sec, double value);
	char szXpCode[IMOS_RES_CODE_LEN];
	int times = 0;//记录进入updateItem函数的次数
	int times_sec;
	int lastSec;
	void stopMission();
	GraphData *graphData;
	void outPutToFile();
	ULONG_32 startAbsoluteTime;
	ULONG_32 curAbsoluteTime;
	ULONG_32 realAbsoluteTime;
public slots:
	void missionComplete();
signals:
	void stopMissionSignal(MissionItem *);//终止任务
private:
	Ui::MissionItem *ui;
	int lastValue;
};
