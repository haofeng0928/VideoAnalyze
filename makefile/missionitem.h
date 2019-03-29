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
	int state;//��ǰ�����״̬ 0:δ��ʼ��1������ 2: ��ͣ 3.�����
	DLONG startRenderTime;//��¼��ʼ��renderTimeֵ���ڵ�һ�λص��и���
	int startSec;
	int wholeSec;
	int endSec;
	Mat blackFrame;
	Mat frontFrame;
	Mat currentFrame;
	void addDate(int sec, double value);
	char szXpCode[IMOS_RES_CODE_LEN];
	int times = 0;//��¼����updateItem�����Ĵ���
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
	void stopMissionSignal(MissionItem *);//��ֹ����
private:
	Ui::MissionItem *ui;
	int lastValue;
};
