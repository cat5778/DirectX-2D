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
	m_byOption(0)
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
	CString csObjectType[7] = { L"Tile",L"Building",L"Tree",L"Grass",L"Monster",L"NPC",L"Player" };
	for (int i = 0; i < 7; i++)
		m_ComboBox.AddString(csObjectType[i]);

	m_TileTool.Create(IDD_TILETOOL);
	m_ObjTool.Create(IDD_OBJECTTOOL);

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
	m_Texname = csItemName.GetString();


	// 픽처 컨트롤에 타일 미리보기 출력.
	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(m_Texname);
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


CString CMyForm::ConvertionCtoE(OBJECT_TYPE _objectType)
{
	switch (_objectType)
	{
	case OBJECT_BUILDING:
		return  L"Building";
		break;
	case OBJECT_MONSTER:
		return  L"Monster";
		break;
	case OBJECT_NPC:
		return L"NPC";
		break;
	case OBJECT_GRASS:
		return  L"Grass";
		break;
	case OBJECT_TREE:
		return L"Tree";
		break;
	case OBJECT_PLAYER:
		return L"Player";
		break;
	default:
		return L"";

		break;
	}

}

void CMyForm::OnCbnSelchange()
{
	CString cs;
	m_ComboBox.GetLBText(m_ComboBox.GetCurSel(), cs);
	//wcout << cs.GetString() << endl;
	for (int i = 0; i < m_ListBox.GetCount(); i++)
		m_ListBox.DeleteString(i);
	//TODO: 요기하는중 현재 콤보박스에서 선택한 오브젝트들만 보이게끔 하는중!!! 
	for (auto object : m_mObjects)
	{
		if(cs.Compare(ConvertionCtoE(object.second))==0)
			m_ListBox.AddString(object.first);
		
	}


}
