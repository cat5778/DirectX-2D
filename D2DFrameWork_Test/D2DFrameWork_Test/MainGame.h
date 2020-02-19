#pragma once
class CMainGame
{
private:
	CMainGame();

public:
	~CMainGame();

public:	
	void Update();
	void LateUpdate();
	void Render();

private:
	HRESULT Initialize();
	void Release();

public:
	static CMainGame* Create();
private:
	HDC m_hDC;
	CDeviceMgr*		m_pDevice;

};

