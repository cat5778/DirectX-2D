#pragma once
class CMyGrid
{
public:
	CMyGrid();
	~CMyGrid();
public:
	void Copy(CMyGrid* _map); // �Ű������� Map ���� �޾ƿ��� �Ű��������� �������簡 �Ͼ.
	void PrintMap(HDC hdc);



public:
	int sizeX, sizeY;
	int** map;

};

