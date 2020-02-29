#pragma once

#include "TileTool.h"
#include "ObjectTool.h"
#include "PathTool.h"
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
	afx_msg void OnBnClickedObjectTool();
	afx_msg void OnLbnSelchangeList();
	afx_msg void OnEnChangeTileOption();
	afx_msg void OnEnChangeTileNum();
	afx_msg void OnCbnSelchange();
private:
	void ConvertionCtoE(CString csobjType);

	CString ConvertionEtoC(OBJECT_TYPE eObjectType);
	HRESULT ReadData(wstring wstrFilePath);

public: // Tool Class
	TileTool		m_TileTool;
	ObjectTool		m_ObjTool;
	CPathTool		m_PathTool;

public:
	CDeviceMgr*		m_pDeviceMgr;
	CTextureMgr*	m_pTextureMgr;
public:
	CListBox m_ListBox;
	CStatic m_Preview;
	CComboBox m_ComboBox;
	int m_iOldCount;

public:
	map<CString, OBJECT_TYPE> m_ObjectPath;
	map<CString, CString> m_mTilePath;
	wstring m_Texname;
	BYTE m_byDrawID;
	BYTE m_byOption;
	OBJECT_TYPE m_eObjType;
	pair<CString, CString> m_TilePath;

	afx_msg void OnBnClickedObject();
};


