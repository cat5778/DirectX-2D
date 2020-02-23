#pragma once

#include "TileTool.h"
#include "ObjectTool.h"
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
	afx_msg void OnBnClickedObjectTool();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnEnChangeTileOption();
	afx_msg void OnEnChangeTileNum();

public: // Tool Class
	TileTool		m_TileTool;
	ObjectTool		m_ObjTool;


public:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;

public:
	CListBox m_ListBox;
	CStatic m_Preview;
	CComboBox m_ComboBox;


public:
	map<CString, OBJECT_TYPE>m_mObjects;
	map<CString, CString> m_mTilePath;
	wstring m_Texname;
	BYTE m_byDrawID;
	BYTE m_byOption;



	afx_msg void OnCbnSelchange();
};


