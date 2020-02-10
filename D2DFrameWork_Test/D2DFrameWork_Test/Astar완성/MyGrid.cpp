#include "stdafx.h"
#include "MyGrid.h"


CMyGrid::CMyGrid()
{
	// ���� ũ�⸦ �ҷ���
	char csizeX[4], csizeY[4];
	GetPrivateProfileStringA("MAP", "sizeX", "", csizeX, sizeof(csizeX) - 1, "../Data/Map.txt");
	GetPrivateProfileStringA("MAP", "sizeY", "", csizeY, sizeof(csizeY) - 1, "../Data/Map.txt");
	sizeX = atoi(csizeX); 
	sizeY = atoi(csizeY);

	// �� ũ�� �Ҵ�
	map = new int*[sizeX]; // �� �Ҵ�
	for (int i = 0; i < sizeX; i++) // �� �Ҵ�
	{
		map[i] = new int[sizeY];
	}

	FILE* stream = fopen("../Data/Map.txt", "rb"); // ���� �ڷḦ �ҷ��� 0=������ �� �ִ� �� , 1=��ֹ�
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			fscanf(stream, "%d", &map[i][j]);
			
		}
	}
	fclose(stream);
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
	//sizeX = WINCX / TILECX;
	//sizeY = WINCY / TILECY;
	//map = new int*[sizeX]; // �� �Ҵ�
	//for (int i = 0; i < sizeX; i++) // �� �Ҵ�
	//{
	//	map[i] = new int[sizeY]();
	//}

}


CMyGrid::~CMyGrid()
{
	for (int i = 0; i < sizeX; i++)
	{
		delete[] map[i]; // ���� �� �����Ҵ� ����, ���� ���� ������ŭ �����Ҵ� �Ǿ����Ƿ� sizeX��ŭ �ݺ�
	}
	delete[] map; // ���� �� �����Ҵ� ����

}

void CMyGrid::Copy(CMyGrid * _map)
{
	sizeX = _map->sizeX;
	sizeY = _map->sizeY;

	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			map[i][j] = _map->map[i][j];
		}
	}

}

void CMyGrid::PrintMap(HDC hdc)
{
	for (int i = 0; i < sizeX; i++)
	{
		for (int j = 0; j < sizeY; j++)
		{
			HBRUSH brush;
			HBRUSH oldBrush;
			switch (map[i][j])
			{
			case 0:
			{
				brush = CreateSolidBrush(RGB(255, 255, 255));
				oldBrush = (HBRUSH)SelectObject(hdc, brush);
			}
			break;
			case 1:
			{
				brush = CreateSolidBrush(RGB(0, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, brush);
			}
			break;

			default:
			{
				brush = CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, brush);
			}
			break;
			}

			Rectangle(hdc,
				j*TILECX - TILECX*0.5 + TILECX*0.5,
				i*TILECX - TILECY*0.5 + TILECY*0.5,
				j*TILECX + TILECX*0.5 + TILECX*0.5,
				i*TILECX + TILECY*0.5 + TILECY*0.5);
			SelectObject(hdc, oldBrush);
			DeleteObject(brush);

			//printf("%d ", map[i][j]);
		}
		//printf("\n");
	}
}


