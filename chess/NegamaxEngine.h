#pragma once
#include "searchengine.h"

class CNegamaxEngine : 	public CSearchEngine
{
public:
	CNegamaxEngine(void);
	~CNegamaxEngine(void);
	void SearchAGoodMove(int Map[10][9]);
protected:
	int NegaMax(int depth);
};

