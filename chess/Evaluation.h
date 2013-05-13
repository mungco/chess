#pragma once
#include "global.h"
#include <vector>

using namespace std;

#define BASEVALUE_PAWN 100
#define BASEVALUE_BISHOP 250
#define BASEVALUE_ELEPHANT 250
#define BASEVALUE_CAR 500
#define BASEVALUE_HORSE 350
#define BASEVALUE_CANON 350
#define BASEVALUE_KING 10000

#define FLEXIBILITY_PAWN 15
#define FLEXIBILITY_BISHOP 1
#define FLEXIBILITY_ELEPHANT 1
#define FLEXIBILITY_CAR 6
#define FLEXIBILITY_HORSE 12
#define FLEXIBILITY_CANON 6
#define FLEXIBILITY_KING 0

class CEvaluation
{
public:
	CEvaluation(void);
	~CEvaluation(void);
	virtual int Evaluate(int Map[10][9],bool bIsRedTurn);
protected:
	int GetRelatePiece(int Map[10][9],CPoint pos);
	bool CanTouch(int Map[10][9],CPoint from , CPoint to);
	int GetBingValue(CPoint pos, int Map[10][9]);
	int m_BaseValue[15];
	int m_FlexValue[15];
	int m_AttackPos[10][9];
	int m_GuardPos[10][9];
	int m_FlexibilityPos[10][9];
	int m_chessValue[10][9];
	vector<CPoint> RelatePos;
};