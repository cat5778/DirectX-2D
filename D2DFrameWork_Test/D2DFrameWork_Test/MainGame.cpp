#include "stdafx.h"
#include "MainGame.h"
CMainGame::CMainGame()
	:	m_pDevice(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);
	m_pDevice = CDeviceMgr::GetInstance();
	m_pDevice->InitDevice(MODE_WIN);


	
	return S_OK;
}

void CMainGame::Update()
{
	if (CKeyManager::GetInstance()->KeyUp(KEY_1))
	{
		POINT pt = {};
		GetCursorPos(&pt);
		ScreenToClient(g_hWnd, &pt);

		// ���� ���콺 ��ǥ�� �׻� Ŭ���̾�Ʈ ������ ��ǥ�̱⿡
		// ���콺�� ��ũ���� �ݴ�� �������־�� �Ѵ�.
		cout << "���콺 ������=" << pt.x << endl;
		cout << "���콺 ������=" << pt.y << endl;
		cout << "X=" << pt.x / TILECX << " Y=" << pt.y / TILECY << endl;
		//Coordinate pos = { pt.x / TILECX,pt.y / TILECY };
	}


}

void CMainGame::LateUpdate()
{
	//m_pPlayer->LateUpdate();
}

void CMainGame::Render()
{
	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	//m_pPlayer->Render(m_hDC);
	CDeviceMgr::GetInstance()->Render_Begin();


	CDeviceMgr::GetInstance()->Render_End();

}

void CMainGame::Release()
{
	CDeviceMgr::GetInstance()->DestroyInstance();
	
	
	ReleaseDC(g_hWnd, m_hDC);

}

CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
