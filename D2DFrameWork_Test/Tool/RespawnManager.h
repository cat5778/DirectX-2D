#pragma once
class CToolView;

class CRespawnManager
{
	DECLARE_SINGLETON(CRespawnManager)
public:
	CRespawnManager();
	~CRespawnManager();
	
public:
	bool CheckObject(const OBJ_INFO& objInfo , D3DXVECTOR3 &vPos);
	void Render();
	float ZOrder(float _y);
	void ConvertPos(const OBJ_INFO& objInfo,const TEX_INFO& pTexInfo ,D3DXVECTOR3 &vPos);
public:
	multimap<OBJ_INFO*, D3DXVECTOR3>	m_mObjects;
	CToolView*							m_pView;

};

