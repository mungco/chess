#include "StdAfx.h"
#include "NegamaxEngine.h"


CNegamaxEngine::CNegamaxEngine(void)
{
	m_nSearchDepth=3;
}


CNegamaxEngine::~CNegamaxEngine(void)
{

}

MoveStep CNegamaxEngine::SearchAGoodMove(int Map[10][9])
{
	m_nMaxDepth=m_nSearchDepth;
	memcpy(CurMap,Map,90*sizeof(int));
	if(NegaMax(m_nMaxDepth)!=-MaxInt){
		MakeMove(&m_cmBestMove);
		return m_cmBestMove;
	}
	return MoveStep(CPoint(0,0),CPoint(0,0),0);
}

int CNegamaxEngine::NegaMax(int depth)
{
	int current = -MaxInt;
	int score;
	int Count,i;
	int type;

	if (depth <= 0)	//叶子节点取估值
		return m_pEval->Evaluate(CurMap, (m_nMaxDepth-depth)%2);

	Count = m_pMG->AllValidMove(CurMap, depth, (m_nMaxDepth-depth)%2);

	for (i=0;i<Count;i++)
	{
		type = MakeMove(&(m_pMG->MoveList[depth][i]));
		score = -NegaMax(depth - 1);
		UnMakeMove(&(m_pMG->MoveList[depth][i]),type); 
		if (score > current) {
			current = score;
			if(depth == m_nMaxDepth)
				m_cmBestMove = m_pMG->MoveList[depth][i];
		}

	}
	return current;
}