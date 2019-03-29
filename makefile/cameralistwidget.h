#pragma once

#include <QTreeWidget>
#include "IMOS.h"
#include <QPoint>
#include "graphlistwidget.h"
class CameraListWidget : public QTreeWidget
{
	Q_OBJECT

public:
	CameraListWidget(QWidget *parent);
	~CameraListWidget();
	TreeData *selectedCamera;
public slots:
	void searchCameraSlot();
	void itemRightButtonMenu(QTreeWidgetItem *item, int column);//QTreeWidgetItem的右键菜单
	void doubleClickedOnTreeItem(QTreeWidgetItem *tmp, int);
signals:
	void realTimeGraph(TreeData *);
	void getHistoryGraph(TreeData *);//获取历史曲线
	void drawHistoryGraph(TreeData *);
private:
	void addTopItem(TreeData *data);
	void AddSubTreeNode(unsigned long ulResType, unsigned long iconType, char* pcOrzCode, QTreeWidgetItem *parent);
	void setIconForItem(QTreeWidgetItem * tmp, TreeData *data, unsigned long ulResType);
	void addChildItem(QTreeWidgetItem *parent, TreeData *data, unsigned long ulResType = 0);
};
