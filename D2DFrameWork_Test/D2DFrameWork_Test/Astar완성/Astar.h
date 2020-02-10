#pragma once
#include "MyGrid.h"
#include "Node.h"

class CAstar
{
public:
	CAstar();
	CAstar(Coordinate _StartPoint, Coordinate _EndPoint);
	~CAstar();


private:
	list<Coordinate*> FindPath(CMyGrid* Navi, Coordinate StartPoint, Coordinate EndPoint);
	list<CNode*>::iterator FindNextNode(list<CNode*>* pOpenNode); // ���³�� �� F���� ���� ���� ��� ã�Ƽ� ��ȯ
	list<CNode*>::iterator FindCoordNode(int x, int y, list<CNode*>* NodeList); // ��帮��Ʈ���� x,y ��ǥ�� ��带 ã�Ƽ� �ּҸ� ��ȯ. ������ end()��ȯ.
	void ExploreNode(CMyGrid* Navi, CNode* SNode, list<CNode*>* OpenNode, list<CNode*>* CloseNode, Coordinate EndPoint); // 8���� ��带 Ž���ϰ� ���� ��忡 �߰� �� �θ� ������ ������

public:
	void FindPath();
	Coordinate GetPos(int order); // order��° ����� ��ǥ�� �޾ƿ�
	list<Coordinate*> GetPath() { return path; } // ��θ� Coordinate* ����Ʈ�� ��°�� �޾ƿ�
	void SetFree(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ����
	void SetObstacle(int _x, int _y); // �ش� ��ǥ�� ��ֹ��� ��ġ
	void PrintPath(HDC hdc);
	void PrintMap(HDC hdc);
	void PrintNavi(HDC hdc);
	void SetStartPoint(Coordinate val);
	void SetEndPoint(Coordinate val);
private:
	CMyGrid Navi; // �� ����
	CMyGrid printNavi; // ��¿� �� ����(��α��� ���)

private:
	Coordinate StartPoint; // �������
	Coordinate EndPoint; // ��ǥ����
	list<Coordinate*> path; // ���
	list<Coordinate*>::iterator m_iter; // ��� iterator

};

