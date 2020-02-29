#pragma once
#include "afxwin.h"


// ObjectTool 대화 상자입니다.

class ObjectTool : public CDialog
{
	DECLARE_DYNAMIC(ObjectTool)

public:
	ObjectTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ObjectTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBJECTTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedAddOBject();
	afx_msg void OnBnClickedDeleteObject();
	afx_msg void OnEnChangeObejctName();
	afx_msg void OnCbnSelchangeObject();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedAniOn();
	afx_msg void OnBnClickedAniOff();

private:
	CString ConvertionEtoC(OBJECT_TYPE eObjectType);
	void ConvertionCtoE(CString csobjType);
	void ReadData();
	void WriteData();
	//TODO: 이제 오브젝트툴에서 이미지 받아서 이름하고 연동시키기
	//주의 사항 Multi ,Single 하고 애니메이션 되는지안되는지 확인가능해야함
	
private	:
	CComboBox	m_CBObjectType;
	CString		m_csObjName;
	CListBox	m_ListBox;
	CListBox	m_ImageBox;
	CStatic		m_PreView;


public:
	map<CString, OBJECT_TYPE>	m_ImagePath;
	map<CString, OBJECT_TYPE>	m_mObjList;
	pair<CString, OBJECT_TYPE>  m_Obj;
	OBJECT_TYPE					m_eObjType;
	bool						m_bIsAni;

	afx_msg void OnLbnSelchangeImageList();
};
