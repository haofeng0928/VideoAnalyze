#include "videoplay.h"
#include "ui_videoplay.h"
#include <QMenu>
#include <QDebug>
#include <QCloseEvent>
VideoPlay::VideoPlay(QWidget *parent)
	: QWidget(parent)
{
	ui = new Ui::VideoPlay();
	ui->setupUi(this);
	this->setWindowTitle(QString());
	this->setWindowFlags(Qt::Drawer | Qt::WindowStaysOnTopHint);
	this->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
	isTop = true;
	this->m_workMode = 0;
}
void VideoPlay::contextMenuRequest(QPoint pos)
{
	QMenu *menu = new QMenu();
	menu->setAttribute(Qt::WA_DeleteOnClose);
	if (isTop)
		menu->addAction(QStringLiteral("È¡ÏûÖÃ¶¥"), [this]() {
		Qt::WindowFlags flags = this->windowFlags();
		flags &= ~Qt::WindowStaysOnTopHint;
		this->setWindowFlags(flags);
		this->show();
		isTop = false;
	});
	else
		menu->addAction(QStringLiteral("´°¿ÚÖÃ¶¥"), [this]() {
		Qt::WindowFlags flags = this->windowFlags();
		flags |= Qt::WindowStaysOnTopHint;
		this->setWindowFlags(flags);
		this->show();
		isTop = true;
	});
	menu->exec(QCursor::pos());
}
void VideoPlay::setWorkMode(int workMode)
{
	m_workMode = workMode;
}
void VideoPlay::closeEvent(QCloseEvent *event)
{
	if(m_workMode == 0)
		this->hide();
	else if (m_workMode == 1)
	{
		IMOS_StopPlay(&g_stLoginInfo.stUserLoginIDInfo, szMonitorCode);
		IMOS_FreeChannelCode(&g_stLoginInfo.stUserLoginIDInfo, szMonitorCode);
		emit widgetClosed(this);
	}
}
VideoPlay::~VideoPlay()
{
	delete ui;
}
