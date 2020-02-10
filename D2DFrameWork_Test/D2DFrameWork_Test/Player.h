#pragma once
class CPlayer
{
private:
	CPlayer();

public:
	~CPlayer();

public:
	void Update();
	void LateUpdate();
	void Render(HDC hDC);

private:
	HRESULT Initialize();
	void Release();
	void ZRotate();
	void Move();
public:
	static CPlayer* Create();

private:
	INFO	m_tInfo;
	float	m_fSize;
	float	m_fRadian;
	float	m_fdgree;
	D3DXVECTOR4 m_vOrigin[4];
	D3DXVECTOR4 m_vConvert[4];
	D3DXMATRIX	m_Matrix;
	D3DXMATRIX	m_RotMat;
};

