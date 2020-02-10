#include "stdafx.h"
#include "Astar.h"
#include "Node.h"

CAstar::CAstar()
{
}

CAstar::CAstar(Coordinate _StartPoint, Coordinate _EndPoint)
{
	StartPoint.x = _StartPoint.x;
	StartPoint.y = _StartPoint.y;
	EndPoint.x = _EndPoint.x; 
	EndPoint.y = _EndPoint.y;
	FindPath();
}


CAstar::~CAstar()
{
	m_iter = path.begin();
	for (; m_iter != path.end(); m_iter++)
	{
		delete *m_iter;
	}
}

list<Coordinate*> CAstar::FindPath(CMyGrid * Navi, Coordinate StartPoint, Coordinate EndPoint)
{
	// (��,��,��,��) 4���� �ð���� Ž�� �� ����� ���� (���,����,����,�»�) Ž��.	
	list<CNode*> OpenNode; // �������
	list<CNode*> CloseNode; // �������
	CNode* SNode; // ���õ� ���
	list<Coordinate*> path;

	OpenNode.push_back(new CNode(StartPoint.x, StartPoint.y, NULL, EndPoint)); // ���������� ������忡 �߰�

	list<CNode*>::iterator iter;

	// ���� ��尡 ��ų�(��������� ����==��) 
	// �������� ����(������忡�� ���� �߰�)�� ��� ��������
	// �� ������ �ݴ�� '���� ��忡 ������ �ְų� �������� �� ã�� ���' �ݺ�
	while ((OpenNode.end() != OpenNode.begin())
		&& (OpenNode.end() == FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode)))
	{
		iter = FindNextNode(&OpenNode); // ������� �� F���� ���� ���� ����� �ּҸ� ã�Ƽ� iter �� ����
		SNode = *iter; // ������� �� F���� ���� ���� ��带 SNode�� ����

					   // ���õ� SNode �ֺ��� 8���� ��� Ž��, ���� ������ �� �ִ� ���� ���� ��� ���̹Ƿ� ���� ���� �ּҸ� ����.
		ExploreNode(Navi, SNode, &OpenNode, &CloseNode, EndPoint);

		CloseNode.push_back(SNode); // ���� Ž���� ��带 ���� ��忡 �߰�
		OpenNode.erase(iter); // ���� ��忡 �߰��� ��带 ���� ��忡�� ����
	}

	if ((OpenNode.end() != OpenNode.begin())) // ���� ã�� ���
	{
		iter = FindCoordNode(EndPoint.x, EndPoint.y, &OpenNode); // �������� ��带 ã�Ƽ� iter�� ����
		for (SNode = *iter; SNode->pParent != NULL; SNode = SNode->pParent)  // �θ� NULL�� ������ path�� ��� ����
		{
			path.push_back(new Coordinate(SNode->point.x, SNode->point.y));
		}	path.push_back(new Coordinate(SNode->point.x, SNode->point.y)); // �θ� NULL�� ����� path���� ����(��� ����)

		path.reverse(); // �������������� �������� �Է������Ƿ� �ٽ� �������� ������ ��������� ù ��°�� �ǵ��� ��.

						// ���� ã�� ��� �����Ҵ� ����
		iter = OpenNode.begin();
		for (; iter != OpenNode.end(); iter++)
		{
			delete *iter; // ���� ��� �����Ҵ� ����
		}
		iter = CloseNode.begin();
		for (; iter != CloseNode.end(); iter++)
		{
			delete *iter; // ���� ��� �����Ҵ� ����
		}

		return path; // ���� ã�� ��� ����
	}

	// ���� ã�� ���� ��� �����Ҵ� ����
	iter = CloseNode.begin();
	for (; iter != CloseNode.end(); iter++)
	{
		delete *iter; // ���� ��� �����Ҵ� ����
	}
	return path; // ���� ã�� ���� ��� ����
}

