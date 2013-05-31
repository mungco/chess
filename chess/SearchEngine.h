#pragma once
#include "Evaluation.h"
#include "MoveGenerater.h"
#include "global.h"

class CSearchEngine
{
public:
	typedef MoveStep CHESSMOVE;
	CSearchEngine(void);
	~CSearchEngine(void);
	virtual CHESSMOVE SearchAGoodMove(int Map[10][9])=0;
	virtual void SetSearchDepth(int nDepth){m_nSearchDepth=nDepth;}
	virtual void SetEvaluator(CEvaluation *pEval){m_pEval=pEval;}
	virtual void SetMoveGenerator(CMoveGenerater *pMG){m_pMG=pMG;}
protected:
	virtual int MakeMove(CHESSMOVE *move);
	virtual void UnMakeMove(CHESSMOVE*move,int type);
	CHESSMOVE m_cmBestMove;
	int CurMap[10][9];
	CEvaluation * m_pEval;
	CMoveGenerater *m_pMG;
	int m_nSearchDepth;
	int m_nMaxDepth;
};

