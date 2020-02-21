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
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vPos = { (float)j*TILECX+ TILECX*0.5f,(float)i*TILECY+ TILECY*0.5f,0.f };
			vSize = { 1.f,1.f,0.f};
			PTILE_INFO tile = new TILE_INFO;
			tile->vPos = vPos;
			tile->vSize = vSize;
			tile->byDrawID = 0;
			tile->byOption = 0;
			tile->wsTexKey = L"TileSet1";
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
		pTexInfo = m_pTextureMgr->GetTexInfo(m_vecTile[i]->wsTexKey);
		NULL_CHECK_CONTINUE(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x,
			m_vecTile[i]->vSize.y,
			m_vecTile[i]->vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x  - m_pView->GetScrollPos(0),
			m_vecTile[i]->vPos.y  - m_pView->GetScrollPos(1),
			m_vecTile[i]->vPos.z);
		
		POINT tID=TileDrawConverstion(m_vecTile[i]->byDrawID);
		fCenterX = TILECX*0.5f;
		fCenterY = TILECY*0.5f;
		RECT rt = { TILECX*tID.x , TILECY*tID.y , TILECX*tID.x+ TILECX , TILECY*tID.y+ TILECY };
		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, &rt,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));
		


		// 타일 인덱스 출력
		swprintf_s(szIndexNum, L"%d", i);

		m_pDeviceMgr->GetFont()->DrawText(m_pDeviceMgr->GetSprite(), szIndexNum,
			lstrlen(szIndexNum), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	}

}

void CTerrain::MiniView()
{
	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";

	for (size_t i = 0; i < m_vecTile.size(); ++i)
	{
		pTexInfo = m_pTextureMgr->GetTexInfo(m_vecTile[i]->wsTexKey);
		NULL_CHECK_CONTINUE(pTexInfo);

		D3DXMatrixScaling(&matScale,
			m_vecTile[i]->vSize.x*0.25f,
			m_vecTile[i]->vSize.y*0.25f,
			m_vecTile[i]->vSize.z);
		D3DXMatrixTranslation(&matTrans,
			m_vecTile[i]->vPos.x*0.25f - m_pView->GetScrollPos(0),
			m_vecTile[i]->vPos.y*0.25f - m_pView->GetScrollPos(1),
			m_vecTile[i]->vPos.z);

		POINT tID = TileDrawConverstion(m_vecTile[i]->byDrawID);
		fCenterX = TILECX*0.5f;
		fCenterY = TILECY*0.5f;
		RECT rt = { TILECX*tID.x , TILECY*tID.y , TILECX*tID.x + TILECX , TILECY*tID.y + TILECY };
		m_pDeviceMgr->GetSprite()->SetTransform(&(matScale * matTrans));
		m_pDeviceMgr->GetSprite()->Draw(pTexInfo->pTexture, &rt,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

void CTerrain::TileChange(const D3DXVECTOR3 & vPos, const BYTE & byDrawID, const BYTE & byOption, const wstring& wsTexKey)
{
	int iIndex = GetTileIndex(vPos);

	if (-1 == iIndex)
		return;

	m_vecTile[iIndex]->byDrawID = byDrawID;
	m_vecTile[iIndex]->byOption = byOption;
	m_vecTile[iIndex]->wsTexKey=wsTexKey;

}
int CTerrain::GetTileIndex(const D3DXVECTOR3& vPos)
{
	for (int i = 0; i < (int)m_vecTile.size(); ++i)
	{
		if (IsPicking(vPos, i))
			return i;
	}

	return -1;
}
bool CTerrain::IsPicking(const D3DXVECTOR3 & vPos, int iIndex)
{
	// 내적을 이용한 방식 (데카르트 기준)
	// 마름모 꼭지점 설정 12시, 3시, 6시, 9시 순서
	D3DXVECTOR3 vPoint[4] =
	{
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x + TILECX * 0.5f, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y + TILECY * 0.5f, 0.f),
		D3DXVECTOR3(m_vecTile[iIndex]->vPos.x - TILECX * 0.5f, m_vecTile[iIndex]->vPos.y - TILECY * 0.5f, 0.f)
	};

	// 각 꼭지점으로부터 시계방향으로 방향벡터들을 구함.
	D3DXVECTOR3 vDir[4] =
	{
		vPoint[1] - vPoint[0],
		vPoint[2] - vPoint[1],
		vPoint[3] - vPoint[2],
		vPoint[0] - vPoint[3],
	};

	// 위에서 구한 방향벡터들의 각 법선벡터들을 구한다.
	D3DXVECTOR3 vNormal[4] = {};

	for (int i = 0; i < 4; ++i)
		D3DXVec3Cross(&vNormal[i], &D3DXVECTOR3(0.f, 0.f, -1.f), &vDir[i]);

	// 각 꼭지점에서부터 마우스위치로의 방향벡터를 구한다.
	D3DXVECTOR3 vMouseDir[4] =
	{
		vPos - vPoint[0],
		vPos - vPoint[1],
		vPos - vPoint[2],
		vPos - vPoint[3]
	};

	// vMouseDir과 vNormal을 각각 내적해서 모두 둔각(음수)이 나오면 TRUE!
	for (int i = 0; i < 4; ++i)
	{
		if (0 < D3DXVec3Dot(&vNormal[i], &vMouseDir[i]))
			return false;
	}

	return true;
}

POINT CTerrain::TileDrawConverstion(int _drawID)
{
	int id = _drawID;
	POINT tileID;
	tileID.y = id / 4;
	tileID.x = id % 4;
	return tileID;
}

