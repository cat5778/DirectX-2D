#pragma once


// CPreView ���Դϴ�.

class CPreView : public CView
{
	DECLARE_DYNCREATE(CPreView)

protected:
	CPreView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPreView();

public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	CDeviceMgr*	m_pDeviceMgr;

	virtual void OnInitialUpdate();
};


