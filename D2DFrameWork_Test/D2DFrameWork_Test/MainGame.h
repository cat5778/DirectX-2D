#pragma once
class CPlayer;
class CAstar;
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
	CPlayer*	m_pPlayer;
	CAstar*	m_Astar;
};

