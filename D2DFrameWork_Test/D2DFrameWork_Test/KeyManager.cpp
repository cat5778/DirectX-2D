#include "stdafx.h"
#include "KeyManager.h"

CKeyManager* CKeyManager::m_pInstance=nullptr;

CKeyManager * CKeyManager::GetInstance()
{
	
	if(m_pInstance==nullptr)
		m_pInstance=new CKeyManager;
	return m_pInstance;
}

void CKeyManager::DestroyInstance()
{
	if (m_pInstance != nullptr)
		delete m_pInstance;

	m_pInstance = nullptr;

}

CKeyManager::CKeyManager()
	: m_dwKeyDown(0), m_dwKeyUp(0), m_dwCurKey(0)
{
}


CKeyManager::~CKeyManager()
{
}

void CKeyManager::Update()
{
	m_dwCurKey = 0;

	if (GetAsyncKeyState('W') & 0x8000)
		m_dwCurKey |= KEY_W;
	if (GetAsyncKeyState('S') & 0x8000)
		m_dwCurKey |= KEY_S;
	if (GetAsyncKeyState(0X41) & 0x8000)
		m_dwCurKey |= KEY_A;
	if (GetAsyncKeyState('D') & 0x8000)
		m_dwCurKey |= KEY_D;
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		m_dwCurKey |= KEY_SPACE;
	if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
		m_dwCurKey |= KEY_SHIFT;
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
		m_dwCurKey |= KEY_LBUTTON;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		m_dwCurKey |= KEY_RBUTTON;
	if (GetAsyncKeyState('R') & 0x8000)
		m_dwCurKey |= KEY_R;
	if (GetAsyncKeyState('F') & 0x8000)
		m_dwCurKey |= KEY_F;
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
		m_dwCurKey |= KEY_RETURN;
	if (GetAsyncKeyState('O') & 0x8000)
		m_dwCurKey |= KEY_O;
	if (GetAsyncKeyState('1') & 0x8000)
		m_dwCurKey |= KEY_1;
	if (GetAsyncKeyState('2') & 0x8000)
		m_dwCurKey |= KEY_2;
	if (GetAsyncKeyState('3') & 0x8000)
		m_dwCurKey |= KEY_3;
	if (GetAsyncKeyState('4') & 0x8000)
		m_dwCurKey |= KEY_4;
	if (GetAsyncKeyState('5') & 0x8000)
		m_dwCurKey |= KEY_5;

}



bool CKeyManager::KeyDown(DWORD dwKey)
{
	// ���� ������ ���� ���� ������ �� TRUE
	if (!(m_dwKeyDown & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyDown |= dwKey;
		return true;
	}
	// ���� ������ �ְ� ���� ������ �ʾ��� �� FALSE
	if ((m_dwKeyDown & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyDown ^= dwKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyUp(DWORD dwKey)
{
	// ���� ������ �ְ� ���� ������ �ʾ��� �� TRUE
	if ((m_dwKeyUp & dwKey) && !(m_dwCurKey & dwKey))
	{
		m_dwKeyUp ^= dwKey;
		return true;
	}
	// ���� ������ ���� ���� ������ �� FALSE
	if (!(m_dwKeyUp & dwKey) && (m_dwCurKey & dwKey))
	{
		m_dwKeyUp |= dwKey;
		return false;
	}

	return false;
}

bool CKeyManager::KeyPressing(DWORD dwKey)
{
	if (m_dwCurKey & dwKey)
		return true;

	return false;
}
