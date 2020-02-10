#include "stdafx.h"
#include "Player.h"


CPlayer::CPlayer()
	:m_fdgree(0.f)
{
	
}


CPlayer::~CPlayer()
{
	Release();
}

void CPlayer::Update()
{
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		m_fdgree += -1.f;
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		m_fdgree += 1.f;

	if (GetAsyncKeyState(VK_UP) & 0x8000)
		m_tInfo.vPos += m_tInfo.vDir ;
	
	m_fRadian = m_fdgree / 180 * 3.141592f;
	
	ZRotate();
	//m_tInfo.vPos = ;


}

void CPlayer::LateUpdate()
{


	m_tInfo.vDir.x = m_tInfo.vLook.x * cosf(D3DXToRadian(m_fdgree))//0*1
		- m_tInfo.vLook.y * -sinf(D3DXToRadian(m_fdgree));//-1*0
	m_tInfo.vDir.y = m_tInfo.vLook.x * -sinf(D3DXToRadian(m_fdgree))//0
		+ m_tInfo.vLook.y * cosf(D3DXToRadian(m_fdgree));//-1*0

	D3DXVec3Normalize(&m_tInfo.vDir, &m_tInfo.vDir);
}

void CPlayer::Render(HDC hDC)
{

	MoveToEx(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y, nullptr);
	LineTo(hDC, (int)m_vConvert[1].x, (int)m_vConvert[1].y);
	LineTo(hDC, (int)m_vConvert[2].x, (int)m_vConvert[2].y);
	LineTo(hDC, (int)m_vConvert[3].x, (int)m_vConvert[3].y);
	LineTo(hDC, (int)m_vConvert[0].x, (int)m_vConvert[0].y);
		
	for (int i = 0; i < 4; i+=3)
		Ellipse(hDC, int(m_vConvert[i].x - 10.f), int(m_vConvert[i].y - 10.f),
			int(m_vConvert[i].x + 10.f), int(m_vConvert[i].y + 10.f));
	
	MoveToEx(hDC, m_tInfo.vPos.x, m_tInfo.vPos.y, nullptr);
	LineTo(hDC, m_tInfo.vDir.x*100+ m_tInfo.vPos.x, m_tInfo.vDir.y*100+ m_tInfo.vPos.y);
	

}

HRESULT CPlayer::Initialize()
{
	m_tInfo.vPos = { 0.f, 0.f, 0.f }; // x, y, z
	m_tInfo.vDir = { 0.f ,0.f, 0.f }; // x, y, z
	m_tInfo.vLook = { 0.f, 1.f, 0.f };
	

	m_vOrigin[0] = { -50,50,0,1 };
	m_vOrigin[1] = { -50,-50,0,1};
	m_vOrigin[2] = { 50,-50,0,1 };
	m_vOrigin[3] = { 50,50,0,1 };
	m_Matrix = {1,0,0,0,
				0,1,0,0,
				0,0,1,0,
				0,0,0,1 };


	//for (int i = 0; i < 4; i++)
	//	D3DXVec4Transform(&m_vConvert[i], &m_vOrigin[i], &m_Matrix);
	
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float fVal=0.f;
			for (int k = 0; k < 4; k++)
				fVal += m_vOrigin[i][k]* m_Matrix.m[k][j];
		
			m_vConvert[i][j] = fVal;
		}
	}
	


	return S_OK;
}

void CPlayer::Release()
{
}

void CPlayer::ZRotate()
{
	m_RotMat = {
		cosf(m_fRadian),-sinf(m_fRadian),0,0,
		sinf(m_fRadian),cosf(m_fRadian),0,0,
		0,0,1,0,
		m_tInfo.vPos.x,m_tInfo.vPos.y,0,1};

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			float fVal = 0.f;
			for (int k = 0; k < 4; k++)
				fVal += m_vOrigin[i][k] * m_RotMat.m[k][j];

			m_vConvert[i][j] = fVal;
		}
	}

}

void CPlayer::Move()
{
}

CPlayer* CPlayer::Create()
{
	CPlayer* pInstance = new CPlayer;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
