#pragma once

#include <QWidget>
namespace Ui { class MissionListWidget; };
#include <QTimer>
#include <QVector>
#include "missionitem.h"
#include "IMOS.h"

class MissionListWidget : public QWidget
{
	Q_OBJECT

public:
	MissionListWidget(QWidget *parent = Q_NULLPTR);
	~MissionListWidget();
public slots:
	void startNewMission(TreeData * pNode);
	void updateItems();
	void removeMissionItem(MissionItem *item);
private:
	Ui::MissionListWidget *ui;
	void closeEvent(QCloseEvent *event);
	QVector<MissionItem *> missionList;
	QTimer *updateTimer;
	MissionItem* addMissionItem(QString CameraName, QDate date);

};
