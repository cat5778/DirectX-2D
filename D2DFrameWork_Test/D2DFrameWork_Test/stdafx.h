// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#ifdef UNICODE
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#else
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.
// Windows ��� ����:
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <deque>
#include <stack>
#include <cmath>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#include <d3dx9.h>
#include <d3dx9math.h>
#pragma comment(lib, "d3dx9.lib")

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "Define.h"
#include "Extern.h"
#include "Struct.h"
#include "Function.h"
#include "tinyxml2.h"
using namespace std;

//manager
#include "KeyManager.h"