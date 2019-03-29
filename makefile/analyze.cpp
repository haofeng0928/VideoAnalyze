#include "analyze.h"
#include "login.h"
#include <QMessageBox>
#include "global.h"
#include "IMOS.h"
#include <QFile>
QString windowTitle_notLogin = QStringLiteral("监控分析系统 - 未登录");
QString windowTitle_login = QStringLiteral("监控分析系统 - 已登录");
analyze::analyze(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	g_graphListWidget = ui.graphListlWidget;
	this->setWindowTitle(windowTitle_notLogin);
	missionListWidget = new MissionListWidget(NULL);
	missionListWidget->hide();
	connect(ui.loginButton, SIGNAL(triggered()), this, SLOT(loginSlot()));
	connect(ui.processButton, SIGNAL(triggered()), this, SLOT(processWidget()));
	ui.tabWidget->clear();

	cameraListWidget = new CameraListWidget(NULL);
	connect(cameraListWidget, SIGNAL(realTimeGraph(TreeData *)), ui.graphListlWidget, SLOT(realTimeGraph(TreeData *)));
	connect(cameraListWidget, SIGNAL(getHistoryGraph(TreeData *)), missionListWidget, SLOT(startNewMission(TreeData *)));
	connect(cameraListWidget, SIGNAL(drawHistoryGraph(TreeData *)), this, SLOT(findHistoryGraph(TreeData *)));

	ui.tabWidget->addTab(cameraListWidget, QStringLiteral("摄像机列表"));
	dataListWidget = new DataListWidget(NULL);
	connect(dataListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)), ui.graphListlWidget, SLOT(drawHistoryGraphSlot(QListWidgetItem *)));
	ui.tabWidget->addTab(dataListWidget, QStringLiteral("历史曲线列表"));
}
void analyze::findHistoryGraph(TreeData *pNode)
{
	ui.tabWidget->setCurrentIndex(1);
	dataListWidget->clear();
	QDir dir("./data");
	QList<QFileInfo> fileinfo(dir.entryInfoList());
	for (int i = 0; i < fileinfo.count(); i++)
	{
		QString fileName = fileinfo.at(i).fileName();
		if (fileName.contains(pNode->text.split(QChar('_')).at(0)))
		{
			QListWidgetItem *item = new QListWidgetItem(fileName, dataListWidget, QListWidgetItem::UserType);
			QVariant i;
			i.setValue<TreeData *>(pNode);
			item->setData(QTreeWidgetItem::UserType, i);
		}
	}
}
void analyze::processWidget()
{
	missionListWidget->show();
}

analyze::~analyze()
{
	delete missionListWidget;
}
void analyze::loginSlot()
{
	Login loginDialog(this);
	if (loginDialog.exec() == QDialog::Rejected)
	{
		QMessageBox::warning(this, QStringLiteral("错误"), QStringLiteral("登陆失败"));
		this->setWindowTitle(windowTitle_notLogin);
	}
	else
	{
		this->setWindowTitle(windowTitle_login);
		cameraListWidget->searchCameraSlot();
	}
}