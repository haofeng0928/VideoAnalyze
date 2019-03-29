//#include "IMOS.h"
//#include <QDebug>
//#include <QTime>
//#include "opencv2/imgproc.hpp"
//#include "opencv2/core.hpp"
//#include "windows.h"
//#include "mycustomplot.h"
//#include "missionitem.h"
//#include "global.h"
//#include "sdk_struct.h"
//using namespace cv;
//
//LOGIN_INFO_S g_stLoginInfo = { 0 };
//char g_szLastUserName[IMOS_NAME_LEN] = { 0 };
//char g_szLastPasswd[IMOS_PASSWD_ENCRYPT_LEN] = { 0 };
//char g_szLastServerIP[IMOS_IPADDR_LEN] = { 0 };
//char g_szLastServerPort[IMOS_STRING_LEN_32] = { 0 };
//char g_szXpCode[IMOS_RES_CODE_LEN];
//XP_CFG_INFO_S g_stXPCfgInfo = { 0 };
//
//
//ULONG CharToWideChar(LPSTR pChar, ULONG ulCharSize, BOOL_T bIsUTF8, LPCWSTR pWideChar)
//{
//	LONG lOrigsize = 0;
//	LONG lConvertedChars = 0;
//	LONG lCodePage = CP_ACP;
//	if (NULL == pChar)
//	{
//		return ERR_COMMON_INVALID_PARAM;
//	}
//
//	/* Begin: Modified by 黄黎滨2009-06-1 for VVD27429*/
//	lOrigsize = (LONG)strlen((CHAR *)pChar);       /* 获取字符串长度*/
//												   /* End: Modified by 黄黎滨2009-06-1 for VVD27429*/
//	if (0 == lOrigsize)
//	{
//		memset((void*)pWideChar, 0, ulCharSize);
//		return ERR_COMMON_SUCCEED;
//	}
//
//	if (BOOL_TRUE == bIsUTF8)
//	{
//		lCodePage = CP_UTF8;
//	}
//	else
//	{
//		lCodePage = CP_ACP;
//	}
//
//	/* 将pcFilePath转成窄字符*/
//	lConvertedChars = MultiByteToWideChar(
//		lCodePage,                                 /* code page */
//		0,                                         /* performance and mapping flags */
//		(LPCSTR)pChar,                            /* wide-character string */
//		lOrigsize,                                 /* number of chars in string. */
//		(LPWSTR)pWideChar,                         /* buffer for new string */
//		(LONG)ulCharSize - 1                      /* size of buffer */
//	);
//
//	if (0 == lConvertedChars)
//	{
//		return ERR_COMMON_FAIL;
//	}
//
//	return ERR_COMMON_SUCCEED;
//}
//ULONG WideCharToChar(LPCWSTR pWideChar, ULONG ulCharSize, BOOL_T bIsUTF8, LPSTR pChar)
//{
//	LONG lOrigsize = 0;
//	LONG lConvertedChars = 0;
//	LONG lCodePage = CP_ACP;
//	if (NULL == pWideChar)
//	{
//		return ERR_COMMON_INVALID_PARAM;
//	}
//
//	/* Begin: Modified by 黄黎滨2009-06-1 for VVD27429*/
//	lOrigsize = (LONG)wcslen((WCHAR *)pWideChar);       /* 获取字符串长度*/
//														/* End: Modified by 黄黎滨2009-06-1 for VVD27429*/
//	if (0 == lOrigsize)
//	{
//		memset(pChar, 0, ulCharSize + 1);
//		return ERR_COMMON_SUCCEED;
//	}
//
//	if (BOOL_TRUE == bIsUTF8)
//	{
//		lCodePage = CP_UTF8;
//	}
//	else
//	{
//		lCodePage = CP_ACP;
//	}
//
//	/* 将pcFilePath转成窄字符*/
//	lConvertedChars = WideCharToMultiByte(
//		lCodePage,                                      /* code page */
//		0,//WC_COMPOSITECHECK|WC_DEFAULTCHAR,           /* Modified by guwuqiang,20160817 of 中文用户名登录 中文转UTF8失败 *//* performance and mapping flags */ 
//		(LPCWSTR)pWideChar,                            /* wide-character string */
//		lOrigsize,                                      /* number of chars in string. */
//		pChar,                                          /* buffer for new string */
//		(LONG)ulCharSize - 1,                          /* size of buffer */
//		0,                                              /* default for unmappable chars */
//		0                                               /* set when default char used */
//	);
//
//	if (0 == lConvertedChars)
//	{
//		return ERR_COMMON_FAIL;
//	}
//	/* Begin: Added by 黄黎滨2009-06-1 for VVD27429*/
//	pChar[lConvertedChars] = '\0';
//	/* End: Added by 黄黎滨2009-06-1 for VVD27429*/
//
//	return ERR_COMMON_SUCCEED;
//}
//void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length)
//{
//	WCHAR *pWchar;
//	pWchar = (WCHAR *)malloc(length * sizeof(WCHAR));
//	if (NULL == pWchar)
//	{
//		return;
//	}
//	memset(pWchar, 0, length * sizeof(WCHAR));
//
//	CharToWideChar(pSrcChar, length, BOOL_FALSE, pWchar);
//	WideCharToChar(pWchar, length, BOOL_TRUE, pcDestChar);
//	if (NULL != pWchar)
//	{
//		free(pWchar);
//	}
//}
//void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length)
//{
//	WCHAR *pWchar;
//	pWchar = (WCHAR *)malloc(length * sizeof(WCHAR));
//	if (NULL == pWchar)
//	{
//		return;
//	}
//	memset(pWchar, 0, length * sizeof(WCHAR));
//
//	CharToWideChar(pSrcChar, length, BOOL_TRUE, pWchar);
//	WideCharToChar(pWchar, length, BOOL_FALSE, pcDestChar);
//	if (NULL != pWchar)
//	{
//		free(pWchar);
//	}
//}
//void InitImos()
//{
//	g_stXPCfgInfo.enPixelFormat = XP_PIXEL_FORMAT_YUV420;
//	g_stXPCfgInfo.enRenderMode = XP_RENDER_MODE_LOWER;
//	g_stXPCfgInfo.enPictureFluency = XP_PICTURE_TIME_PRIORITY;
//}
//
//
//VOID __stdcall DecoderVideoOutput_Real(IN USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo,
//	IN CHAR  szCamCode[IMOS_RES_CODE_LEN],
//	IN STORE_RES_INFO_S *  pstStoreResInfo
//)
//{
//	if (IMOS_AssignStoreRes(pstUserLoginIDInfo, szCamCode, pstStoreResInfo) == ERR_COMMON_SUCCEED) {
//	}
//	return;
//}