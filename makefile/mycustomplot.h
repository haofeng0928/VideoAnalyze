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
	static const int tickCounts = 11;//�������tick����
	~MyCustomPlot();
	int state;//��ǰ���ڵ�״̬ 0:δʹ�ã�1������ʵʱ���� 2: stop״̬
	int startSec;//��¼��ʼ����ʱ��ʱ��
	DLONG startRenderTime;//��¼��ʼ��renderTimeֵ���ڻص��и���
	DLONG renderTime;//ÿ�λص����´�ֵ
	int value;//������˶�ֵ���ڻص������
	char szMonitorCode[IMOS_RES_CODE_LEN];//��¼��������
	void startDrawGraph();//��ʼ��������
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
	void playVideoSlot_realTime();//�ط�ʵʱ����ʱ��֮ǰ����Ƶ
	void playVideoSlot_history();//�ط���ʷ���߶�Ӧ����Ƶ
	void removeHistoryGraph();//�Ƴ�ѡ�е���ʷ����
	void selectionChanged();
	void generateTick();
	void addDatePerSec();//��ʱ���ص���ִ�У�ÿ�����һ������
	void stopDrawGraph();//ֹͣ���Ʋ�Ĩȥ����
	void pauseDrawGraph();//��ͣ����
	void realTimeVideoPlay();
	void videoPlayWidgetClosed(VideoPlay *);//���Ŵ��ڱ��ر�֮��Ĵ���
protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
private:
	void initAxis();
	int playSec;//������Ƶʱ�Ŀ�ʼʱ��
	QCPItemText *timeText;//������ڴ���ָʾ��ʱ��
	QString getTimeStrByCoord(int sec);
	QVector<double> tickPosition;
	void createTimeString();
	QVector<QString> tickLabelStr;
	QCPGraph *realTimeGraph;//ʵʱ����
	QMap<QCPGraph *, VideoPlay *> graphVideoPlayMap;
};
