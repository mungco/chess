#include "StdAfx.h"
#include "SearchEngine.h"


CSearchEngine::CSearchEngine(void)
{
}


CSearchEngine::~CSearchEngine(void)
{
}

int CSearchEngine::MakeMove(CHESSMOVE *move)
{
	int nChessID;
	nChessID=CurMap[move->to.x][move->to.y];
	CurMap[move->to.x][move->to.y]=CurMap[move->from.x][move->from.y];
	CurMap[move->from.x][move->from.y]=NOCHESS;
	return nChessID;
}

void CSearchEngine::UnMakeMove(CHESSMOVE *move,int type)
{
	CurMap[move->from.x][move->from.y]=CurMap[move->to.x][move->to.y];
	CurMap[move->to.x][move->to.y]=type;
}
