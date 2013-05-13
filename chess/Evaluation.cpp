#include "StdAfx.h"
#include "Evaluation.h"


const int BA0[10][9] = {
	{0,  0,  0,  0,  0,  0,  0,  0,  0},
	{90,90,110,120,120,120,110,90,90},
	{90,90,110,120,120,120,110,90,90},
	{70,90,110,110,110,110,110,90,70},
	{70,70,70, 70, 70,  70, 70,70,70},
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

bool CEvaluation::CanTouch(int Map[10][9],CPoint from,CPoint to)
{
	int i, j;
	int nMoveChessID, nTargetID;

	if (from==to)
		return FALSE;//目的与源相同

	nMoveChessID = Map[from.x][from.y];
	nTargetID = Map[to.x][to.y];

	switch(nMoveChessID)
	{
	case B_KING:     
		if (nTargetID == R_KING) {
			if (from.y != to.y)
				return FALSE;
			for (i = from.x + 1; i < to.x; i++)
				if (Map[i][from.y] != NOCHESS)
					return FALSE;
		}
		else {
			if (to.x > 2 || to.y > 5 || to.y < 3 || to.x<0)
				return FALSE;//目标点在九宫之外
			if(abs(from.x - to.x) + abs(from.y - to.y) > 1) 
				return FALSE;//将帅只走一步直线
		}
		break;
	case R_BISHOP:   

		if (to.x < 7 || to.y > 5 || to.y < 3 || to.x>9)
			return FALSE;//士出九宫	

		if (abs(from.x - to.x) != 1 || abs(from.y-to.y) != 1)
			return FALSE;	//士走斜线
		break;

	case B_BISHOP:   //黑士

		if (to.x > 2 || to.y > 5 || to.y < 3 || to.x<0)
			return FALSE;//士出九宫	

		if (abs(from.x - to.x) != 1 || abs(from.y-to.y) != 1)
			return FALSE;	//士走斜线

		break;

	case R_ELEPHANT://红象

		if(to.x < 5)
			return FALSE;//相不能过河

		if(abs(from.y-to.y) != 2 || abs(from.x - to.x) != 2)
			return FALSE;//相走田字

		if(Map[(from.y+to.y) / 2][(from.x + to.x) / 2] != NOCHESS)
			return FALSE;//相眼被塞住了

		break;

	case B_ELEPHANT://黑象 

		if(to.x > 4)
			return FALSE;//相不能过河

		if(abs(from.y-to.y) != 2 || abs(from.x - to.x) != 2)
			return FALSE;//相走田字

		if(Map[(from.y+to.y) / 2][(from.x + to.x) / 2] != NOCHESS)
			return FALSE;//相眼被塞住了

		break;

	case B_PAWN:     //黑兵

		if(to.x < from.x)
			return FALSE;//兵不回头

		if( from.x < 5 && from.x == to.x)
			return FALSE;//兵过河前只能直走

		if(abs(from.y-to.y) +to.x - from.x > 1)
			return FALSE;//兵只走一步直线:

		break;

	case R_PAWN:    //红兵

		if(to.x > from.x)
			return FALSE;//兵不回头

		if( from.x > 4 && from.x == to.x)
			return FALSE;//兵过河前只能直走

		if(abs(from.y-to.y) + from.x - to.x > 1)
			return FALSE;//兵只走一步直线:

		break;

	case R_KING:     
		if (nTargetID == B_KING) {
			if (from.y != to.y)
				return FALSE;//两个将不在同一列
			for (i = from.x - 1; i > to.x; i--)
				if (Map[i][from.y] != NOCHESS)
					return FALSE;//中间有别的子
		}
		else
		{
			if (to.x < 7 || to.y > 5 || to.y < 3)
				return FALSE;//目标点在九宫之外
			if(abs(from.y-to.y) + abs(from.x - to.x) > 1) 
				return FALSE;//将帅只走一步直线:
		}
		break;

	case B_CAR:      
	case R_CAR:      

		if(from.x != to.x && from.y != to.y)
			return FALSE;	//车走直线:

		if(from.x == to.x)	{
			if(from.y < to.y) {
				for(i = from.y + 1; i < to.y; i++)
					if(Map[from.x][i] != NOCHESS)
						return FALSE;
			}
			else {
				for(i = to.y + 1; i < from.y; i++)
					if(Map[from.x][i] != NOCHESS)
						return FALSE;
			}
		}
		else {
			if(from.x < to.x) {
				for(j = from.x + 1; j < to.x; j++)
					if(Map[j][from.y] != NOCHESS)
						return FALSE;
			}
			else {
				for(j= to.x + 1; j < from.x; j++)
					if(Map[j][from.y] != NOCHESS)
						return FALSE;
			}
		}
		break;

	case B_HORSE:    
	case R_HORSE:    

		if(!((abs(to.y-from.y)==1 && abs(to.x-from.x)==2)
			||(abs(to.y-from.y)==2&&abs(to.x-from.x)==1)))
			return FALSE;//马走日字

		if	(to.y-from.y==2) {
			i=from.y+1;
			j=from.x;
		}
		else if	(from.y-to.y==2) {
			i=from.y-1;
			j=from.x;
		}
		else if	(to.x-from.x==2) {
			i=from.y;
			j=from.x+1;
		}
		else if	(from.x-to.x==2){
			i=from.y;
			j=from.x-1;
		}

		if(Map[i][j] != NOCHESS)
			return FALSE;//绊马腿

		break;
	case B_CANON:    
	case R_CANON:    

		if(from.x!=to.x && from.y!=to.y)
			return FALSE;	//炮走直线:

		//炮cantouch到的并不一定能吃子

		if(Map[to.x][to.y] == NOCHESS)
		{
			if(from.x == to.x) {
				if(from.y < to.y){
					for(i = from.y + 1; i < to.y; i++)
						if(Map[from.x][i] != NOCHESS)
							return FALSE;
				}
				else {
					for(i = to.y + 1; i < from.y; i++)
						if(Map[from.x][i]!=NOCHESS)
							return FALSE;
				}
			}
			else {
				if(from.x < to.x) {
					for(j = from.x + 1; j < to.x; j++)
						if(Map[j][from.y] != NOCHESS)
							return FALSE;
				}
				else {
					for(j = to.x + 1; j < from.x; j++)
						if(Map[j][from.y] != NOCHESS)
							return FALSE;
				}
			}
		}
		//以上是炮不吃子-------------------------------------
		//吃子时:=======================================
		else {
			int nCount=0;
			if(from.x == to.x) {
				if(from.y < to.y) {
					for(i=from.y+1;i<to.y;i++)
						if(Map[from.x][i]!=NOCHESS)
							nCount++;
					if(nCount != 1)
						return FALSE;
				}
				else {
					for(i=to.y+1;i<from.y;i++)
						if(Map[from.x][i] != NOCHESS)
							nCount++;
					if(nCount!=1)
						return FALSE;
				}
			}
			else {
				if(from.x<to.x)	{
					for(j=from.x+1;j<to.x;j++)
						if(Map[j][from.y]!=NOCHESS)
							nCount++;
					if(nCount!=1)
						return FALSE;
				}
				else {
					for(j=to.x+1;j<from.x;j++)
						if(Map[j][from.y] != NOCHESS)
							nCount++;
					if(nCount!=1)
						return FALSE;
				}
			}
		}
		break;
	default:
		return FALSE;
	}

	return TRUE;

}

int CEvaluation::GetRelatePiece(int Map[10][9],CPoint pos)
{
	BYTE nChessID;
	BYTE flag;
	int x,y;

	nChessID = Map[pos.x][pos.y];
	switch(nChessID)
	{
	case R_KING:
	case B_KING:

		for (x = 0; x < 3; x++)
			for (y = 3; y < 6; y++)
				if (CanTouch(Map, pos, CPoint(x, y)))
					RelatePos.push_back(CPoint(x, y));
		for (x = 7; x < 10; x++)
			for (y = 3; y < 6; y++)
				if (CanTouch(Map,pos,CPoint(x, y)))
					RelatePos.push_back(CPoint(x, y));
		break;

	case R_BISHOP:

		for (x = 7; x < 10; x++)
			for (y = 3; y < 6; y++)
				if (CanTouch(Map,pos,CPoint(x, y)))
					RelatePos.push_back(CPoint(x, y));
		break;

	case B_BISHOP:

		for (x = 0; x < 3; x++)
			for (y = 3; y < 6; y++)
				if (CanTouch(Map, pos, CPoint(x, y)))
					RelatePos.push_back(CPoint(x, y));
		break;

	case R_ELEPHANT:
	case B_ELEPHANT:

		x=pos.x+2;
		y=pos.y+2;
		if(x < 10 && y < 9  && CanTouch(Map, pos, CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x-2;
		y=pos.y+2;
		if(y < 9 && x>=0  &&  CanTouch(Map, pos, CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x+2;
		y=pos.y-2;
		if(y>=0 && x < 10  && CanTouch(Map, pos, CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x-2;
		y=pos.y-2;
		if(x>=0 && y>=0  && CanTouch(Map, pos, CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));
		break;

	case R_HORSE:		
	case B_HORSE:		
		x=pos.x+1;
		y=pos.y+2;
		if((y < 9 && x < 10) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x-1;
		y=pos.y+2;
		if((y < 9 && x >= 0) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x+1;
		y=pos.y-2;
		if((y >= 0 && x < 10) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x-1;
		y=pos.y-2;
		if((x >= 0 && y >= 0) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));

		x=pos.x+2;
		y=pos.y+1;
		if((y < 9 && x < 10) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));
		x=pos.x+2;
		y=pos.y-1;
		if((x >= 0 && y < 10) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));
		x=pos.x-2;
		y=pos.y+1;
		if((y < 9 && x >= 0) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));
		x=pos.x-2;
		y=pos.y-1;
		if((x >= 0 && y >= 0) && CanTouch(Map,pos,CPoint(x, y)))
			RelatePos.push_back(CPoint(x, y));
		break;

	case R_CAR:
	case B_CAR:
		x=pos.x;
		y=pos.y+1;
		while(y < 9) {
			if( NOCHESS == Map[x][y] )
				RelatePos.push_back(CPoint(x, y));
			else {
				RelatePos.push_back(CPoint(x, y));
				break;
			}
			y++;
		}

		x = pos.x;
		y = pos.y-1;
		while(y >= 0) {
			if( NOCHESS == Map[x][y] )
				RelatePos.push_back(CPoint(x, y));
			else {
				RelatePos.push_back(CPoint(x, y));
				break;
			}
			y--;
		}

		x=pos.x+1;
		y=pos.y;//
		while(x < 10) {
			if( NOCHESS == Map[x][y])
				RelatePos.push_back(CPoint(x, y));
			else {
				RelatePos.push_back(CPoint(x, y));
				break;
			}
			x++;
		}

		x = pos.x-1;
		y = pos.y;//
		while(x>=0)
		{
			if( NOCHESS == Map[x][y])
				RelatePos.push_back(CPoint(x, y));
			else {
				RelatePos.push_back(CPoint(x, y));
				break;
			}
			x--;
		}
		break;

	case R_PAWN:
		y = pos.y;
		x = pos.x-1;

		if(x >= 0)
			RelatePos.push_back(CPoint(x, y));

		if(pos.x < 5)
		{
			y=pos.y+1;
			x=pos.x;
			if(y < 9 )
				RelatePos.push_back(CPoint(x, y));
			y=pos.y-1;
			if(y >= 0 )
				RelatePos.push_back(CPoint(x, y));
		}
		break;

	case B_PAWN:
		y = pos.y;
		x = pos.x+1;

		if(x < 10 )
			RelatePos.push_back(CPoint(x, y));

		if(pos.x > 4)
		{
			y=pos.y+1;
			x=pos.x;
			if(y < 9)
				RelatePos.push_back(CPoint(x, y));
			y=pos.y-1;
			if(y >= 0)
				RelatePos.push_back(CPoint(x, y));
		}
		break;

	case B_CANON:
	case R_CANON:

		x=pos.x;		//
		y=pos.y+1;
		flag=FALSE;
		while(y < 9){
			if( NOCHESS == Map[x][y] ){
				if(!flag)
					RelatePos.push_back(CPoint(x, y));
			}
			else {
				if(!flag)
					flag=TRUE;
				else {
					RelatePos.push_back(CPoint(x, y));
					break;
				}
			}
			y++;
		}
		y=pos.y-1;
		x=pos.x;
		flag=FALSE;	
		while(y>=0) {
			if( NOCHESS == Map[x][y] ) {
				if(!flag)
					RelatePos.push_back(CPoint(x, y));
			}
			else {
				if(!flag)
					flag=TRUE;
				else {
					RelatePos.push_back(CPoint(x, y));
					break;
				}
			}
			y--;
		}
		x=pos.x+1;	
		y=pos.y;
		flag=FALSE;
		while(x < 10)
		{
			if( NOCHESS == Map[x][y] ) {
				if(!flag)
					RelatePos.push_back(CPoint(x, y));
			}
			else {
				if(!flag)
					flag=TRUE;
				else {
					RelatePos.push_back(CPoint(x, y));
					break;
				}
			}
			x++;
		}
		x=pos.x-1;
		y=pos.y;
		flag=FALSE;	
		while(x>=0)
		{
			if( NOCHESS == Map[x][y] ) {
				if(!flag)
					RelatePos.push_back(CPoint(x, y));
			}
			else {
				if(!flag)
					flag=TRUE;
				else {
					RelatePos.push_back(CPoint(x, y));
					break;
				}
			}
			x--;
		}
		break;

	default:
		break;

	}
	return RelatePos.size() ;				

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
				for (k = 0; k < RelatePos.size() ; k++)	{
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