#pragma once
/************************************************************************/
/* ����ļ���Ҫ������������߷����鿴ĳ���߷��Ƿ�Ϸ���                          */
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
	//���������߷����뵽M_MoveList��ȥ��������������������
	int AddMove(CPoint from , CPoint to , int ply);
	//����涨�������ӵ��߷���������
	//��
	void GNT_JiangMove(int Map[10][9] ,CPoint pos , int ply);
	//˧
	void GNT_ShuaiMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_RXiangMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_BXiangMove(int Map[10][9] , CPoint pos , int ply);
	//��ʿ
	void GNT_RShiMove(int Map[10][9] , CPoint pos , int ply);
	//��ʿ
	void GNT_BShiMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_RMaMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_BMaMove(int Map[10][9] , CPoint pos , int ply);
	//��܇
	void GNT_RJuMove(int Map[10][9] , CPoint pos , int ply);
	//��܇
	void GNT_BJuMove(int Map[10][9] , CPoint pos , int ply);
	//���
	void GNT_RBingMove(int Map[10][9] ,CPoint pos , int ply);
	//����
	void GNT_BZuMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_RPaoMove(int Map[10][9] , CPoint pos , int ply);
	//����
	void GNT_BPaoMove(int Map[10][9] , CPoint pos , int ply);
	int m_nMoveCount;
};

