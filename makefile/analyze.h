#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_analyze.h"
#include "cameralistwidget.h"
#include "missionlistwidget.h"
#include "datalistwidget.h"
#include <QListWidget>
#include "IMOS.h"
class analyze : public QMainWindow
{
	Q_OBJECT
public:
	analyze(QWidget *parent = Q_NULLPTR);
	~analyze();
	CameraListWidget *cameraListWidget;
	DataListWidget *dataListWidget;
public slots:
	void loginSlot();
	void processWidget();
	void findHistoryGraph(TreeData *);
private:
	Ui::analyzeClass ui;
	MissionListWidget *missionListWidget;
};