list<CNode*>::iterator CAstar::FindNextNode(list<CNode*>* pOpenNode)
{
	list<CNode*>::iterator iter = (*pOpenNode).begin();

	int minValue = 2000000000; // ���� ���� ���� ���� ����
	int order = 0; // �������� ����� iterator�� ������Ѱ�

	for (int i = 1; iter != (*pOpenNode).end(); i++, iter++)
	{
		if ((*iter)->F <= minValue) // ����� ������� 
		{
			minValue = (*iter)->F;
			order = i;
		}
	}

	iter = (*pOpenNode).begin();
	for (int i = 1; i < order; i++) 
	{
		iter++;
	}

	return iter;
}

list<CNode*>::iterator CAstar::FindCoordNode(int x, int y, list<CNode*>* NodeList)
{
	list<CNode*>::iterator iter = NodeList->begin();

	for (int i = 1; iter != NodeList->end(); i++, iter++)
	{
		if ((*iter)->point.x == x && (*iter)->point.y == y)
		{
			return iter;
		}
	}

	return NodeList->end();
}

void CAstar::ExploreNode(CMyGrid * Navi, CNode * SNode, list<CNode*>* OpenNode, list<CNode*>* CloseNode, Coordinate EndPoint)
{
	bool up = true, right = true, down = true, left = true; // �� ����� ���� �밢�� ���� Ž�� ���θ� ����. true == ��ֹ� ����, false == ����
	list<CNode*>::iterator iter;
	POINT point;

	// '��' ���� Ž��
	point = { SNode->point.x - 1 ,SNode->point.y };
	if (SNode->point.x > 0 && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		up = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point = { SNode->point.x,SNode->point.y + 1 };
	if (SNode->point.y < (Navi->sizeY - 1) && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		right = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point = { SNode->point.x + 1,SNode->point.y };
	if (SNode->point.x < (Navi->sizeX - 1) && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		down = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
		}
	}
	// '��' ���� Ž��
	point = { SNode->point.x,SNode->point.y - 1 };
	if (SNode->point.y > 0 && Navi->map[point.x][point.y] == 0) // '��' ���⿡ ���� �����ϰ� ��ֹ��� ���� ���
	{
		// ��ֹ��� ���� ��쿡 �ش��ϹǷ� ��ֹ� false ����
		left = false;

		// �̹� ���� ��忡 �ִ� ���
		if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
		{
			iter = FindCoordNode(point.x, point.y, OpenNode);
			if ((*iter)->G > (SNode->G + 10)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
			{
				(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
			}
		}

		// ���� ��忡 �ִ� ���
		else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
		{
		}

		// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
		// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
		else
		{
			OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
		}
	}

	// '���' ���� Ž��
	//point = { SNode->point.x - 1,SNode->point.y + 1 };
	//if (SNode->point.x > 0 &&
	//	SNode->point.y < (Navi->sizeY - 1) &&
	//	Navi->map[point.x][point.y] == 0 &&
	//	up == false && right == false) // '���' ���⿡ ���� �����ϰ� ��ֹ��� ������, ������ ����⿡�� ��ֹ��� ���� ���
	//{
	//	// �̹� ���� ��忡 �ִ� ���
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
	//		{
	//			(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
	//		}
	//	}

	//	// ���� ��忡 �ִ� ���
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
	//	// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
	//	else
	//	{
	//		OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '����' ���� Ž��
	//point = { SNode->point.x + 1,SNode->point.y + 1 };
	//if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y < (Navi->sizeY - 1) &&
	//	Navi->map[point.x][point.y] == 0 && right == false && down == false)
	//	// '����' ���⿡ ���� �����ϰ� ��ֹ��� ������, ������ �Ϲ��⿡�� ��ֹ��� ���� ���
	//{
	//	// �̹� ���� ��忡 �ִ� ���
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
	//		{
	//			(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
	//		}
	//	}

	//	// ���� ��忡 �ִ� ���
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
	//	// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
	//	else
	//	{
	//		OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '����' ���� Ž��
	//point = { SNode->point.x + 1,SNode->point.y - 1 };
	//if (SNode->point.x < (Navi->sizeX - 1) && SNode->point.y > 0 && Navi->map[point.x][point.y] == 0 &&
	//	left == false && down == false) // '����' ���⿡ ���� �����ϰ� ��ֹ��� ������, �¹���� �Ϲ��⿡�� ��ֹ��� ���� ���
	//{
	//	// �̹� ���� ��忡 �ִ� ���
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
	//		{
	//			(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
	//		}
	//	}

	//	// ���� ��忡 �ִ� ���
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
	//	// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
	//	else
	//	{
	//		OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
	//	}
	//}
	//// '�»�' ���� Ž��
	//point={SNode->point.x - 1,SNode->point.y - 1};
	//if (SNode->point.x > 0 && SNode->point.y > 0 && Navi->map[point.x][point.y] == 0 &&
	//	left == false && up == false) // '�»�' ���⿡ ���� �����ϰ� ��ֹ��� ������, �¹���� ����⿡�� ��ֹ��� ���� ���
	//{
	//	// �̹� ���� ��忡 �ִ� ���
	//	if (OpenNode->end() != FindCoordNode(point.x, point.y, OpenNode))
	//	{
	//		iter = FindCoordNode(point.x, point.y, OpenNode);
	//		if ((*iter)->G > (SNode->G + 14)) // ���� �θ� ���ؼ� ���� ���� ��뺸�� ���� ��带 ���ؼ� ���� �� ����� �� ������ ��� 
	//		{
	//			(*iter)->pParent = SNode; // ���� ��带 �θ�� �ٲ�
	//		}
	//	}

	//	// ���� ��忡 �ִ� ���
	//	else if (CloseNode->end() != FindCoordNode(point.x, point.y, CloseNode))
	//	{
	//	}

	//	// ����⿡ ��ֹ��� ���� ���� ��� �� ���� ��忡 �߰��Ǿ����� ���� ���
	//	// ����� ��带 ���� ��忡 �߰�, �θ�� ���� Ž�� ���� ����.
	//	else
	//	{
	//		OpenNode->push_back(new CNode(point.x, point.y, SNode, EndPoint));
	//	}
	//}
}

void CAstar::FindPath()
{
	path = FindPath(&Navi, StartPoint, EndPoint);
	m_iter = path.begin(); // iter �� ������� �����ֱ�
}

Coordinate CAstar::GetPos(int order)
{
	Coordinate pos;
	for (int i = 1; i < order; i++)
	{
		m_iter++;
	}
	pos.x = (*m_iter)->x;
	pos.y = (*m_iter)->y;
	m_iter = path.begin();
	return pos;
}

void CAstar::SetFree(int _x, int _y)
{
	Navi.map[_x][_y] = 0;
}

void CAstar::SetObstacle(int _x, int _y)
{
	Navi.map[_x][_y] = 1;
}

void CAstar::PrintPath(HDC hdc)
{
	for (int i = 0; m_iter != path.end(); m_iter++)
	{
		//cout << (*m_iter)->x << (*m_iter)->y << endl;
		Rectangle(hdc,
			(*m_iter)->x*TILECX - TILECX*0.5 + TILECX*0.5,
			(*m_iter)->y *TILECX - TILECY*0.5 + TILECY*0.5,
			(*m_iter)->x*TILECX + TILECX*0.5 + TILECX*0.5,
			(*m_iter)->y *TILECX + TILECY*0.5 + TILECY*0.5);

	}
	m_iter = path.begin(); // iter �� ������� �����ֱ�
}

void CAstar::PrintMap(HDC hdc)
{
	Navi.PrintMap(hdc);
}

void CAstar::PrintNavi(HDC hdc)
{
	printNavi.Copy(&Navi);

	for (int i = 0; m_iter != path.end(); m_iter++) // �ʿ��� ��ο� �ش��ϴ� ���� 7�� ǥ��
	{
		printNavi.map[(*m_iter)->x][(*m_iter)->y] = 7;
	}
	m_iter = path.begin(); // iter �� ������� �����ֱ�

	printNavi.PrintMap(hdc);
}

void CAstar::SetStartPoint(Coordinate val)
{
	StartPoint.x = val.x;
	StartPoint.y = val.y;
}

void CAstar::SetEndPoint(Coordinate val)
{
	EndPoint.x = val.x;
	EndPoint.y = val.y;
	FindPath();
}
