// Kill.h: interface for the CKill class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_KILL_H__854D8E1E_85CA_4B50_8125_D5A648B7C47F__INCLUDED_)
#define AFX_KILL_H__854D8E1E_85CA_4B50_8125_D5A648B7C47F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <Windows.h>
#include <deque>
using namespace std;

struct Point
{
	int x;
	int y;
};

class CKill  
{
public:
	CKill();
	virtual ~CKill();
	void OnKill();
	int baseaddress;
private:
	Point BFS(byte path[11][19],Point ptstart);
private:
	byte chessdata[11][19];//存放连连看棋子矩阵
};

#endif // !defined(AFX_KILL_H__854D8E1E_85CA_4B50_8125_D5A648B7C47F__INCLUDED_)
