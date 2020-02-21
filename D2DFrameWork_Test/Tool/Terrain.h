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

	// CGameObject��(��) ���� ��ӵ�
public:
	virtual void Release() override;
	virtual HRESULT Initialize() override;

public:
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
public:
	void MiniView();
	void TileChange(const D3DXVECTOR3& vPos, const BYTE& byDrawID, const BYTE& byOption = 0,const wstring &wsTexKey= L"TileSet1");
private:
	int	GetTileIndex(const D3DXVECTOR3& vPos);
	bool IsPicking(const D3DXVECTOR3& vPos, int iIndex);
	POINT TileDrawConverstion(int _drawID);
public:
	vector<TILE_INFO*>	m_vecTile;
	CToolView*			m_pView;


};

