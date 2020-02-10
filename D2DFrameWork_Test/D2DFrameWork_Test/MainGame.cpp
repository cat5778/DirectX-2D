#include "stdafx.h"
#include "MainGame.h"
#include "Player.h"
CMainGame::CMainGame()
	: m_pPlayer(nullptr)
{
}


CMainGame::~CMainGame()
{
	Release();
}

HRESULT CMainGame::Initialize()
{
	m_hDC = GetDC(g_hWnd);

	//m_pPlayer = CPlayer::Create();
	//NULL_CHECK_MSG_RETURN(m_pPlayer, L"Player Create Failed", E_FAIL);

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

	//m_pPlayer->Update();
}

void CMainGame::LateUpdate()
{
	//m_pPlayer->LateUpdate();
}

void CMainGame::Render()
{
	//Rectangle(m_hDC, 0, 0, WINCX, WINCY);
	//m_pPlayer->Render(m_hDC);


}

void CMainGame::Release()
{
	ReleaseDC(g_hWnd, m_hDC);

	SafeDelete(m_pPlayer);
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
