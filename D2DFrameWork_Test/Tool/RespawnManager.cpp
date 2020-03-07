#include "stdafx.h"
#include "RespawnManager.h"
#include "ToolView.h"

IMPLEMENT_SINGLETON(CRespawnManager)
CRespawnManager::CRespawnManager()
{
	//
}


CRespawnManager::~CRespawnManager()
{
	auto itr = m_mObjects.begin();
	for (; itr != m_mObjects.end();)
	{
		if ((*itr).first != nullptr)
			delete (*itr).first;
		//itr->first = nullptr;
		itr = m_mObjects.erase(itr);
	}
}

bool CRespawnManager::CheckObject(const OBJ_INFO& objInfo ,D3DXVECTOR3 &vPos)
{
	const TEX_INFO* pTexInfo;
	bool bIsReady=true;
	if (objInfo.IsAni)
		pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(objInfo.wstrObjectKey, objInfo.wstrStateKey);
	else
		pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(objInfo.wstrObjectKey, objInfo.wstrStateKey, objInfo.ImageIDX);
	ConvertPos(objInfo, *pTexInfo, vPos);


	for_each(m_mObjects.begin(), m_mObjects.end(), [&bIsReady,vPos](pair<OBJ_INFO*, D3DXVECTOR3> fobj)
	{
		if (fobj.second == vPos)
		{
			bIsReady = false;
			cout << bIsReady << endl;
			return ;
		}

	});

	cout << bIsReady << endl;
	return bIsReady;
}

void CRespawnManager::Render()
{

	D3DXMATRIX matScale, matTrans;

	const TEX_INFO* pTexInfo = nullptr;
	float fCenterX = 0.f, fCenterY = 0.f;

	TCHAR szIndexNum[MIN_STR] = L"";
	for (auto Obj: m_mObjects)
	{

		if(Obj.first->IsAni)
			pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(Obj.first->wstrObjectKey, Obj.first->wstrStateKey);
		else
			pTexInfo = CTextureMgr::GetInstance()->GetTexInfo(Obj.first->wstrObjectKey, Obj.first->wstrStateKey, Obj.first->ImageIDX);
		NULL_CHECK_CONTINUE(pTexInfo);
		ConvertPos(*Obj.first, *pTexInfo, Obj.second);
	
		D3DXMatrixScaling(&matScale,
			1, 1, 1);
		D3DXMatrixTranslation(&matTrans,
			Obj.second.x - m_pView->GetScrollPos(0),
			Obj.second.y - m_pView->GetScrollPos(1),
			ZOrder(Obj.second.y));

		//POINT tID = TileDrawConverstion(m_vecTile[i]->byDrawID, pTexInfo->tImgInfo.Width / TILECX, pTexInfo->tImgInfo.Height / TILECY);
		fCenterX = TILECX*0.5f;
		fCenterY = TILECY*0.5f;
		//RECT rt = { TILECX*tID.x , TILECY*tID.y , TILECX*tID.x + TILECX , TILECY*tID.y + TILECY };
		CDeviceMgr::GetInstance()->GetSprite()->SetTransform(&(matScale * matTrans));
		CDeviceMgr::GetInstance()->GetSprite()->Draw(pTexInfo->pTexture, nullptr,
			&D3DXVECTOR3(fCenterX, fCenterY, 0.f), nullptr, D3DCOLOR_ARGB(255, 255, 255, 255));



		//// 타일 인덱스 출력
		//swprintf_s(szIndexNum, L"%d", (int)m_vecTile[i]->byOption);

		//m_pDeviceMgr->GetFont()->DrawText(m_pDeviceMgr->GetSprite(), szIndexNum,
		//	lstrlen(szIndexNum), nullptr, 0, D3DCOLOR_ARGB(255, 255, 255, 255));

	}
}

float  CRespawnManager::ZOrder(float _y)
{
	return 1-(_y *0.0001f);
}

void CRespawnManager::ConvertPos(const OBJ_INFO& objInfo,const TEX_INFO& pTexInfo,D3DXVECTOR3 &vPos)
{
	D3DXVECTOR3 Temp;
	int iW=0,iH=0;
	if (objInfo.wstrObjectName.find(L"TP") != wstring::npos)
	{
		iW = pTexInfo.tImgInfo.Width*0.6f;
		iH = pTexInfo.tImgInfo.Height*0.25f;
		vPos.x = (((int)vPos.x / iW) *iW);
		vPos.y = (((int)vPos.y / iH) *iH);
	}
	else if (objInfo.wstrObjectName.find(L"Horizontal_Wall") != wstring::npos)
	{
		iW = pTexInfo.tImgInfo.Width*0.9f;
		iH = pTexInfo.tImgInfo.Height;
		vPos.x = (((int)vPos.x / iW) *iW);
		vPos.y = (((int)vPos.y / iH) *iH);
	}
	else if (objInfo.wstrObjectName.find(L"Vertical_Wall") != wstring::npos)
	{
	iW = pTexInfo.tImgInfo.Width*0.75;
	iH = pTexInfo.tImgInfo.Height*0.8;
	vPos.x = (((int)vPos.x / iW) *iW);
	vPos.y = (((int)vPos.y / iH) *iH);
	}
	else if (objInfo.wstrObjectName.find(L"Wooden_Wall") != wstring::npos)
	{
		iW = pTexInfo.tImgInfo.Width;
		iH = pTexInfo.tImgInfo.Height*0.5;
		vPos.x = (((int)vPos.x / iW) *iW);
		vPos.y = (((int)vPos.y / iH) *iH);
	}
	else
	{
		iW = pTexInfo.tImgInfo.Width;
		iH = pTexInfo.tImgInfo.Height;
		vPos.x = (((int)vPos.x / iW) *iW);
		vPos.y = (((int)vPos.y / iH) *iH);
	}

}
