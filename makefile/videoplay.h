#pragma once

#include <QWidget>
#include "IMOS.h"
namespace Ui { class VideoPlay; };

class VideoPlay : public QWidget
{
	Q_OBJECT

public:
	VideoPlay(QWidget *parent = Q_NULLPTR);
	~VideoPlay();
	void setWorkMode(int);
	char szMonitorCode[IMOS_RES_CODE_LEN];//��¼��������
public slots:
	void contextMenuRequest(QPoint pos);
signals:
	void widgetClosed(VideoPlay *);
private:
	Ui::VideoPlay *ui;
	void closeEvent(QCloseEvent *event);
	bool isTop;
	int m_workMode;//0 ʵʱ��Ƶ��1����ʷ��Ƶ 2��ʵʱ�µ���ʷ��Ƶ
};
