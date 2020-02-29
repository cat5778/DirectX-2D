// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"
// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM),
	m_byDrawID(0),
	m_Texname(L"TileSet1"),
	m_byOption(0),
	m_iOldCount(0)
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_byDrawID);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Text(pDX, IDC_EDIT3, m_byOption);
	DDX_Control(pDX, IDC_Picture, m_Preview);
	DDX_Control(pDX, IDC_COMBO1, m_ComboBox);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedTileButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyForm::OnBnClickedObjectTool)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMyForm::OnLbnSelchangeList)
	ON_EN_CHANGE(IDC_EDIT1, &CMyForm::OnEnChangeTileNum)
	ON_EN_CHANGE(IDC_EDIT3, &CMyForm::OnEnChangeTileOption)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMyForm::OnCbnSelchange)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyForm::OnBnClickedObject)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	CString csObjectType[8] = { L"Tile",L"Building",L"Tree",L"Grass",L"Monster",L"NPC",L"Player",L"Obstacle" };
	for (int i = 0; i < 8; i++)
		m_ComboBox.AddString(csObjectType[i]);
	ReadData(L"../Data/PathInfo.txt");
	//CTextureMgr::GetInstance()->
	m_TileTool.Create(IDD_TILETOOL);
	m_ObjTool.Create(IDD_OBJECTTOOL);
	m_PathTool.Create(IDD_PATHTOOL);

}



void CMyForm::OnBnClickedTileButton()
{

	m_TileTool.ShowWindow(SW_SHOW);

}



void CMyForm::OnEnChangeTileNum()
{
	UpdateData(TRUE);
	
	cout << (int)m_byDrawID << endl;

}

CString CMyForm::ConvertionEtoC(OBJECT_TYPE eObjectType)
{
	switch (eObjectType)
	{
	case OBJECT_BUILDING:
		return L"Building";
	case OBJECT_MONSTER:
		return L"Monster";
	case OBJECT_NPC:
		return L"NPC";
	case OBJECT_GRASS:
		return L"Grass";
	case OBJECT_TREE:
		return L"Tree";
	case OBJECT_PLAYER:
		return L"Player";
	default:
		return L"";
	}
}

HRESULT CMyForm::ReadData(wstring wstrFilePath)
{
	wifstream fin;

	fin.open(wstrFilePath);

	if (fin.fail())
		return E_FAIL;

	TCHAR szObjectKey[MAX_STR] = L"";
	TCHAR szStateKey[MAX_STR] = L"";
	TCHAR szCount[MAX_STR] = L"";
	TCHAR szRelative[MAX_STR] = L"";

	while (true)
	{
		fin.getline(szObjectKey, MAX_STR, '|');
		fin.getline(szStateKey, MAX_STR, '|');
		fin.getline(szCount, MAX_STR, '|');
		fin.getline(szRelative, MAX_STR);

		if (fin.eof())
			break;
		ConvertionCtoE(szObjectKey);
		switch (m_eObjType)
		{
		case OBJECT_OBSTACLE:
			m_ObjectPath.insert(make_pair(szStateKey, m_eObjType));
			break;
			//case object_
		case OBJECT_TERRAIN:
			m_mTilePath.insert(make_pair(szStateKey,szObjectKey));
			break;
		default:
			break;
		}
	}

	fin.close();
}


void CMyForm::OnEnChangeTileOption()
{
	UpdateData(TRUE);
	cout << (int)m_byOption << endl;

}


void CMyForm::OnLbnSelchangeList()
{
	CString csItemName;

	//cout << csItemName << endl;


	m_ListBox.GetText(m_ListBox.GetCurSel(), csItemName);
	// 픽처 컨트롤에 타일 미리보기 출력.
	
	m_TilePath = make_pair(m_mTilePath.find(csItemName)->first.GetString(), m_mTilePath.find(csItemName)->second.GetString());
	//wcout << m_TilePath.first.GetString() << endl;

	//wcout << m_TilePath.second.GetString() << endl;
	
	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(m_TilePath.second.GetString(), m_TilePath.first.GetString());
	NULL_CHECK(pTexInfo);
	float fCenterX = 0;
	float fCenterY = 0;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, (float)WINCX / pTexInfo->tImgInfo.Width, (float)WINCY / pTexInfo->tImgInfo.Height, 0.f);
	D3DXMatrixTranslation(&matTrans, 0, 0, 0.f);

	matWorld = matScale * matTrans;

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&matWorld);
	Invalidate(FALSE);


	CDeviceMgr::GetInstance()->Render_Begin();

	CDeviceMgr::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(fCenterX, fCenterY, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDeviceMgr::GetInstance()->Render_End(m_Preview.m_hWnd);




}


void CMyForm::OnBnClickedObjectTool()
{
	m_ObjTool.ShowWindow(SW_SHOW);


}


void CMyForm::OnCbnSelchange()
{
	m_ListBox.ResetContent();
	CString cs;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(), cs);

	if (cs.Compare(L"Tile") == 0)
	{
		for (auto path : m_mTilePath)
			m_ListBox.AddString(path.first);

	}
	for (auto object : m_ObjectPath)
	{
		if (cs.Compare(ConvertionEtoC(object.second)) == 0)
		{
			//wcout << object.first.GetString() << endl;
			m_ListBox.AddString(object.first);
			m_iOldCount++;
		}
		
	}
	//wcout << cs.GetString() << endl;
	m_iOldCount = 0;

}

void CMyForm::ConvertionCtoE(CString csobjType)
{
	if (csobjType.Compare(L"Building") == 0)
		m_eObjType = OBJECT_BUILDING;
	else if (csobjType.Compare(L"Tree") == 0)
		m_eObjType = OBJECT_TREE;
	else if (csobjType.Compare(L"Grass") == 0)
		m_eObjType = OBJECT_GRASS;
	else if (csobjType.Compare(L"NPC") == 0)
		m_eObjType = OBJECT_NPC;
	else if (csobjType.Compare(L"Monster") == 0)
		m_eObjType = OBJECT_MONSTER;
	else if (csobjType.Compare(L"Player") == 0)
		m_eObjType = OBJECT_PLAYER;
	else if (csobjType.Compare(L"Trap") == 0)
		m_eObjType = OBJECT_TRAP;
	else if (csobjType.Compare(L"Obstacle") == 0)
		m_eObjType = OBJECT_OBSTACLE;

}


void CMyForm::OnBnClickedObject()
{
	m_PathTool.ShowWindow(SW_SHOW);

}
