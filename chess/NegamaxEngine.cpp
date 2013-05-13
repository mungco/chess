#include "StdAfx.h"
#include "NegamaxEngine.h"


CNegamaxEngine::CNegamaxEngine(void)
{
	m_nSearchDepth=1;
}


CNegamaxEngine::~CNegamaxEngine(void)
{

}

void CNegamaxEngine::SearchAGoodMove(int Map[10][9])
{
	m_nMaxDepth=m_nSearchDepth;
	memcpy(CurMap,Map,90*sizeof(int));
	NegaMax(m_nMaxDepth);
	MakeMove(&m_cmBestMove);
	memcpy(Map,CurMap,90*sizeof(int));
}

int CNegamaxEngine::NegaMax(int depth)
{
	int current = -MaxInt ;
	int score;
	int Count,i;
	BYTE type;

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