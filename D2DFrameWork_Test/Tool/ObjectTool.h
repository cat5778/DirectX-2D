#pragma once
#include "afxwin.h"


// ObjectTool ��ȭ �����Դϴ�.

class ObjectTool : public CDialog
{
	DECLARE_DYNAMIC(ObjectTool)

public:
	ObjectTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ObjectTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedAddOBject();
	afx_msg void OnBnClickedDeleteObject();
	afx_msg void OnEnChangeObejctName();
	afx_msg void OnCbnSelchangeObject();
	afx_msg void OnBnClickedOk();
private:
	void ConvertionCtoE(CString csobjType);
	void ReadData();
	void WriteData();
private	:
	CComboBox	m_CBObjectType;
	CString		m_csObjName;
	CListBox	m_ListBox;

public:
	map<CString, OBJECT_TYPE>m_mObjList;
	OBJECT_TYPE m_eObjType;



	virtual BOOL OnInitDialog();
};
