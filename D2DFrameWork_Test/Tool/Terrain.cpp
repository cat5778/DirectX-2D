#include "stdafx.h"
#include "ToolView.h"
#include "Terrain.h"

IMPLEMENT_SINGLETON(CTerrain)
CTerrain::CTerrain()
{
	
}


CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Initialize()
{
	
	D3DXVECTOR3 vPos = {};
	D3DXVECTOR3 vSize = {};
	for (int i = 0; i < 1; i++)
	{
		for (int j = 0; j < 1; j++)
		{
			vPos = { (float)j*TILECX,(float)i*TILECY,0.f };
			vSize = { 1.f,1.f,0.f};
			PTILE_INFO tile = new TILE_INFO;
			tile->vPos = vPos;
			tile->vSize = vSize;
			tile->byDrawID = 1;
			tile->byOption = 0;

			m_vecTile.push_back(tile);
		}
	}
	return E_NOTIMPL;
}

void CTerrain::Release()
{
	for_each(m_vecTile.begin(), m_vecTile.end(), [](PTILE_INFO &ptile)
	{
		if (ptile != nullptr)
			delete ptile;
		ptile = nullptr;
	});

	m_vecTile.clear();

}

int CTerrain::Update()
{


	return S_OK;
}

void CTerrain::LateUpdate()
{


}

void CTerrain::Render()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(L"TileSet1");
		NULL_CHECK_CONTINUE(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x,
			m_vecTile[i]->vSize.y,
			m_vecTile[i]->vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x - m_pView->GetScrollPos(0),
			m_vecTile[i]->vPos.y - m_pView->GetScrollPos(1),
			m_vecTile[i]->vPos.z);
		
		
		POINT tID=TileDrawConverstion(m_vecTile[i]->byDrawID);

		RECT rt = { TILECX*tID.x , TILECY*tID.y , TILECX*tID.x+ TILECX , TILECY*tID.y+ TILECY };
		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, &rt,
			nullptr, nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));


		// 타일 인덱스 출력
		swprintf_s(szIndexNum, L"%d", i);
		m_pDeviceMgr->GetFont()->DrawText(m_pDeviceMgr->GetSprite(), szIndexNum,
			lstrlen(szIndexNum), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	
	}

}

POINT CTerrain::TileDrawConverstion(int _drawID)
{
	int id = _drawID;
	POINT tileID;
	tileID.y = id / 4;
	tileID.x = id % 4;
	return tileID;
}

