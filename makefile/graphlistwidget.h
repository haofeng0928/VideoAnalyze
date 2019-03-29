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
	int curCPRows;//��ǰ���ڵ�������
public slots:
	void resetCPs(int);//�ı䴰������
	void selectCP(MyCustomPlot *);//ѡ��ĳ������
	void fullSlot(MyCustomPlot *);//ȫ������
	void realTimeGraph(TreeData * pNode);//ʵʱ��������
	void updateGraph();//ÿ��������ߣ���ʱ���Ĳۺ���
	void drawHistoryGraphSlot(QListWidgetItem *);//������ʷ����
protected:
	void paintEvent(QPaintEvent *event);
private:
	Ui::GraphListWidget *ui;
	QGridLayout *gridLayout;
	QPen bluePen;//ѡ�к󴰿ڵı߿򻭱�
	void initCPs();
	QTimer *realTimeTimer;//ÿ�����������ʹ�õĶ�ʱ��
	QVector<double> sequenceVector;
};
