#pragma once
/************************************************************************/
/* 这个文件主要是生成象棋的走法，查看某种走法是否合法。                          */
/************************************************************************/


#include <vector>
#include "global.h"
using namespace std;

class CMoveGenerater
{
public:
	struct MoveStep{
		CPoint from;
		CPoint to;
		int ChessID;
		MoveStep(CPoint nfrom=CPoint(0,0),CPoint nto=CPoint(0,0),int nChessID=0){from=nfrom,to=nto,ChessID=nChessID;}
	};
	CMoveGenerater(void);
	~CMoveGenerater(void);
	static bool IsValidMove(int Map[10][9],CPoint From,CPoint To);
	int AllValidMove(int Map[10][9],int ply,int size);
	vector<vector<MoveStep> > MoveList;
protected:
	//将产生的走法插入到M_MoveList中去！！！！！！！！！！
	int AddMove(CPoint from , CPoint to , int ply);
	//下面规定所有棋子的走法！！！！
	//将
	void GNT_JiangMove(int Map[10][9] ,CPoint pos , int ply);
	//帅
	void GNT_ShuaiMove(int Map[10][9] , CPoint pos , int ply);
	//红相
	void GNT_RXiangMove(int Map[10][9] , CPoint pos , int ply);
	//黑象
	void GNT_BXiangMove(int Map[10][9] , CPoint pos , int ply);
	//红士
	void GNT_RShiMove(int Map[10][9] , CPoint pos , int ply);
	//黑士
	void GNT_BShiMove(int Map[10][9] , CPoint pos , int ply);
	//红马
	void GNT_RMaMove(int Map[10][9] , CPoint pos , int ply);
	//黑马
	void GNT_BMaMove(int Map[10][9] , CPoint pos , int ply);
	//红車
	void GNT_RJuMove(int Map[10][9] , CPoint pos , int ply);
	//黑車
	void GNT_BJuMove(int Map[10][9] , CPoint pos , int ply);
	//红兵
	void GNT_RBingMove(int Map[10][9] ,CPoint pos , int ply);
	//黑卒
	void GNT_BZuMove(int Map[10][9] , CPoint pos , int ply);
	//红炮
	void GNT_RPaoMove(int Map[10][9] , CPoint pos , int ply);
	//黑炮
	void GNT_BPaoMove(int Map[10][9] , CPoint pos , int ply);
	int m_nMoveCount;
};

