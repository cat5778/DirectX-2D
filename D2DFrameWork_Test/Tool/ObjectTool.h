#pragma once
#include "afxwin.h"
#include "afxcmn.h"


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
	afx_msg void OnLbnSelchangeImageList();

private:
	CString ConvertionEtoC(OBJECT_TYPE eObjectType);
	void ConvertionCtoE(CString csobjType);
	void ReadData();
	void WriteData();
	void DrawPreview();
	//TODO: ���� ������Ʈ������ �̹��� �޾Ƽ� �̸��ϰ� ������Ű��
	//���� ���� Multi ,Single �ϰ� �ִϸ��̼� �Ǵ����ȵǴ��� Ȯ�ΰ����ؾ���
	
private	:
	CComboBox	m_CBObjectType;
	CString		m_csObjName;
	CListBox	m_ListBox;
	CListBox	m_ImageBox;
	CStatic		m_PreView;
	CEdit m_EditImageNum;
	CSpinButtonCtrl m_spKeyButton;


public:
	map<CString, OBJECT_TYPE>	m_ImagePath;
	map<CString, OBJECT_TYPE>	m_mObjList;
	pair<CString, OBJECT_TYPE>  m_Obj;
	OBJECT_TYPE					m_eObjType;
	bool						m_bIsAni;
	int							m_iImageKey;
	afx_msg void OnDeltaposSpinButton(NMHDR *pNMHDR, LRESULT *pResult);
};
