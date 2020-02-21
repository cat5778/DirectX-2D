#pragma once

#include "TileTool.h"
#include "afxwin.h"
// CMyForm 폼 뷰입니다.
class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // 동적 만들기에 사용되는 protected 생성자입니다.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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


