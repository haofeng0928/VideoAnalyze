#pragma once

#include <qcustomplot.h>
#include <QMouseEvent>
#include <QVector>
#include "IMOS.h"
#include "videoplay.h"
#include <opencv2/core.hpp>
#include "graphdata.h"
#include "videoplay.h"
#include <QSet>
using namespace cv;
class MyCustomPlot : public QCustomPlot
{
	Q_OBJECT

public:
	MyCustomPlot(QObject *);
	static const int tickCounts = 11;//横坐标的tick数量
	~MyCustomPlot();
	int state;//当前窗口的状态 0:未使用，1：正在实时绘制 2: stop状态
	int startSec;//记录开始绘制时的时间
	DLONG startRenderTime;//记录开始的renderTime值，在回调中更改
	DLONG renderTime;//每次回调更新此值
	int value;//计算的运动值，在回调里更新
	char szMonitorCode[IMOS_RES_CODE_LEN];//记录摄像机编号
	void startDrawGraph();//开始绘制曲线
	Mat blackFrame;
	Mat frontFrame;
	Mat currentFrame;
	bool isUpdate;
	VideoPlay *realTimeVideoWidget;
	TreeData * pNode;
	QMap<QCPGraph*, GraphData*> map;
	QSet<int> colorSet;
	int warningLevel;
signals:
	void resetCPs(int rows);
	void selecteCP(MyCustomPlot *);
	void full(MyCustomPlot *);
public slots:
	void contextMenuRequest(QPoint pos);
	void playVideoSlot_realTime();//回放实时绘制时，之前的视频
	void playVideoSlot_history();//回放历史曲线对应的视频
	void removeHistoryGraph();//移除选中的历史曲线
	void selectionChanged();
	void generateTick();
	void addDatePerSec();//定时器回调中执行，每秒更新一次曲线
	void stopDrawGraph();//停止绘制并抹去曲线
	void pauseDrawGraph();//暂停绘制
	void realTimeVideoPlay();
	void videoPlayWidgetClosed(VideoPlay *);//播放窗口被关闭之后的处理
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	void initAxis();
	int playSec;//调用视频时的开始时间
	QCPItemText *timeText;//鼠标所在处所指示的时间
	QString getTimeStrByCoord(int sec);
	QVector<double> tickPosition;
	void createTimeString();
	QVector<QString> tickLabelStr;
	QCPGraph *realTimeGraph;//实时曲线
	QMap<QCPGraph *, VideoPlay *> graphVideoPlayMap;
};
