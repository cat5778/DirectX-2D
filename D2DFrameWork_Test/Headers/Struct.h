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