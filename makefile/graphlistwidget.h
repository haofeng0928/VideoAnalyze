#pragma once
#include <QWidget>
#include <QMouseEvent>
#include <QGridLayout>
#include <QPen>
#include "mycustomplot.h"
#include "IMOS.h"
namespace Ui { class GraphListWidget; };

class GraphListWidget : public QWidget
{
	Q_OBJECT

public:
	GraphListWidget(QWidget *parent = Q_NULLPTR);
	~GraphListWidget();
	QVector<MyCustomPlot *> CPs;
	MyCustomPlot* curCP;
	MyCustomPlot* lastCP;
	int curCPRows;//当前窗口的总行数
public slots:
	void resetCPs(int);//改变窗口数量
	void selectCP(MyCustomPlot *);//选择某个窗口
	void fullSlot(MyCustomPlot *);//全屏窗口
	void realTimeGraph(TreeData * pNode);//实时绘制曲线
	void updateGraph();//每秒更新曲线，定时器的槽函数
	void drawHistoryGraphSlot(QListWidgetItem *);//绘制历史曲线
protected:
	void paintEvent(QPaintEvent *event);
private:
	Ui::GraphListWidget *ui;
	QGridLayout *gridLayout;
	QPen bluePen;//选中后窗口的边框画笔
	void initCPs();
	QTimer *realTimeTimer;//每秒更新曲线所使用的定时器
	QVector<double> sequenceVector;
};
