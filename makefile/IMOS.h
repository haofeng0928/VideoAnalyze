#pragma once
#include <QObject>
#include <QString>
#include <QVector>
#include <windows.h>
#include <string>
#include "sdk_func.h"
#include "xp_func.h"
#include "xp_func_inner.h"

#include <core.hpp>
#include <imgproc.hpp>
#include <highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

#define DEMO_MAX_PLAYS  25
#define DOC_CAMERA 0xFFFFFF01
#define DOC_MONITOR 0xFFFFFF02
#define DOC_SWITCHRES 0xFFFFFF03
#define DEMO_QUERY_PAGE_NUM 200

extern LOGIN_INFO_S g_stLoginInfo;
extern char g_szLastUserName[IMOS_NAME_LEN];
extern char g_szLastPasswd[IMOS_PASSWD_ENCRYPT_LEN];
extern char g_szLastServerIP[IMOS_IPADDR_LEN];
extern char g_szLastServerPort[IMOS_STRING_LEN_32];

extern char g_szXpCode[IMOS_RES_CODE_LEN];

class TreeData
{
public:
	ORG_RES_QUERY_ITEM_S m_nodeInfo;
	USER_LOGIN_ID_INFO_S m_stUseLoginInfo;
	QString text;
	TreeData() {}
	TreeData(const TreeData &other) {
		memcpy(&m_nodeInfo, &other.m_nodeInfo, sizeof(ORG_RES_QUERY_ITEM_S));
		memcpy(&m_stUseLoginInfo, &other.m_stUseLoginInfo, sizeof(ORG_RES_QUERY_ITEM_S));
		text = other.text;
	}
	bool isEqual(const TreeData &other)
	{
		return !memcmp(&m_nodeInfo, &other.m_nodeInfo, sizeof(ORG_RES_QUERY_ITEM_S));
	}
};
Q_DECLARE_METATYPE(TreeData)
Q_DECLARE_METATYPE(TreeData *)
typedef enum tagTreeImageEnum
{
	TREE_ROOT = 0,
	TREE_LOCAL_DOMAIN,
	TREE_FOLDER,
	TREE_FOLDER_OPEN,
	TREE_CAMERA,
	TREE_DOME,
	TREE_CAMERA_OFFLINE,
	TREE_DOME_OFFLINE,
	TREE_GUARDTOURRES
}TREE_IMAGE_E;

typedef struct tagCfgInfo
{
	ULONG ulSnatchInterval;
	ULONG ulMaxMediaPort;
	ULONG ulMinMediaPort;
	ULONG ulMaxProtlPort;
	ULONG ulMinProtlPort;
	ULONG ulSysVolume;
	ULONG ulRRPlayTime;
	XP_PROTOCOL_E enProtl;                /* ����Э�� */
	XP_FIELD_MODE_E enFieldMode;          /* ��Ƶ�ļ�ģʽ */
	XP_RENDER_MODE_E enRenderMode;        /* ��Ƶ����ģʽ */
	XP_PICTURE_FORMAT_E enPicType;        /* ͼƬ��ʽ */
	XP_DEINTERLACE_MODE_E enDeinterlace;  /* ȥ��֯����ģʽ��ö�ٶ��� */
	XP_PIXEL_FORMAT_EX_E enPixelFormat;   /* ��Ƶ���ظ�ʽ */
	XP_PICTURE_FLUENCY_E enPictureFluency;/* ͼ�񲥷������� */

										  /* begin add by guwuqiang gW1963 20161123*/
	XP_MEDIA_FILE_FORMAT_E enRecordFileFormat;/* ý���ļ���ʽ */
	XP_MEDIA_FILE_FORMAT_E enDownloadFileFormat;/* ý���ļ���ʽ */
	IMOS_TRANS_TYPE_E enTransProtl;/* ʵ��������Э�� */
	IMOS_STREAM_SERVER_MODE_E enStreamServerMode;/* �����䷽ʽ */
	ULONG_32 ulStreamType;/* ���鲥���� 0Ϊ��֧�ֵ�����1Ϊ��֧�ֵ���Ҳ֧���鲥 */
	IMOS_STREAM_SERVER_MODE_E enVoiceCommMode;/* �����Խ����䷽ʽ */
	XP_STREAM_PULL_TYPE enXPStreamPullType;/* NAT����ѡ�� */
										   /* end add by guwuqiang gW1963 20161123*/
}XP_CFG_INFO_S;
extern XP_CFG_INFO_S g_stXPCfgInfo;

void InitImos();
void ConvertUnicodeToUTF8(LPSTR pSrcChar, LPSTR pcDestChar, int length);
void ConvertUTF8ToUnicode(LPSTR pSrcChar, LPSTR pcDestChar, int length);
VOID __stdcall DecoderVideoOutput_Real(IN const USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo,
	IN const CHAR *pcChannelCode,
	IN const XP_PICTURE_DATA_S *pPictureData,
	IN LONG_REAL lUserParam,
	IN LONG_REAL lReserved);
VOID __stdcall DecoderVideoOutput_Recall(IN const USER_LOGIN_ID_INFO_S *pstUserLoginIDInfo,
	IN const CHAR *pcChannelCode,
	IN const XP_PICTURE_DATA_S *pPictureData,
	IN LONG_REAL lUserParam,
	IN LONG_REAL lReserved);