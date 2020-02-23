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
	
	DDX_Control(pDX, IDC_PICTURE4, m_Preview);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyForm::OnBnClickedTileButton)
	ON_EN_CHANGE(IDC_EDIT1, &CMyForm::OnEnChangeTileNum)
	ON_EN_CHANGE(IDC_EDIT3, &CMyForm::OnEnChangeTileOption)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMyForm::OnLbnSelchangeList)
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

	m_TileTool.Create(IDD_TILETOOL);

}



void CMyForm::OnBnClickedTileButton()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

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

	//m_pTextureMgr->Getmap();
	// 픽처 컨트롤에 타일 미리보기 출력.
	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(m_Texname);
	NULL_CHECK(pTexInfo);

	//float fCenterX = pTexInfo->tImgInfo.Width * 0.5f;
	//float fCenterY = pTexInfo->tImgInfo.Height * 0.5f;

	D3DXMATRIX matScale, matTrans, matWorld;
	D3DXMatrixScaling(&matScale, 4,3, 0.f);
	D3DXMatrixTranslation(&matTrans, 1, 1, 0.f);

	matWorld = matScale * matTrans;

	CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&matWorld);
	Invalidate(FALSE);
	//TODO: 현재요기중
	CDeviceMgr::GetInstance()->Render_Begin();

	CDeviceMgr::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr, &D3DXVECTOR3(0, 0, 0.f),
		nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	CDeviceMgr::GetInstance()->Render_End(m_Preview.m_hWnd);




}
