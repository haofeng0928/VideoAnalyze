#include "IMOS.h"
#include <QDebug>
#include <QTime>
#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "windows.h"
#include "mycustomplot.h"
#include "missionitem.h"
#include "global.h"
using namespace cv;

LOGIN_INFO_S g_stLoginInfo = { 0 };
char g_szLastUserName[IMOS_NAME_LEN] = { 0 };
char g_szLastPasswd[IMOS_PASSWD_ENCRYPT_LEN] = { 0 };
char g_szLastServerIP[IMOS_IPADDR_LEN] = { 0 };
char g_szLastServerPort[IMOS_STRING_LEN_32] = { 0 };
char g_szXpCode[IMOS_RES_CODE_LEN];
XP_CFG_INFO_S g_stXPCfgInfo = { 0 };

double addPic(const Mat &Mat)//求和函数，计算图片所有元素像素值的和，输入为要计算矩阵
{
	double people_lower = 0.005;
	double people_upper = 0.1;
	int peopleLevel_lower = 1;
	int peopleLevel_upper = 8;
	int sum = 0;
	int result = 0;
	int rows = Mat.rows;
	int cols = Mat.cols;
	double scale = 0;
	for (int row = rows / 10; row < rows; row++)
	{
		const float* ptr = Mat.ptr<float>(row);
		for (int col = 0; col < cols; col++)
		{
			sum += *(ptr + col);
		}
	}
	scale = ((double)sum) / (double)(rows - rows / 10) / (double)cols;
	if (scale < people_lower)
		return 0;
	else if (scale < people_upper)
		return peopleLevel_lower + (peopleLevel_upper - peopleLevel_lower) * (scale - people_lower) / (people_upper - people_lower);
	else if (scale < 0.7)
		return 9;
	else
		return 10;
}
ULONG CharToWideChar(LPSTR pChar, ULONG ulCharSize, BOOL_T bIsUTF8, LPCWSTR pWideChar)
{
	LONG lOrigsize = 0;
	LONG lConvertedChars = 0;
	LONG lCodePage = CP_ACP;
	if (NULL == pChar)
	{
		return ERR_COMMON_INVALID_PARAM;
	}

	/* Begin: Modified by 黄黎滨2009-06-1 for VVD27429*/
	lOrigsize = (LONG)strlen((CHAR *)pChar);       /* 获取字符串长度*/
												   /* End: Modified by 黄黎滨2009-06-1 for VVD27429*/
	if (0 == lOrigsize)
	{
		memset((void*)pWideChar, 0, ulCharSize);
		return ERR_COMMON_SUCCEED;
	}

	if (BOOL_TRUE == bIsUTF8)
	{
		lCodePage = CP_UTF8;
	}
	else
	{
		lCodePage = CP_ACP;
	}

	/* 将pcFilePath转成窄字符*/
	lConvertedChars = MultiByteToWideChar(
		lCodePage,                                 /* code page */
		0,                                         /* performance and mapping flags */
		(LPCSTR)pChar,                            /* wide-character string */
		lOrigsize,                                 /* number of chars in string. */
		(LPWSTR)pWideChar,                         /* buffer for new string */
		(LONG)ulCharSize - 1                      /* size of buffer */
	);

	if (0 == lConvertedChars)
	{
		return ERR_COMMON_FAIL;
	}

	return ERR_COMMON_SUCCEED;
}
ULONG WideCharToChar(LPCWSTR pWideChar, ULONG ulCharSize, BOOL_T bIsUTF8, LPSTR pChar)
{
	LONG lOrigsize = 0;
	LONG lConvertedChars = 0;
	LONG lCodePage = CP_ACP;
	if (NULL == pWideChar)
	{
		return ERR_COMMON_INVALID_PARAM;
	}

	/* Begin: Modified by 黄黎滨2009-06-1 for VVD27429*/
	lOrigsize = (LONG)wcslen((WCHAR *)pWideChar);       /* 获取字符串长度*/
														/* End: Modified by 黄黎滨2009-06-1 for VVD27429*/
	if (0 == lOrigsize)
	{
		memset(pChar, 0, ulCharSize + 1);
		return ERR_COMMON_SUCCEED;
	}

	if (BOOL_TRUE == bIsUTF8)
	{
		lCodePage = CP_UTF8;
	}
	else
	{
		lCodePage = CP_ACP;
	}

	/* 将pcFilePath转成窄字符*/
	lConvertedChars = WideCharToMultiByte(
		lCodePage,                                      /* code page */
		0,//WC_COMPOSITECHECK|WC_DEFAULTCHAR,           /* Modified by guwuqiang,20160817 of 中文用户名登录 中文转UTF8失败 *//* performance and mapping flags */ 
		(LPCWSTR)pWideChar,                            /* wide-character string */
		lOrigsize,                                      /* number of chars in string. */
		pChar,                                          /* buffer for new string */
		(LONG)ulCharSize - 1,                          /* size of buffer */
		0,                                              /* default for unmappable chars */
		0                                               /* set when default char used */
	);

	if (0 == lConvertedChars)
	{
		return ERR_COMMON_FAIL;
	}
	/* Begin: Added by 黄黎滨2009-06-1 for VVD27429*/
	pChar[lConvertedChars] = '\0';
	/* End: Added by 黄黎滨2009-06-1 for VVD27429*/

	return ERR_COMMON_SUCCEED;
}
void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length)
{
	WCHAR *pWchar;
	pWchar = (WCHAR *)malloc(length * sizeof(WCHAR));
	if (NULL == pWchar)
	{
		return;
	}
	memset(pWchar, 0, length * sizeof(WCHAR));

	CharToWideChar(pSrcChar, length, BOOL_FALSE, pWchar);
	WideCharToChar(pWchar, length, BOOL_TRUE, pcDestChar);
	if (NULL != pWchar)
	{
		free(pWchar);
	}
}
void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length)
{
	WCHAR *pWchar;
	pWchar = (WCHAR *)malloc(length * sizeof(WCHAR));
	if (NULL == pWchar)
	{
		return;
	}
	memset(pWchar, 0, length * sizeof(WCHAR));

	CharToWideChar(pSrcChar, length, BOOL_TRUE, pWchar);
	WideCharToChar(pWchar, length, BOOL_FALSE, pcDestChar);
	if (NULL != pWchar)
	{
		free(pWchar);
	}
}
void InitImos()
{
	g_stXPCfgInfo.enPixelFormat = XP_PIXEL_FORMAT_YUV420;
	g_stXPCfgInfo.enRenderMode = XP_RENDER_MODE_LOWER;
	g_stXPCfgInfo.enPictureFluency = XP_PICTURE_TIME_PRIORITY;
}

