#pragma once
#include "afxwin.h"


// CPathTool ��ȭ �����Դϴ�.

class CPathTool : public CDialog
{
	DECLARE_DYNAMIC(CPathTool)

public:
	CPathTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPathTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PATHTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

public:
	void SettingHorizontalScrollSize();
public:
	CListBox m_ListBox;



public: // User Variables
	list<PATH_INFO*>	m_PathInfoList;
};
