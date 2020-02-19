#pragma once
#include "GameObject.h"

class CToolView;
class CTerrain :
	public CGameObject
{
	DECLARE_SINGLETON(CTerrain)
public:
	CTerrain();
	~CTerrain();

	// CGameObject을(를) 통해 상속됨
public:
	virtual void Release() override;
	virtual HRESULT Initialize() override;

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	
	POINT TileDrawConverstion(int _drawID);
public:
	vector<TILE_INFO*>	m_vecTile;
	CToolView*			m_pView;


};