VOID __stdcall DecoderVideoOutput_Real(IN const USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo,
	IN const CHAR *pcChannelCode,
	IN const XP_PICTURE_DATA_S *pPictureData,
	IN LONG_REAL lUserParam,
	IN LONG_REAL lReserved)
{
	MyCustomPlot *cp = (MyCustomPlot *)lUserParam;
	if (!cp->isUpdate)
		return;
	Mat frame_read(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_8UC1, pPictureData->pucData[0]);
	frame_read.convertTo(frame_read, CV_32FC1);
	if (cp->startSec == -1)
	{
		cp->startSec = QTime(0, 0, 0).secsTo(QTime::currentTime());
		cp->xAxis->setRange(cp->startSec - 50, cp->startSec + 100);
		cp->realTimeVideoWidget->resize(pPictureData->ulPicWidth / 2, pPictureData->ulPicHeight / 2);
		cp->startRenderTime = pPictureData->dlRenderTime;
		cp->blackFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		cp->frontFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		cp->currentFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		frame_read.convertTo(cp->blackFrame, CV_32FC1);
		frame_read.convertTo(cp->frontFrame, CV_32FC1);
	}
	cp->renderTime = pPictureData->dlRenderTime;

	frame_read.convertTo(cp->currentFrame, CV_32FC1);

	//当前帧跟背景图相减
	absdiff(cp->currentFrame, cp->blackFrame, cp->frontFrame);
	//二值化
	threshold(cp->frontFrame, cp->frontFrame, 25, 1, CV_THRESH_BINARY);
	//更新背景
	accumulateWeighted(cp->currentFrame, cp->blackFrame, 0.8);

	cp->value = addPic(cp->frontFrame);
	cp->isUpdate = false;
	return;
}

VOID __stdcall DecoderVideoOutput_Recall(IN const USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo,
	IN const CHAR *pcChannelCode,
	IN const XP_PICTURE_DATA_S *pPictureData,
	IN LONG_REAL lUserParam,
	IN LONG_REAL lReserved)
{
	MissionItem *mission = (MissionItem *)lUserParam;
	Mat frame_read(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_8UC1, pPictureData->pucData[0]);
	frame_read.convertTo(frame_read, CV_32FC1);
	ULONG_32 absoluteTime;
	IMOS_GetPlayedTimeEx(&g_stLoginInfo.stUserLoginIDInfo, mission->szXpCode, &absoluteTime);
	if (mission->state == 0)
	{
		mission->startRenderTime = pPictureData->dlRenderTime;
		mission->startAbsoluteTime = absoluteTime;
		mission->curAbsoluteTime = absoluteTime;
		mission->realAbsoluteTime = absoluteTime;
		mission->state = 1;
		mission->blackFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		mission->frontFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		mission->currentFrame.create(pPictureData->ulPicHeight, pPictureData->ulPicWidth, CV_32FC1);
		frame_read.convertTo(mission->blackFrame, CV_32FC1);
		frame_read.convertTo(mission->frontFrame, CV_32FC1);
	}

	frame_read.convertTo(mission->currentFrame, CV_32FC1);
	//当前帧跟背景图相减
	absdiff(mission->currentFrame, mission->blackFrame, mission->frontFrame);
	//二值化
	threshold(mission->frontFrame, mission->frontFrame, 25, 1, CV_THRESH_BINARY);
	//更新背景
	accumulateWeighted(mission->currentFrame, mission->blackFrame, 0.8);

	if (absoluteTime == mission->curAbsoluteTime)
	{
		mission->addDate(mission->realAbsoluteTime - mission->startAbsoluteTime, addPic(mission->frontFrame));
		qDebug() << mission->realAbsoluteTime - mission->startAbsoluteTime << "==";
	}
	else
	{
		mission->curAbsoluteTime = absoluteTime;
		mission->realAbsoluteTime = absoluteTime;
		mission->addDate(mission->realAbsoluteTime - mission->startAbsoluteTime, addPic(mission->frontFrame));
		qDebug() << mission->realAbsoluteTime - mission->startAbsoluteTime << "!=";
	}
	mission->realAbsoluteTime++;
	return;
}