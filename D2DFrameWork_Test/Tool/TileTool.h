#pragma once
#include "afxwin.h"


// TileTool ��ȭ �����Դϴ�.

class TileTool : public CDialog
{
	DECLARE_DYNAMIC(TileTool)

public:
	TileTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~TileTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TILETOOL };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();

public:
	CListBox m_ListBox;
	map<CString, CString> m_mTilePath;
	LPDIRECT3DDEVICE9 m_pGraphicDev;
};
