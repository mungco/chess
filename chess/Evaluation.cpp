#include "StdAfx.h"
#include "Evaluation.h"


const int BA0[10][9] = {
	{0,	0,	0,	0,	0,	0,	0,	0,	0},
	{90,90,	110,120,120,120,110,90,	90},
	{90,90,	110,120,120,120,110,90,	90},
	{70,90,	110,110,110,110,110,90,	70},
	{70,70,	70, 70, 70,  70, 70,70,	70},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
};

const int BA1[10][9] = {
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{70,70,70, 70, 70,70, 70,70, 70},
	{70,90,110,110,110,110,110,90,70},
	{90,90,110,120,120,120,110,90,90},
	{90,90,110,120,120,120,110,90,90},
	{0,  0, 0,  0,  0,  0,  0,  0,  0},
};

CEvaluation::CEvaluation(void)
{
	m_BaseValue[B_KING] = BASEVALUE_KING; 
	m_BaseValue[B_CAR] = BASEVALUE_CAR; 
	m_BaseValue[B_HORSE] = BASEVALUE_HORSE; 
	m_BaseValue[B_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[B_ELEPHANT] = BASEVALUE_ELEPHANT; 
	m_BaseValue[B_CANON] = BASEVALUE_CANON; 
	m_BaseValue[B_PAWN] = BASEVALUE_PAWN; 

	m_BaseValue[R_KING] = BASEVALUE_KING; 
	m_BaseValue[R_CAR] = BASEVALUE_CAR; 
	m_BaseValue[R_HORSE] = BASEVALUE_HORSE; 
	m_BaseValue[R_BISHOP] = BASEVALUE_BISHOP; 
	m_BaseValue[R_ELEPHANT] = BASEVALUE_ELEPHANT; 
	m_BaseValue[R_CANON] = BASEVALUE_CANON; 
	m_BaseValue[R_PAWN] = BASEVALUE_PAWN; 

	m_FlexValue[B_KING] = FLEXIBILITY_KING; 
	m_FlexValue[B_CAR] = FLEXIBILITY_CAR; 
	m_FlexValue[B_HORSE] = FLEXIBILITY_HORSE; 
	m_FlexValue[B_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[B_ELEPHANT] = FLEXIBILITY_ELEPHANT; 
	m_FlexValue[B_CANON] = FLEXIBILITY_CANON; 
	m_FlexValue[B_PAWN] = FLEXIBILITY_PAWN; 

	m_FlexValue[R_KING] = FLEXIBILITY_KING; 
	m_FlexValue[R_CAR] = FLEXIBILITY_CAR; 
	m_FlexValue[R_HORSE] = FLEXIBILITY_HORSE; 
	m_FlexValue[R_BISHOP] = FLEXIBILITY_BISHOP; 
	m_FlexValue[R_ELEPHANT] = FLEXIBILITY_ELEPHANT; 
	m_FlexValue[R_CANON] = FLEXIBILITY_CANON; 
	m_FlexValue[R_PAWN] = FLEXIBILITY_PAWN; 
	m_nRelatePos=0;
}


CEvaluation::~CEvaluation(void)
{

}

int CEvaluation::GetBingValue(CPoint pos, int Map[10][9])
{
	if(Map[pos.x][pos.y]==R_PAWN)
		return BA0[pos.x][pos.y];
	if(Map[pos.x][pos.y]==B_PAWN)
		return BA1[pos.x][pos.y];
	return 0;
}

void CEvaluation::AddPoint(const CPoint &pos)
{
	RelatePos[m_nRelatePos].x=pos.x;
	RelatePos[m_nRelatePos].y=pos.y;
	m_nRelatePos++;
}

int CEvaluation::GetRelatePiece(int Map[10][9],CPoint pos)
{//性能瓶颈！！！！！！
	BYTE nChessID;
	BYTE flag;
	int x,y;
	CPoint addp;
	m_nRelatePos=0;
	nChessID = Map[pos.x][pos.y];
	switch(nChessID)
	{
	case R_KING:
		GNT_ShuaiRelate(Map,pos);
		break;
	case B_KING:
		GNT_JiangRelate(Map,pos);
		break;
	case R_BISHOP:
		GNT_RShiRelate(Map,pos);
		break;
	case B_BISHOP:
		GNT_BShiRelate(Map,pos);
		break;
	case R_ELEPHANT:
		GNT_RXiangRelate(Map,pos);
		break;
	case B_ELEPHANT:
		GNT_BXiangRelate(Map,pos);
		break;
	case R_HORSE:
	case B_HORSE:
		GNT_MaRelate(Map,pos);
		break;
	case R_CAR:
	case B_CAR:
		GNT_JuRelate(Map,pos);
		break;
	case R_PAWN:
		y = pos.y;
		x = pos.x-1;
		addp.x=x;
		addp.y=y;
		if(x >= 0)
			AddPoint(addp);
		if(pos.x < 5)
		{
			y=pos.y+1;
			x=pos.x;
			addp.x=x;
			addp.y=y;
			if(y < 9 )
				AddPoint(addp);
			y=pos.y-1;
			addp.y=y;
			if(y >= 0 )
				AddPoint(addp);
		}
		break;

	case B_PAWN:
		y = pos.y;
		x = pos.x+1;
		addp.x=x;
		addp.y=y;
		if(x < 10 )
			AddPoint(addp);
		if(pos.x > 4)
		{
			y=pos.y+1;
			x=pos.x;
			addp.x=x;
			addp.y=y;
			if(y < 9)
				AddPoint(addp);
			y=pos.y-1;
			addp.y=y;
			if(y >= 0)
				AddPoint(addp);
		}
		break;

	case B_CANON:
	case R_CANON:
		GNT_CannonRelate(Map,pos);
		break;
	default:
		break;
	}
	return m_nRelatePos ;				

}

inline void CEvaluation::GNT_JiangRelate(int Map[][9], const CPoint &pos)
{
	int x;
	int y;
	x=pos.x;
	y=pos.y+1;
	CPoint addp;
	addp.x=x;
	addp.y=y;
	if(y<=5)
		AddPoint(addp);
	x=pos.x;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(y>=3)
		AddPoint(addp);
	x=pos.x+1;
	y=pos.y;
	addp.x=x;
	addp.y=y;
	if(x<=2)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y;
	addp.x=x;
	addp.y=y;
	if(x>=0)
		AddPoint(addp);
}

inline void CEvaluation::GNT_ShuaiRelate(int Map[][9],const CPoint &pos)
{
	CPoint addp;
	int x;
	int y;
	x=pos.x;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;
	if(y<=5)
		AddPoint(addp);
	x=pos.x;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(y>=3)
		AddPoint(addp);
	x=pos.x+1;
	y=pos.y;
	addp.x=x;
	addp.y=y;
	if(x<=9)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y;
	addp.x=x;
	addp.y=y;
	if(x>=7)
		AddPoint(addp);
}

inline void CEvaluation::GNT_BShiRelate(int Map[][9], const CPoint &pos)
{
	CPoint addp;
	int x,y;
	x=pos.x+1;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;
	if(x<=2 && y<=5)
		AddPoint(addp);
	x=pos.x+1;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(x<=2 && y>=3)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;
	if(x>=0 && y<=5)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(x>=0 && y>=3)
		AddPoint(addp);
}

inline void CEvaluation::GNT_RShiRelate(int Map[][9], const CPoint &pos)
{
	CPoint addp;
	int x,y;
	x=pos.x+1;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;
	if(x<=9 && y<=5)
		AddPoint(addp);
	x=pos.x+1;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(x<=9 && y>=3)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;
	if(x>=7 && y<=5)
		AddPoint(addp);
	x=pos.x-1;
	y=pos.y-1;
	addp.x=x;
	addp.y=y;
	if(x>=7 && y>=3)
		AddPoint(addp);
}

inline void CEvaluation::GNT_RXiangRelate(int Map[][9],const CPoint &pos)
{
	CPoint addp;
	int srcx=pos.x;
	int srcy=pos.y;
	int x, y;
	x=pos.x+2;
	y=pos.y+2;
	addp.x=x;
	addp.y=y;
	if(x<10 && y<9 && Map[srcx+1][srcy+1]!=NOCHESS)
		AddPoint(addp);
	x=srcx+2;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if(x<10 && y>=0 && Map[srcx+1][srcy-1]!=NOCHESS)
		AddPoint(addp);
	x=srcx-2;
	y=srcy+2;
	addp.x=x;
	addp.y=y;
	if(x>=5 && y<9 && Map[srcx-1][srcy+1]!=NOCHESS)
		AddPoint(addp);
	x=srcx-2;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if(x>=5 && y>=0 && Map[srcx-1][srcy-1]!=NOCHESS)
		AddPoint(addp);
}

inline void CEvaluation::GNT_BXiangRelate(int Map[][9],const CPoint &pos)
{
	CPoint addp;
	int srcx=pos.x;
	int srcy=pos.y;
	int x, y;
	x=pos.x+2;
	y=pos.y+2;
	addp.x=x;
	addp.y=y;
	if(x<5 && y<9 && Map[srcx+1][srcy+1]!=NOCHESS)
		AddPoint(addp);
	x=srcx+2;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if(x<5 && y>=0 && Map[srcx+1][srcy-1]!=NOCHESS)
		AddPoint(addp);
	x=srcx-2;
	y=srcy+2;
	addp.x=x;
	addp.y=y;
	if(x>=0 && y<9 && Map[srcx-1][srcy+1]!=NOCHESS)
		AddPoint(addp);
	x=srcx-2;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if(x>=0 && y>=0 && Map[srcx-1][srcy-1]!=NOCHESS)
		AddPoint(addp);
}

inline void CEvaluation::GNT_MaRelate(int Map[][9], const CPoint &pos)
{
	CPoint addp;
	int srcx=pos.x;
	int srcy=pos.y;
	int x, y;
	x=srcx+1;
	y=srcy+2;
	addp.x=x;
	addp.y=y;
	if(x < 9 && y < 10 && Map[srcx][srcy+1]!=NOCHESS)
		AddPoint(addp);

	x=srcx+2;
	y=srcy+1;
	addp.x=x;
	addp.y=y;
	if(x < 9 && y < 10 && Map[srcx+1][srcy]!=NOCHESS)
		AddPoint(addp);
	x=srcx-1;
	y=srcy+2;
	addp.x=x;
	addp.y=y;
	if(y < 9 && x >= 0 && Map[srcx][srcy+1]!=NOCHESS)
		AddPoint(addp);

	x=srcx+1;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if( y >= 0 && x < 10 && Map[srcx][srcy-1]!=NOCHESS)
		AddPoint(addp);

	x=srcx-1;
	y=srcy-2;
	addp.x=x;
	addp.y=y;
	if( x >= 0 && y >= 0  && Map[srcx][srcy-1]!=NOCHESS)
		AddPoint(addp);

	x=srcx+2;
	y=srcy-1;
	addp.x=x;
	addp.y=y;
	if( y >= 0 && x < 10 && Map[srcx+1][srcy]!=NOCHESS)
		AddPoint(addp);

	x=srcx-2;
	y=srcy+1;
	addp.x=x;
	addp.y=y;
	if( y < 9 && x >= 0 && Map[srcx-1][srcy]!=NOCHESS)
		AddPoint(addp);

	x=srcx-2;
	y=srcy-1;
	addp.x=x;
	addp.y=y;
	if((x >= 0 && y >= 0) && Map[srcx-1][srcy]!=NOCHESS)
		AddPoint(addp);
}

inline void CEvaluation::GNT_JuRelate(int Map[][9],const CPoint &pos)
{
	CPoint addp;
	int x , y;
	x=pos.x;
	y=pos.y+1;
	addp.x=x;
	addp.y=y;	
	while(y < 9) {
		if( NOCHESS == Map[x][y] )
			AddPoint(addp);
		else {
			AddPoint(addp);
			break;
		}
		y++;
		addp.y++;
	}

	x = pos.x;
	y = pos.y-1;
	addp.x=x;
	addp.y=y;
	while(y >= 0) {
		if( NOCHESS == Map[x][y] )
			AddPoint(addp);
		else {
			AddPoint(addp);
			break;
		}
		y--;
		addp.y--;
	}

	x=pos.x+1;
	y=pos.y;//
	addp.x=x;
	addp.y=y;
	while(x < 10) {
		if( NOCHESS == Map[x][y])
			AddPoint(addp);
		else {
			AddPoint(addp);
			break;
		}
		x++;
		addp.x++;
	}

	x = pos.x-1;
	y = pos.y;//
	addp.x=x;
	addp.y=y;
	while(x>=0)
	{
		if( NOCHESS == Map[x][y])
			AddPoint(addp);
		else {
			AddPoint(addp);
			break;
		}
		x--;
		addp.x--;
	}
}

inline void CEvaluation::GNT_CannonRelate(int Map[][9],const CPoint &pos)
{
	CPoint addp;
	int x=pos.x;		//
	int y=pos.y+1;
	addp.x=x;
	addp.y=y;
	BOOL flag=FALSE;
	while(y < 9){
		if( NOCHESS == Map[x][y] ){
			if(!flag)
				AddPoint(addp);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				AddPoint(addp);
				break;
			}
		}
		y++;
		addp.y++;
	}
	y=pos.y-1;
	x=pos.x;
	addp.x=x;
	addp.y=y;
	flag=FALSE;	
	while(y>=0) {
		if( NOCHESS == Map[x][y] ) {
			if(!flag)
				AddPoint(addp);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				AddPoint(addp);
				break;
			}
		}
		y--;
		addp.y--;
	}
	x=pos.x+1;	
	y=pos.y;
	addp.x=x;
	addp.y=y;
	flag=FALSE;
	while(x < 10)
	{
		if( NOCHESS == Map[x][y] ) {
			if(!flag)
				AddPoint(addp);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				AddPoint(addp);
				break;
			}
		}
		x++;
		addp.x++;
	}
	x=pos.x-1;
	y=pos.y;
	addp.x=x;
	addp.y=y;
	flag=FALSE;	
	while(x>=0)
	{
		if( NOCHESS == Map[x][y] ) {
			if(!flag)
				AddPoint(addp);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				AddPoint(addp);
				break;
			}
		}
		x--;
		addp.x--;
	}
}

