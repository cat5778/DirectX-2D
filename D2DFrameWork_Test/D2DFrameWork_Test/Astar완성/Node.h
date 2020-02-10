#pragma once
class CNode
{
public:
	CNode();
	CNode(int _x, int _y, CNode* _pParent, Coordinate _EndPoint);
	~CNode();

	Coordinate point;
	Coordinate end;
	float F, G, H; // F = ���, G = ���� �Ÿ�, H = ���� �Ÿ�

	CNode* pParent;
};

