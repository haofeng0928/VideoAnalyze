#pragma once

#include <QListWidget>

class DataListWidget : public QListWidget
{
	Q_OBJECT

public:
	DataListWidget(QWidget *parent);
	~DataListWidget();
};
