// TileTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "TileTool.h"
#include "afxdialogex.h"
#include "DirectoryMgr.h"
#include "MainFrm.h"
#include "MyForm.h"


// TileTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(TileTool, CDialog)

TileTool::TileTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_TILETOOL, pParent)
{

}

TileTool::~TileTool()
{
}

void TileTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
}


BEGIN_MESSAGE_MAP(TileTool, CDialog)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDOK, &TileTool::OnBnClickedOk)
END_MESSAGE_MAP()


// TileTool �޽��� ó�����Դϴ�.


void TileTool::OnDropFiles(HDROP hDropInfo)
{

	TCHAR szFileName[MAX_STR] = L"";

	// �巡�� �� ��ӵ� ���� �� �ε����� �ش��ϴ� ������ �̸��� ���´�.
	//::DragQueryFile(hDropInfo, 1, szFileName, MAX_STR);
	//::AfxMessageBox(szFileName);

	// �ι�°���ڰ� -1�� �� �巡�� �� ��ӵ� ������ ��ü ������ ���´�.
	int iCount = ::DragQueryFile(hDropInfo, -1, nullptr, 0);

	CString strRelative = L"";
	CString strFileName = L"";

	for (int i = 0; i < iCount; ++i)
	{
		::DragQueryFile(hDropInfo, i, szFileName, MAX_STR);

		strRelative = CDirectoryMgr::ConvertRelativePath(szFileName);
		//cout << strRelative.GetString() << endl;
		strFileName = ::PathFindFileName(szFileName); // ���ϸ� ���� �Լ�.

		lstrcpy(szFileName, strFileName);
		::PathRemoveExtension(szFileName); // Ȯ���� ����.

		m_ListBox.AddString(strRelative);
		m_mTilePath.insert(make_pair(strFileName, strRelative));
	}

	//SettingHorizontalScrollSize();

	CDialog::OnDropFiles(hDropInfo);
}


void TileTool::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	CMainFrame* pFrameWnd = dynamic_cast<CMainFrame*>(::AfxGetApp()->GetMainWnd());
	NULL_CHECK(pFrameWnd);

	CMyForm* pFormView = dynamic_cast<CMyForm*>(pFrameWnd->m_SecondSplitter.GetPane(1, 0));
	NULL_CHECK(pFormView);

	//pFormView->m_mTilePath.insert(m_mTilePath.begin(), m_mTilePath.end());
	m_pGraphicDev = CDeviceMgr::GetInstance()->GetDevice();
	
	for (auto tilePath : m_mTilePath)
	{
		if(pFormView->m_mTilePath.find(tilePath.first) == pFormView->m_mTilePath.end())
			pFormView->m_ListBox.AddString(tilePath.first);
		pFormView->m_mTilePath.insert(tilePath);
		CTextureMgr::GetInstance()->LoadTexture(m_pGraphicDev, TEXTURE_SINGLE,
			tilePath.second.GetString(), tilePath.first.GetString());
	}

	CDialog::OnOK();
}
