#include "selectdatedialog.h"
#include "ui_selectdatedialog.h"
#include <QDebug>
SelectDateDialog::SelectDateDialog(TreeData *pNode, QWidget *parent)
	: QDialog(parent), m_pNode(pNode)
{
	ui = new Ui::SelectDateDialog();
	ui->setupUi(this);
	this->setWindowTitle(QStringLiteral("选择要分析的日期"));
	this->setWindowFlags(Qt::Drawer);
	connect(ui->startDate, &QDateEdit::dateChanged, [this](const QDate &date) {
		startDate = date;
		ui->endDate->setDate(date); });
	connect(ui->endDate, &QDateEdit::dateChanged, [this](const QDate &date) {
		endDate = date;});
	connect(ui->startTimeEdit, &QTimeEdit::timeChanged, [this](const QTime &time) {
		startTime = time;});
	connect(ui->endTimeEdit, &QTimeEdit::timeChanged, [this](const QTime &time) {
		endTime = time;});
	ui->startDate->setDate(QDate::currentDate());
	ui->startTimeEdit->setTime(QTime(0, 0, 0, 1));
	ui->endTimeEdit->setTime(QTime(23, 59, 59));
	connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(searchHistoryVideo()));
	connect(ui->startButton, SIGNAL(clicked()), this, SLOT(startMission()));

	this->startSec = 0;
	this->wholeSec = 86400;
}
void SelectDateDialog::startMission()
{
	this->accept();
	this->hide();
}
void SelectDateDialog::searchHistoryVideo()
{
	if ((startDate.daysTo(endDate) < 0) || (startTime.secsTo(endTime) <= 0))
	{
		ui->statusLabel->setText(QStringLiteral("!!!!所选的时间有冲突!!!!"));
		return;
	}
	startSec = QTime(0, 0).secsTo(startTime);
	wholeSec = QTime(0, 0).secsTo(endTime) - startSec;
	qDebug() << startSec << wholeSec;
	ui->statusLabel->setText(QString());
	ULONG ulRet = ERR_COMMON_SUCCEED;
	REC_QUERY_INFO_S stRecQueryInfo = { 0 };
	QUERY_PAGE_INFO_S stQueryPageInfo = { 0 };
	RSP_PAGE_INFO_S stRspPageInfo = { 0 };
	ULONG ulBeginNum = 0;
	ULONG ulTotalNum = 0;
	int iItemIndex = 0;

	QDate startDate = ui->startDate->date();
	QDate endDate = ui->endDate->date();
	QString startDateStr = startDate.toString("yyyy-MM-dd") + startTime.toString(" hh:mm:ss");
	QString endDateStr = endDate.toString("yyyy-MM-dd") + endTime.toString(" hh:mm:ss");

	sprintf(stRecQueryInfo.stQueryTimeSlice.szBeginTime, "%s", startDateStr.toStdString().c_str());
	sprintf(stRecQueryInfo.stQueryTimeSlice.szEndTime, "%s", endDateStr.toStdString().c_str());
	strncpy(stRecQueryInfo.szCamCode, m_pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);
	//分配查询结果内存，每次查DEMO_QUERY_PAGE_NUM条
	RECORD_FILE_INFO_S *pstRecordList = (RECORD_FILE_INFO_S *)malloc(DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));
	if (NULL == pstRecordList)
	{
		ui->statusLabel->setText(QStringLiteral("历史视频文件不存在"));
		return;
	}
	memset(pstRecordList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));

	GET_URL_INFO_S stGetUrlInfo = { 0 };
	do
	{
		stQueryPageInfo.ulPageFirstRowNumber = ulBeginNum;
		stQueryPageInfo.ulPageRowNum = DEMO_QUERY_PAGE_NUM;

		/* 调用SDK接口进行录像检索，分页查询 */
		ulRet = IMOS_RecordRetrieval(&g_stLoginInfo.stUserLoginIDInfo,
			&stRecQueryInfo,
			&stQueryPageInfo,
			&stRspPageInfo,
			pstRecordList);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			free(pstRecordList);
			ui->statusLabel->setText(QStringLiteral("历史视频文件不存在"));
			return;
		}
		for (ULONG i = 0; i < stRspPageInfo.ulRowNum; i++)
		{
			strncpy(stGetUrlInfo.szCamCode, stRecQueryInfo.szCamCode, IMOS_RES_CODE_LEN);
			strncpy(stGetUrlInfo.stRecTimeSlice.szBeginTime, pstRecordList[i].szStartTime, IMOS_TIME_LEN);
			strncpy(stGetUrlInfo.stRecTimeSlice.szEndTime, pstRecordList[i].szEndTime, IMOS_TIME_LEN);
			strncpy(stGetUrlInfo.szFileName, pstRecordList[i].szFileName, IMOS_FILE_NAME_LEN);
			strncpy(stGetUrlInfo.szClientIp, g_stLoginInfo.stUserLoginIDInfo.szUserIpAddress, IMOS_IPADDR_LEN);
			iItemIndex++;
		}
		ulTotalNum = stRspPageInfo.ulTotalRowNum;
		ulBeginNum += stRspPageInfo.ulRowNum;
		memset(pstRecordList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RECORD_FILE_INFO_S));
		memset(&stRspPageInfo, 0, sizeof(RSP_PAGE_INFO_S));

	} while (ulTotalNum > ulBeginNum);
	free(pstRecordList);
	/* 调用xp接口获取录像文件的URL信息 */

	ulRet = IMOS_GetRecordFileURL(&g_stLoginInfo.stUserLoginIDInfo, &stGetUrlInfo, &stUrlInfo);
	if (ERR_COMMON_SUCCEED != ulRet)
	{
		ui->statusLabel->setText(QStringLiteral("历史视频文件不存在"));
		return;
	}
	ui->lineEdit->setText(stGetUrlInfo.szFileName);
	ui->statusLabel->setText(QStringLiteral("查询文件成功"));
}
SelectDateDialog::~SelectDateDialog()
{
	delete ui;
}
