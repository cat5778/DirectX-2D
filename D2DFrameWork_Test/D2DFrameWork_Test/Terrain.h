#pragma once
#include "GameObject.h"
class CTerrain :
	public CGameObject
{
public:
	CTerrain();
	~CTerrain();

	// CGameObject��(��) ���� ��ӵ�
	virtual HRESULT Initialize() override;
	virtual void Release() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
};

