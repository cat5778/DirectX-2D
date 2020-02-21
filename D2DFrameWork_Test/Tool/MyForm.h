#pragma once

#include "TileTool.h"
#include "afxwin.h"
// CMyForm �� ���Դϴ�.
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
	//afx_msg
	afx_msg void OnBnClickedTileButton();
	afx_msg void OnEnChangeTileNum();
	afx_msg void OnEnChangeTileOption();
	afx_msg void OnLbnSelchangeList();

public:
	TileTool		m_TileTool;

public:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;

public:
	CListBox m_ListBox;
	CStatic m_Preview;


public:
	map<CString, CString> m_mTilePath;
	wstring m_Texname;
	BYTE m_byDrawID;
	BYTE m_byOption;



};