int count=0;

int CEvaluation::Evaluate(int Map[10][9],bool bIsRedTurn)
{
	int i, j, k;
	int nChessType, nTargetType;
	count++;

	memset(m_chessValue,0, 90*sizeof(int));
	memset(m_AttackPos,0, 90*sizeof(int)); 
	memset(m_GuardPos,0, 90*sizeof(int)); 
	memset(m_FlexibilityPos, 0, 90*sizeof(int));

	for(i = 0; i < 10; i++)
		for(j = 0; j < 9; j++) {
			if(Map[i][j] != NOCHESS) {
				nChessType = Map[i][j];
				GetRelatePiece(Map, CPoint(i,j));
				for (k = 0; k < m_nRelatePos ; k++)	{
					nTargetType = Map[RelatePos[k].x][RelatePos[k].y];
					if (nTargetType == NOCHESS)	{
						m_FlexibilityPos[i][j]++;	
					}
					else if(IsSameSide(nChessType, nTargetType))
							m_GuardPos[RelatePos[k].x][RelatePos[k].y]++;
					else {
							m_AttackPos[RelatePos[k].x][RelatePos[k].y]++;
							m_FlexibilityPos[i][j]++;	
							switch (nTargetType)
							{
							case R_KING:
								if (!bIsRedTurn)
									return MaxInt;
								break;
							case B_KING:
								if (bIsRedTurn)
									return MaxInt;
								break;
							default:
								m_AttackPos[RelatePos[k].x][RelatePos[k].y] += (30 + (m_BaseValue[nTargetType] - m_BaseValue[nChessType])/10)/10;
								break;
							}//switch
						}//else
					}//for
				}//if
			}//for
	for(i = 0; i < 10; i++){//根据每个棋子的灵活性计算出的棋子的价值
		for(j = 0; j < 9; j++) {
			if(Map[i][j] != NOCHESS) {
				nChessType = Map[i][j];
				m_chessValue[i][j]++;
				m_chessValue[i][j] += m_FlexValue[nChessType] * m_FlexibilityPos[i][j];
				m_chessValue[i][j] += GetBingValue(CPoint(i,j), Map);
			}
		}
	}
	int nHalfvalue;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 9; j++) {
			if(Map[i][j] != NOCHESS) {
				nChessType = Map[i][j];
				nHalfvalue = m_BaseValue[nChessType]>>4;
				m_chessValue[i][j] += m_BaseValue[nChessType];

				if (IsRed(nChessType)) {
					if (m_AttackPos[i][j]) {
						if (bIsRedTurn)	{
							if (nChessType == R_KING)
								m_chessValue[i][j]-= 20;
							else {
								m_chessValue[i][j] -= (nHalfvalue << 1);
								if (m_GuardPos[i][j])
									m_chessValue[i][j] += nHalfvalue;
							}
						}
						else {
							if (nChessType == R_KING)
								return MaxInt;
							m_chessValue[i][j] -= nHalfvalue*10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue*9;
						}
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else {
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;
					}
				}
				else{
					if (m_AttackPos[i][j]) {
						if (!bIsRedTurn){
							if (nChessType == B_KING)									
								m_chessValue[i][j]-= 20;
							else{
								m_chessValue[i][j] -= nHalfvalue * 2;
								if (m_GuardPos[i][j])
									m_chessValue[i][j] += nHalfvalue;
							}
						}
						else{
							if (nChessType == B_KING)
								return MaxInt;
							m_chessValue[i][j] -= nHalfvalue*10;
							if (m_GuardPos[i][j])
								m_chessValue[i][j] += nHalfvalue*9;
						}
						m_chessValue[i][j] -= m_AttackPos[i][j];
					}
					else {
						if (m_GuardPos[i][j])
							m_chessValue[i][j] += 5;
					}
				}
			}
		}
	}
	int nRedValue = 0; 
	int	nBlackValue = 0;

	for(i = 0; i < 10; i++){
		for(j = 0; j < 9; j++)
		{
			nChessType = Map[i][j];
			if (nChessType != NOCHESS) {
				if (IsRed(nChessType))
					nRedValue += m_chessValue[i][j];	
				else
					nBlackValue += m_chessValue[i][j];
			}
		}
	}
	if (bIsRedTurn)
		return nRedValue - nBlackValue;
	else
		return  nBlackValue-nRedValue;
}