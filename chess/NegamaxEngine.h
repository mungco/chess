#pragma once
#include "searchengine.h"

class CNegamaxEngine : 	public CSearchEngine
{
public:
	CNegamaxEngine(void);
	~CNegamaxEngine(void);
	MoveStep SearchAGoodMove(int Map[10][9]);
protected:
	int NegaMax(int depth);
};

