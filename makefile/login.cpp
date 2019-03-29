#include "login.h"
#include "ui_login.h"
#include <QIcon>
#include "IMOS.h"
#include <QDebug>
Login::Login(QWidget *parent)
	: QDialog(parent)
{
	ui = new Ui::Login();
	ui->setupUi(this);
	this->setWindowFlags(Qt::Drawer);
	
	ui->serverAddressLineEdit->setText(DEFAULTSERVERADDRESS);
	ui->serverPortLineEdit->setText(QString::number(DEFAULTSERVERPORT));
	ui->userNameLineEdit->setText(DEFAULTUSERNAME);
	ui->passwordLineEdit->setText(DEFAULTPASSWORD);
	connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearButtonSlot()));
	connect(ui->enterButton, SIGNAL(clicked()), this, SLOT(enterButtonSlot()));
	connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancalButtonSlot()));
}

Login::~Login()
{
	delete ui;
}
void Login::clearButtonSlot()
{
	ui->serverAddressLineEdit->clear();
	ui->serverPortLineEdit->clear();
	ui->userNameLineEdit->clear();
	ui->passwordLineEdit->clear();
}
void Login::cancalButtonSlot()
{
	this->reject();
	this->hide();
}
void Login::enterButtonSlot()
{
	serverAddress = ui->serverAddressLineEdit->text();
	serverPort = ui->serverPortLineEdit->text().toInt();
	userName = ui->userNameLineEdit->text();
	password = ui->passwordLineEdit->text();


	if (userName.isEmpty() || password.isEmpty())
	{
		this->reject();
		return;
	}
	ULONG ulRet = ERR_COMMON_FAIL;
	ulRet = IMOS_Initiate("N/A", serverPort, BOOL_TRUE, BOOL_TRUE);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		this->reject();
		return;
	}
	CHAR szPasswd[IMOS_PASSWD_ENCRYPT_LEN] = { 0 };
	ulRet = IMOS_Encrypt(password.toStdString().c_str(), (ULONG_32)strlen(password.toStdString().c_str()), szPasswd);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		this->reject();
		return;
	}
	ulRet = IMOS_SetOption(OPTION_NAME_SERVER_IMG_PORT, &serverPort, sizeof(USHORT));
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		this->reject();
		return;
	}
	//用户登陆
	CHAR  szServerAdd[IMOS_IPADDR_LEN] = { 0 };
	CHAR  szUserLoginName[IMOS_NAME_LEN] = { 0 };
	CHAR  szLoginPwd[IMOS_PASSWD_LEN] = { 0 };
	strncpy(szServerAdd, serverAddress.toStdString().c_str(), IMOS_IPADDR_LEN);
	strncpy(szUserLoginName, userName.toStdString().c_str(), IMOS_NAME_LEN);
	strncpy(szLoginPwd, password.toStdString().c_str(), IMOS_PASSWD_LEN);
	//将用户名转为UTF8
	CHAR szUserLoginNameUTF8[IMOS_NAME_LEN] = { 0 };
	ConvertUnicodeToUTF8(szUserLoginName, szUserLoginNameUTF8, IMOS_NAME_LEN);

	ulRet = IMOS_LoginEx(szUserLoginNameUTF8, szPasswd, szServerAdd, "N/A", &g_stLoginInfo);
	//ulRet = IMOS_LoginEx("test002", "e10adc3949ba59abbe56e057f20f883e", "10.10.10.1", "N/A", &g_stLoginInfo);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		this->reject();
		return;
	}
	//更新到全局
	strncpy(g_szLastUserName, szUserLoginName, IMOS_NAME_LEN - 1);
	strncpy(g_szLastPasswd, szLoginPwd, IMOS_PASSWD_ENCRYPT_LEN - 1);
	strncpy(g_szLastServerIP, szServerAdd, IMOS_IPADDR_LEN - 1);
	strncpy(g_szLastServerPort, g_szLastServerPort, IMOS_STRING_LEN_32 - 1);

	PLAY_WND_INFO_S *pstPlayWnds = (PLAY_WND_INFO_S *)malloc(DEMO_MAX_PLAYS * sizeof(PLAY_WND_INFO_S));
	if (NULL == pstPlayWnds)
	{
		this->reject();
		return;
	}
	/* 启动xp */
	ulRet = IMOS_StartPlayer(&g_stLoginInfo.stUserLoginIDInfo, DEMO_MAX_PLAYS, pstPlayWnds);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		free(pstPlayWnds);
		IMOS_LogoutEx(&g_stLoginInfo.stUserLoginIDInfo);
		this->reject();
		return;
	}
	strncpy(g_szXpCode, pstPlayWnds[DEMO_MAX_PLAYS - 1].szPlayWndCode, IMOS_RES_CODE_LEN);
	free(pstPlayWnds);
	XP_STREAM_INFO_S stXpStreamInfo;
	/* 查询默认配置 防止误修改其他默认配置 */
	IMOS_QueryXpStreamInfo(&g_stLoginInfo.stUserLoginIDInfo, &stXpStreamInfo);

	/* 将流传输方式修改为TCP （目前仅支持自适应和TCP） */
	stXpStreamInfo.ulVoiceCommMode = IMOS_STREAM_MODE_MS_AUTO;

	/* 设置参数 */
	IMOS_ConfigXpStreamInfo(&g_stLoginInfo.stUserLoginIDInfo, &stXpStreamInfo);
	/* 订阅推送功能 */
	//ulRet = IMOS_SubscribePushInfo(&g_stLoginInfo.stUserLoginIDInfo, SUBSCRIBE_PUSH_TYPE_ALL);
	//if (ERR_COMMON_SUCCEED != ulRet)
	//{
	//	IMOS_StopPlayer(&g_stLoginInfo.stUserLoginIDInfo);
	//	IMOS_LogoutEx(&g_stLoginInfo.stUserLoginIDInfo);
	//	this->reject();
	//	return;
	//}
	/* 注册推送信息处理的回调函数，包括告警 */
	//ulRet = IMOS_RegCallBackPrcFuncEx(&g_stLoginInfo.stUserLoginIDInfo, NULL);
	//qDebug() << ulRet;
	//if (ERR_COMMON_SUCCEED != ulRet)
	//{
	//	//log
	//	IMOS_StopPlayer(&g_stLoginInfo.stUserLoginIDInfo);
	//	IMOS_LogoutEx(&g_stLoginInfo.stUserLoginIDInfo);
	//	this->reject();
	//	return;
	//}
	this->accept();
	//设置系统音量,与系统相关，多次设置仅是覆盖
	//ulRet = IMOS_AdjustAllWaveAudio(&g_stLoginInfo.stUserLoginIDInfo, g_stXPCfgInfo.ulSysVolume);

	ulRet = IMOS_SetRenderMode(g_stXPCfgInfo.enRenderMode);

	ulRet = IMOS_SetPixelFormat(g_stXPCfgInfo.enPixelFormat);

	ulRet = IMOS_SetRealtimeFluency(g_stXPCfgInfo.enPictureFluency);
	this->hide();
	//IMOS_SetRunMsgCB(RunInfoCallback);
}