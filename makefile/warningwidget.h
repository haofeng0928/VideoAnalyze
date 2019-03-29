#pragma once

#include <QWidget>
namespace Ui { class WarningWidget; };

class WarningWidget : public QWidget
{
	Q_OBJECT

public:
	WarningWidget(int level, QString position, QWidget *parent = Q_NULLPTR);
	~WarningWidget();
	int minutes;
signals:
	void enterSignal(int);
public slots:
	void selectTime(int);
	void enterButtonSlot();
private:
	Ui::WarningWidget *ui;
};
