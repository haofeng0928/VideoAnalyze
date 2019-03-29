#include "cameralistwidget.h"
#include <QMessageBox>
#include <QAction>
#include <QMenu>
#include <QDebug>

CameraListWidget::CameraListWidget(QWidget *parent)
	: QTreeWidget(parent)
{
	selectedCamera = NULL;
	this->setHeaderHidden(true);
	this->setColumnCount(1);
	QHeaderView *pHeader = this->header();
	pHeader->setSectionResizeMode(QHeaderView::ResizeToContents);
	pHeader->setStretchLastSection(false);

	connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem *, int)), this, SLOT(doubleClickedOnTreeItem(QTreeWidgetItem *, int)));
	connect(this, SIGNAL(itemPressed(QTreeWidgetItem *, int)), this, SLOT(itemRightButtonMenu(QTreeWidgetItem *, int)));
}
void CameraListWidget::itemRightButtonMenu(QTreeWidgetItem *item , int column)
{
	if (qApp->mouseButtons() != Qt::RightButton)
		return;
	QMenu*menu = new QMenu(this);
	menu->setAttribute(Qt::WA_DeleteOnClose);
	TreeData *pNode = item->data(0, QTreeWidgetItem::UserType).value<TreeData *>();
	if (pNode->m_nodeInfo.ulResType == IMOS_TYPE_CAMERA)
	{
		menu->addAction(QStringLiteral("绘制实时曲线"), [this, pNode]() {emit realTimeGraph(pNode); });
		menu->addAction(QStringLiteral("获取历史曲线"), [this, pNode]() {emit getHistoryGraph(pNode); });
		menu->addAction(QStringLiteral("绘制历史曲线"), [this, pNode]() {emit drawHistoryGraph(pNode); });
	}
	//menu->addAction(QStringLiteral("刷新摄像机"), this, SLOT(searchCameraSlot()));
	menu->exec(QCursor::pos());
}
void CameraListWidget::searchCameraSlot()
{
	if (g_stLoginInfo.stUserLoginIDInfo.szUserLoginCode[0] == 0)
	{
		QMessageBox::warning(NULL, QStringLiteral("错误"), QStringLiteral("未登陆"));
		return;
	}
	//使用用户所在域为树的根节点
	TreeData * pRootNode = new TreeData();
	strncpy(pRootNode->m_nodeInfo.szOrgCode, g_stLoginInfo.szOrgCode, IMOS_DOMAIN_CODE_LEN);
	strncpy(pRootNode->m_nodeInfo.szResName, g_stLoginInfo.szDomainName, IMOS_NAME_LEN);
	strncpy(pRootNode->m_nodeInfo.szResCode, g_stLoginInfo.szOrgCode, IMOS_RES_CODE_LEN);
	memcpy(&pRootNode->m_stUseLoginInfo, &g_stLoginInfo.stUserLoginIDInfo, sizeof(USER_LOGIN_ID_INFO_S));
	pRootNode->m_nodeInfo.ulResType = IMOS_TYPE_ORG;
	pRootNode->m_nodeInfo.ulResSubType = 0;
	QString text = QString(g_stLoginInfo.szDomainName) + QString(g_stLoginInfo.stUserLoginIDInfo.szUserCode);
	pRootNode->text = text;
	addTopItem(pRootNode);
	return;
}
CameraListWidget::~CameraListWidget()
{

}
void CameraListWidget::addTopItem(TreeData *data)
{
	QTreeWidgetItem * tmp = new QTreeWidgetItem(this, QStringList(data->text), QTreeWidgetItem::UserType);
	tmp->setIcon(0, QIcon(QPixmap(QString(":/analyze/Resources/LocalDomain.bmp"))));
	QVariant i;
	i.setValue<TreeData *>(data);
	tmp->setData(0, QTreeWidgetItem::UserType, i);
}
void CameraListWidget::doubleClickedOnTreeItem(QTreeWidgetItem *tmp, int)
{
	TreeData *pNode = tmp->data(0, QTreeWidgetItem::UserType).value<TreeData *>();
	selectedCamera = NULL;
	TreeData *pDocCameraNode = NULL;
	TreeData *pDocSwitchResNode = NULL;
	CHAR strResName[IMOS_NAME_LEN] = { 0 };
	ULONG ulRet = ERR_COMMON_FAIL;
	//当存在子节点时，为收起子树操作，将子节点删除
	if (tmp->isExpanded())
	{
		QList<QTreeWidgetItem *> itemList = tmp->takeChildren();
		for (int i = 0; i < itemList.count(); i++)
		{
			//TreeData *data = tmp->data(0, QTreeWidgetItem::UserType).value<TreeData *>();
			//delete data;
			tmp->removeChild(itemList.at(i));
			delete itemList.at(i);
		}
		tmp->setExpanded(false);
		return;
	}
	switch (pNode->m_nodeInfo.ulResType)
	{
	case IMOS_TYPE_ORG:
	{
		//更新全局的信息
		memcpy(&g_stLoginInfo.stUserLoginIDInfo, &pNode->m_stUseLoginInfo, sizeof(USER_LOGIN_ID_INFO_S));
		strncpy(g_stLoginInfo.szOrgCode, pNode->m_nodeInfo.szOrgCode, IMOS_DOMAIN_CODE_LEN);
		strncpy(g_stLoginInfo.szDomainName, pNode->m_nodeInfo.szResName, IMOS_NAME_LEN);
		strncpy(g_stLoginInfo.szOrgCode, pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);

		//添加摄像机文件夹
		pDocCameraNode = new TreeData();
		strncpy(pDocCameraNode->m_nodeInfo.szOrgCode, pNode->m_nodeInfo.szOrgCode, IMOS_DOMAIN_CODE_LEN);
		strncpy(pDocCameraNode->m_nodeInfo.szResName, QString(QStringLiteral("摄像机")).toStdString().c_str(), IMOS_NAME_LEN);
		strncpy(pDocCameraNode->m_nodeInfo.szResCode, pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);
		pDocCameraNode->m_nodeInfo.ulResType = DOC_CAMERA;

		pDocCameraNode->text = QString(pDocCameraNode->m_nodeInfo.szResName);
		addChildItem(tmp, pDocCameraNode);

		//添加轮切资源文件夹
		pDocSwitchResNode = new TreeData();
		strncpy(pDocSwitchResNode->m_nodeInfo.szOrgCode, pNode->m_nodeInfo.szOrgCode, IMOS_DOMAIN_CODE_LEN);
		strncpy(pDocSwitchResNode->m_nodeInfo.szResName, QString(QStringLiteral("轮切资源")).toStdString().c_str(), IMOS_NAME_LEN);
		strncpy(pDocSwitchResNode->m_nodeInfo.szResCode, pNode->m_nodeInfo.szResCode, IMOS_RES_CODE_LEN);
		pDocSwitchResNode->m_nodeInfo.ulResType = DOC_SWITCHRES;

		pDocSwitchResNode->text = QString(pDocSwitchResNode->m_nodeInfo.szResName);

		addChildItem(tmp, pDocSwitchResNode);
		//添加子域
		AddSubTreeNode(IMOS_TYPE_ORG, TREE_LOCAL_DOMAIN, pNode->m_nodeInfo.szResCode, tmp);
		break;
	}
	case DOC_CAMERA:
	{
		//添加摄像机
		AddSubTreeNode(IMOS_TYPE_CAMERA, IMOS_TYPE_CAMERA, pNode->m_nodeInfo.szResCode, tmp);
		break;
	}
	case DOC_MONITOR:
	{
		break;
	}
	case DOC_SWITCHRES:
	{
		AddSubTreeNode(IMOS_TYPE_GUARD_TOUR_RESOURCE, IMOS_TYPE_GUARD_TOUR_RESOURCE, pNode->m_nodeInfo.szResCode, tmp);
		break;
	}
	case IMOS_TYPE_CAMERA:
	{
		selectedCamera = pNode;
		emit realTimeGraph(pNode);
		break;
	}
	case IMOS_TYPE_GUARD_TOUR_RESOURCE:
	{
		break;
	}
	default:
		break;
	}
	return;
}
void CameraListWidget::AddSubTreeNode(unsigned long ulResType, unsigned long iconType, char* pcOrzCode, QTreeWidgetItem *parent)
{
	ULONG ulRet;
	QUERY_PAGE_INFO_S stQueryPageInfo = { 0 };
	COMMON_QUERY_CONDITION_S stQueryCondition = { 0 };
	RSP_PAGE_INFO_S stRspPageInfo = { 0 };
	ULONG ulBeginNum = 0;
	ULONG ulTotalNum = 0;
	CHAR  strResName[IMOS_NAME_LEN] = { 0 };
	//分配查询结果内存，每次查DEMO_QUERY_PAGE_NUM条
	RES_ITEM_V2_S * pstResList = (RES_ITEM_V2_S *)malloc(DEMO_QUERY_PAGE_NUM * sizeof(RES_ITEM_V2_S));
	if (NULL == pstResList)
	{
		return;
	}
	memset(pstResList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RES_ITEM_V2_S));
	do
	{
		stQueryPageInfo.ulPageFirstRowNumber = ulBeginNum;
		stQueryPageInfo.ulPageRowNum = DEMO_QUERY_PAGE_NUM;
		stQueryPageInfo.bQueryCount = BOOL_TRUE;

		stQueryCondition.ulItemNum = 1;
		stQueryCondition.astQueryConditionList[0].ulQueryType = RES_TYPE;
		stQueryCondition.astQueryConditionList[0].ulLogicFlag = EQUAL_FLAG;
		sprintf_s(stQueryCondition.astQueryConditionList[0].szQueryData, IMOS_QUERY_DATA_MAX_LEN, "%d", ulResType);
		/* 调用SDK接口查询资源列表，分页查询，每次查询DEMO_QUERY_PAGE_NUM条记录 */
		ulRet = IMOS_QueryResourceListV2(&g_stLoginInfo.stUserLoginIDInfo,
			pcOrzCode,
			&stQueryCondition,
			&stQueryPageInfo,
			&stRspPageInfo,
			pstResList);
		if (ERR_COMMON_SUCCEED != ulRet)
		{
			free(pstResList);
			return;
		}
		for (ULONG i = 0; i < stRspPageInfo.ulRowNum; i++)
		{
			TreeData * pNode = new TreeData();
			memcpy(&pNode->m_nodeInfo, &pstResList[i].stResItemV1, sizeof(ORG_RES_QUERY_ITEM_S));
			memcpy(&pNode->m_stUseLoginInfo, &g_stLoginInfo.stUserLoginIDInfo, sizeof(USER_LOGIN_ID_INFO_S));

			pNode->text = QString(pNode->m_nodeInfo.szResName);
			addChildItem(parent, pNode, iconType);
		}
		ulTotalNum = stRspPageInfo.ulTotalRowNum;
		ulBeginNum += stRspPageInfo.ulRowNum;
		memset(pstResList, 0, DEMO_QUERY_PAGE_NUM * sizeof(RES_ITEM_V2_S));
	} while (ulTotalNum > ulBeginNum);
	if (NULL != pstResList)
	{
		free(pstResList);
		pstResList = NULL;
	}
}
void CameraListWidget::addChildItem(QTreeWidgetItem *parent, TreeData *data, unsigned long ulResType)
{
	QTreeWidgetItem * tmp = new QTreeWidgetItem(parent, QStringList(data->text), QTreeWidgetItem::UserType);
	setIconForItem(tmp, data, ulResType);
	QVariant i;
	i.setValue<TreeData *>(data);
	tmp->setData(0, QTreeWidgetItem::UserType, i);
	tmp->setToolTip(0, data->text);
}
void CameraListWidget::setIconForItem(QTreeWidgetItem * tmp, TreeData *data, unsigned long ulResType)
{
	ULONG_32 type = data->m_nodeInfo.ulResType;
	if (ulResType != 0)
		type = ulResType;
	switch (type)
	{
	case TREE_LOCAL_DOMAIN:
		tmp->setIcon(0, QIcon(QPixmap(QString(":/analyze/Resources/LocalDomain.bmp"))));
		return;
	case DOC_CAMERA:
	case DOC_SWITCHRES:
		tmp->setIcon(0, QIcon(QPixmap(QString(":/analyze/Resources/Folder.bmp"))));
		return;
	case IMOS_TYPE_CAMERA:
		if (IMOS_DEV_STATUS_ONLINE == data->m_nodeInfo.ulResStatus)
			tmp->setIcon(0, QIcon(QPixmap(QString(":/analyze/Resources/Camera.bmp"))));
		else
			tmp->setIcon(0, QIcon(QPixmap(QString(":/analyze/Resources/Camera_Offline.bmp"))));
		break;
	default:break;
	}
}