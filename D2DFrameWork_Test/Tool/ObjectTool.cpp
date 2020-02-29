// ObjectTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "MainFrm.h"
#include "MyForm.h"
#include "Tool.h"
#include "ObjectTool.h"
#include "afxdialogex.h"



// ObjectTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(ObjectTool, CDialog)

ObjectTool::ObjectTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_OBJECTTOOL, pParent)
	, m_csObjName(_T(""))
	, m_bIsAni(false)
{

}

ObjectTool::~ObjectTool()
{
}

void ObjectTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csObjName);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_COMBO1, m_CBObjectType);
	DDX_Control(pDX, IDC_LIST2, m_ImageBox);
	DDX_Control(pDX, IDC_Preview2, m_PreView);
	DDX_Control(pDX, IDC_EDIT2, m_EditImageNum);
	DDX_Control(pDX, IDC_SPIN1, m_spKeyButton);
}

BEGIN_MESSAGE_MAP(ObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ObjectTool::OnBnClickedAddOBject)
	ON_BN_CLICKED(IDC_BUTTON5, &ObjectTool::OnBnClickedDeleteObject)
	ON_EN_CHANGE(IDC_EDIT1, &ObjectTool::OnEnChangeObejctName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ObjectTool::OnCbnSelchangeObject)
	ON_BN_CLICKED(IDOK, &ObjectTool::OnBnClickedOk)
	ON_BN_CLICKED(IDC_RADIO1, &ObjectTool::OnBnClickedAniOn)
	ON_BN_CLICKED(IDC_RADIO2, &ObjectTool::OnBnClickedAniOff)
	ON_LBN_SELCHANGE(IDC_LIST2, &ObjectTool::OnLbnSelchangeImageList)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &ObjectTool::OnDeltaposSpinButton)
END_MESSAGE_MAP()


// ObjectTool 메시지 처리기입니다.



#pragma region ObjectFun

void ObjectTool::OnEnChangeObejctName()
{
	UpdateData(TRUE);

}

void ObjectTool::OnBnClickedAddOBject()
{
	CString csTemp;
	m_CBObjectType.GetLBText(m_CBObjectType.GetCurSel(), csTemp);
	ConvertionCtoE(csTemp);

	m_mObjList.insert(make_pair(m_csObjName,m_eObjType));
	wstring cs = m_csObjName;
	//wcout << cs << m_eObjType << endl;

	m_ListBox.AddString(m_csObjName);
}	


void ObjectTool::OnBnClickedDeleteObject()
{	
	CString csTemp;
	m_ListBox.GetText(m_ListBox.GetCurSel(), csTemp);
	m_mObjList.erase(csTemp);
	//cout << m_mObjList.size() << endl;
	m_ListBox.DeleteString(m_ListBox.GetCurSel());
}

#pragma endregion



void ObjectTool::OnCbnSelchangeObject()
{
}

CString ObjectTool::ConvertionEtoC(OBJECT_TYPE eObjectType)
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
	case OBJECT_OBSTACLE:
		return L"Obstacle";
	default:
		return L"";
	}
}

void ObjectTool::ConvertionCtoE(CString csobjType)
{
	if (csobjType.Compare(L"Building")==0)
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

void ObjectTool::ReadData()
{
	ifstream fin;

	fin.open("../Data/ObjectList.txt");

	if (fin.fail())
		return;

	CString csTemp;
	char cTemp[32];
	while (!fin.eof())
	{
		fin.getline(cTemp, 32); // 공백을 포함한 문장 단위(개행 단위)로 읽어오기.
		csTemp = cTemp;
		fin.getline(cTemp, 32); // 공백을 포함한 문장 단위(개행 단위)로 읽어오기.
		m_mObjList.insert(make_pair(csTemp, (OBJECT_TYPE)atoi(cTemp)));
	}
	fin.close();
	for (auto object : m_mObjList)
	{ 
		if (object.first.Compare(L"") == 0)
			continue;
		m_ListBox.AddString(object.first);
	}
	//return	;
}

void ObjectTool::WriteData()
{
	
	ofstream fout;
	fout.open("../Data/ObjectList.txt", ios::trunc);
	if (fout.fail())
		return;
	//_TCHAR buf[32];
	for (auto Object : m_mObjList)
	{
		if (Object.first.Compare(L"")==0)
			continue;
		fout << CW2A(Object.first) << endl;
		fout << Object.second << endl;
	}

	fout.close();

}

void ObjectTool::DrawPreview()
{
	CString csItemName;

	m_ImageBox.GetText(m_ImageBox.GetCurSel(), csItemName);
	auto pathItr = m_ImagePath.find(csItemName);
	m_Obj = make_pair(pathItr->first.GetString(), pathItr->second);

	const TEX_INFO* pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(ConvertionEtoC(m_Obj.second).GetString(), m_Obj.first.GetString(), m_iImageKey);
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

	CDeviceMgr::GetInstance()->Render_End(m_PreView.m_hWnd);

}


BOOL ObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csObjectType[8]= { L"Building",L"Tree",L"Grass",L"Monster",L"NPC",L"Player",L"Trap",L"Obstacle" };
	for(int i=0;i<8;i++)
		m_CBObjectType.AddString(csObjectType[i]);


	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK_RETURN(pFrameWnd, FALSE);

	CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK_RETURN(pFormView, FALSE);

	m_EditImageNum.SetWindowTextW(L"0");
	m_spKeyButton.SetRange(0, 100);
	m_spKeyButton.SetPos(0);
	
	m_ImagePath = pFormView->m_ObjectPath;
	for (auto path : m_ImagePath)
	{
		m_ImageBox.AddString(path.first);

	}
	//TODO: 오브젝트 이름, 사진 포지션 연관지어서 구조체하나 짜서 myform 에서 연동가능하게 만들기

	ReadData();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void ObjectTool::OnBnClickedOk()
{
	WriteData();
	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pFormView);

	CDialog::OnOK();
}


void ObjectTool::OnBnClickedAniOn()
{
	m_bIsAni = true;
}


void ObjectTool::OnBnClickedAniOff()
{
	m_bIsAni = false;
}


void ObjectTool::OnLbnSelchangeImageList()
{
	m_EditImageNum.SetWindowTextW(L"0");
	m_spKeyButton.SetPos(0);
	m_iImageKey = 0;
	DrawPreview();

}


void ObjectTool::OnDeltaposSpinButton(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	m_iImageKey = pNMUpDown->iPos + pNMUpDown->iDelta;
	
	CString sVal;
	sVal.Format(_T("%d\n"), m_iImageKey);
	m_EditImageNum.SetWindowTextW(sVal);

	DrawPreview();

	*pResult = 0;
}
