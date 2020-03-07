#pragma once

typedef struct tagInfo
{
	D3DXVECTOR3 vPos;	// ��ġ���� (���п����� ��ġ���Ͷ�� ������ ����)
	D3DXVECTOR3 vDir;	// ���⺤��
	D3DXVECTOR3 vLook;	// ���⺤��

}INFO;
typedef struct tagRect
{
	D3DXVECTOR3  leftTop;
	D3DXVECTOR3  leftBottom;
	D3DXVECTOR3  rightTop;
	D3DXVECTOR3  rightBottom;
}vRect;
typedef struct tagTextureInfo
{
	LPDIRECT3DTEXTURE9 pTexture;
	D3DXIMAGE_INFO tImgInfo;
}TEX_INFO;

typedef struct Coordinate
{
	int x, y;
	void Set(int _x = 0, int _y = 0)
	{
		x = _x;
		y = _y;
	}
	Coordinate() {}
	Coordinate(int _x, int _y) :x(_x), y(_y) {}
}Coordinate;


typedef struct tagTileInfo
{
	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vSize;
	BYTE byDrawID;
	BYTE byOption;
	std::wstring wsTexKey;
}TILE_INFO,*PTILE_INFO;

typedef struct tagFrame
{
	float fCurFrame;
	float fMaxFrame;
}FRAME;

typedef struct tagUnit
{
	std::wstring wstrName;
	int iAtt;
	int iDef;
	int iJobIndex;
	int iItem;
}UNIT_DATA;
typedef struct tagPathInfo
{
	std::wstring wstrObjectKey;
	std::wstring wstrStateKey;
	std::wstring wstrRelative;
	int iImgCount;
}PATH_INFO;
typedef struct ObjectInfo
{
	std::wstring	wstrObjectName;
	std::wstring	wstrObjectKey;
	std::wstring	wstrStateKey;
	bool			IsAni;
	WORD			ImageIDX;
	OBJECT_TYPE		eObjectType;
	bool ObjectInfo::operator==(ObjectInfo& objInfo)
	{
		if (wstrObjectName.compare(objInfo.wstrObjectName) == 0)
			return true;
		return false;
	}
	ObjectInfo& ObjectInfo::operator=(const ObjectInfo& objinfo)
	{
		wstrObjectName = objinfo.wstrObjectName;
		wstrObjectKey = objinfo.wstrObjectKey;
		wstrStateKey = objinfo.wstrStateKey;
		IsAni = objinfo.IsAni;
		ImageIDX = objinfo.ImageIDX;
		eObjectType = objinfo.eObjectType;
		return *this;
	}

}OBJ_INFO;
typedef struct RespawnData
{
	D3DXVECTOR3 vPos;
	BYTE		byImageIDX;
}RESPAWN_DATA;