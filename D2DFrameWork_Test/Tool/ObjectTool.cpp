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
}

BEGIN_MESSAGE_MAP(ObjectTool, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &ObjectTool::OnBnClickedAddOBject)
	ON_BN_CLICKED(IDC_BUTTON5, &ObjectTool::OnBnClickedDeleteObject)
	ON_EN_CHANGE(IDC_EDIT1, &ObjectTool::OnEnChangeObejctName)
	ON_CBN_SELCHANGE(IDC_COMBO1, &ObjectTool::OnCbnSelchangeObject)
	ON_BN_CLICKED(IDOK, &ObjectTool::OnBnClickedOk)
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
	wcout << cs << m_eObjType << endl;
	m_ListBox.AddString(m_csObjName);
}	


void ObjectTool::OnBnClickedDeleteObject()
{	
	CString csTemp;
	m_ListBox.GetText(m_ListBox.GetCurSel(), csTemp);
	m_mObjList.erase(csTemp);
	cout << m_mObjList.size() << endl;
	m_ListBox.DeleteString(m_ListBox.GetCurSel());
}

#pragma endregion



void ObjectTool::OnCbnSelchangeObject()
{
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


BOOL ObjectTool::OnInitDialog()
{
	CDialog::OnInitDialog();
	CString csObjectType[6]= { L"Building",L"Tree",L"Grass",L"Monster",L"NPC",L"Player" };
	for(int i=0;i<6;i++)
		m_CBObjectType.AddString(csObjectType[i]);

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
	pFormView->m_mObjects = m_mObjList;



	CDialog::OnOK();
}
