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