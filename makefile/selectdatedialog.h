#pragma once

#include <QDialog>
#include <IMOS.h>
#include <QDate>
namespace Ui { class SelectDateDialog; };

class SelectDateDialog : public QDialog
{
	Q_OBJECT

public:
	SelectDateDialog(TreeData *pNode, QWidget *parent = Q_NULLPTR);
	~SelectDateDialog();
	QDate startDate;
	QDate endDate;
	int startSec;
	int wholeSec;
	URL_INFO_S stUrlInfo;
public slots:
	void searchHistoryVideo();
	void startMission();
private:
	Ui::SelectDateDialog *ui;
	TreeData *m_pNode;
	QTime startTime;
	QTime endTime;
};
