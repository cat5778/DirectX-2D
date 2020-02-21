// PreView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "PreView.h"


// CPreView

IMPLEMENT_DYNCREATE(CPreView, CView)

CPreView::CPreView()
	:m_pDeviceMgr(CDeviceMgr::GetInstance())
{

}

CPreView::~CPreView()
{
}

BEGIN_MESSAGE_MAP(CPreView, CView)
END_MESSAGE_MAP()


// CPreView �׸����Դϴ�.

void CPreView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	m_pDeviceMgr->Render_Begin();


	m_pDeviceMgr->Render_End(m_hWnd);


}


// CPreView �����Դϴ�.

#ifdef _DEBUG
void CPreView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CPreView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPreView �޽��� ó�����Դϴ�.


void CPreView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.


}
