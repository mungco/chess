#include "StdAfx.h"
#include "MoveGenerater.h"
#include "global.h"

CMoveGenerater::CMoveGenerater(void)
{
	MoveList=vector<vector<MoveStep> >(8);
}


CMoveGenerater::~CMoveGenerater(void)
{

}

int CMoveGenerater::AddMove(CPoint from,CPoint to,int ply)
{
	MoveList[ply].push_back(MoveStep(from,to));
	m_nMoveCount++;
	return MoveList[ply].size();
}

bool CMoveGenerater::IsValidMove(int Map[10][9] , CPoint from, CPoint to ){
	int i, j;
	int nMoveChessID, nTargetID;

	if (from == to)
		return false;//目的与源相同

	nMoveChessID = Map[from.x][from.y];
	nTargetID = Map[to.x][to.y];

	if (IsSameSide(nMoveChessID, nTargetID))
		return false;//不能吃自己的棋

	switch(nMoveChessID)
	{
	case B_KING:     
		if (nTargetID == R_KING)//老将也是可以Move的
		{
			if (from.y != to.y)
				return FALSE;
			for (i = from.x + 1; i < to.x; i++)
				if (Map[i][from.y] != NOCHESS)
					return FALSE;
		}
		else
		{
			if (to.x > 2 || to.y > 5 || to.y < 3)
				return FALSE;//目标点在九宫之外
			if(abs(from.x - to.x) + abs(to.y - from.y) > 1) 
				return FALSE;//将帅只走一步直线:
		}
		break;
	case R_BISHOP:   

		if (to.x < 7 || to.y > 5 || to.y < 3)
			return FALSE;//士出九宫	

		if (abs(from.x - to.x) != 1 || abs(to.y - from.y) != 1)
			return FALSE;	//士走斜线

		break;

	case B_BISHOP:   //黑士

		if (to.x > 2 || to.y > 5 || to.y < 3)
			return FALSE;//士出九宫	

		if (abs(from.x - to.x) != 1 || abs(to.y - from.y) != 1)
			return FALSE;	//士走斜线

		break;

	case R_ELEPHANT://红象

		if(to.x < 5)
			return FALSE;//相不能过河

		if(abs(from.y-to.y) != 2 || abs(from.x-to.x) != 2)
			return FALSE;//相走田字

		if(Map[(from.x + to.x) / 2][(from.y + to.y) / 2] != NOCHESS)
			return FALSE;//相眼被塞住了

		break;

	case B_ELEPHANT://黑象 

		if(to.x > 4)
			return FALSE;//相不能过河

		if(abs(from.y-to.y) != 2 || abs(from.x-to.x) != 2)
			return FALSE;//相走田字

		if(Map[(from.x + to.x) / 2][(from.y + to.y) / 2] != NOCHESS)
			return FALSE;//相眼被塞住了

		break;

	case B_PAWN:     //黑兵

		if(to.x < from.x)
			return FALSE;//兵不回头

		if( from.x < 5 && from.x == to.x)
			return FALSE;//兵过河前只能直走

		if(to.x - from.x + abs(to.y - from.y) > 1)
			return FALSE;//兵只走一步直线:

		break;

	case R_PAWN:    //红兵

		if(to.x > from.x)
			return FALSE;//兵不回头

		if( from.x > 4 && from.x == to.x)
			return FALSE;//兵过河前只能直走

		if(from.x - to.x + abs(to.y - from.y) > 1)
			return FALSE;//兵只走一步直线:

		break;

	case R_KING:     
		if (nTargetID == B_KING)//老将见面?
		{
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
			if(abs(from.x - to.x) + abs(to.y - from.y) > 1) 
				return FALSE;//将帅只走一步直线:
		}
		break;

	case B_CAR:      
	case R_CAR:      

		if(from.x != to.x && from.y != to.y)
			return FALSE;	//车走直线:

		if(from.x == to.x) {
			if(from.y < to.y){
				for(i = from.y + 1; i < to.y; i++)
					if(Map[from.x][i] != NOCHESS)
						return FALSE;
			}else{
				for(i = to.y + 1; i < from.y; i++)
					if(Map[from.x][i] != NOCHESS)
						return FALSE;
			}
		}
		else{
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
			return FALSE;

		if(to.y-from.y==2)
		{
			i=from.y+1;
			j=from.x;
		}
		else if	(from.y-to.y==2)
		{
			i=from.y-1;
			j=from.x;
		}
		else if	(to.x-from.x==2)
		{
			i=from.y;
			j=from.x+1;
		}
		else if	(from.x-to.x==2)
		{
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

		//炮不吃子时经过的路线中不能有棋子

		if(Map[to.x][to.y] == NOCHESS)
		{
			if(from.x == to.x)
			{
				if(from.y < to.y)
				{
					for(i = from.y + 1; i < to.y; i++)
						if(Map[from.x][i] != NOCHESS)
							return FALSE;
				}
				else
				{
					for(i = to.y + 1; i < from.y; i++)
						if(Map[from.x][i]!=NOCHESS)
							return FALSE;
				}
			}
			else
			{
				if(from.x < to.x)
				{
					for(j = from.x + 1; j < to.x; j++)
						if(Map[j][from.y] != NOCHESS)
							return FALSE;
				}
				else
				{
					for(j = to.x + 1; j < from.x; j++)
						if(Map[j][from.y] != NOCHESS)
							return FALSE;
				}
			}
		}
		//炮吃子时
		else	
		{
			int count=0;
			if(from.x == to.x)
			{
				if(from.y < to.y)
				{
					for(i=from.y+1;i<to.y;i++)
						if(Map[from.x][i]!=NOCHESS)
							count++;
					if(count != 1)
						return FALSE;
				}
				else
				{
					for(i=to.y+1;i<from.y;i++)
						if(Map[from.x][i] != NOCHESS)
							count++;
					if(count!=1)
						return FALSE;
				}
			}
			else
			{
				if(from.x<to.x)
				{
					for(j=from.x+1;j<to.x;j++)
						if(Map[j][from.y]!=NOCHESS)
							count++;
					if(count!=1)
						return FALSE;
				}
				else
				{
					for(j=to.x+1;j<from.x;j++)
						if(Map[j][from.y] != NOCHESS)
							count++;
					if(count!=1)
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

int CMoveGenerater::AllValidMove(int Map[10][9],int nPly,int nSide)
{
	int     nChessID;
	int		i,j;

	m_nMoveCount = 0;
	for (i = 0; i < 10; i++)
		for (j = 0; j < 9; j++)
		{
			if (Map[i][j] != NOCHESS)
			{
				nChessID = Map[i][j];
				if (!nSide && IsRed(nChessID))
					continue;
				if (nSide && IsBlack(nChessID))
					continue;
				switch(nChessID)
				{
				case R_KING:
					GNT_ShuaiMove(Map, CPoint(i,j), nPly);
				case B_KING:
					GNT_JiangMove(Map, CPoint(i,j), nPly);
					break;

				case R_BISHOP:
					GNT_RShiMove(Map, CPoint(i,j), nPly);
					break;

				case B_BISHOP:
					GNT_BShiMove(Map, CPoint(i,j), nPly);
					break;

				case R_ELEPHANT:
				case B_ELEPHANT:
					GNT_BXiangMove(Map, CPoint(i,j), nPly);
					break;

				case R_HORSE:		
				case B_HORSE:		
					GNT_BMaMove(Map,CPoint(i,j), nPly);
					break;

				case R_CAR:
				case B_CAR:
					GNT_BJuMove(Map, CPoint(i,j), nPly);
					break;

				case R_PAWN:
					GNT_RBingMove(Map,CPoint(i,j), nPly);
					break;

				case B_PAWN:
					GNT_BZuMove(Map, CPoint(i,j), nPly);
					break;

				case B_CANON:
				case R_CANON:
					GNT_BPaoMove(Map, CPoint(i,j), nPly);
					break;
				default:
					break;

				}
			}
		}
		return m_nMoveCount;
}

void CMoveGenerater::GNT_JiangMove(int Map[10][9],CPoint pos,int nPly)
{
	int x,y;
	for(x=0 ; x<3 ; x++)
		for(y=3 ; y<6 ; y++)
			if(IsValidMove(Map,pos,CPoint(x,y)))
				AddMove(pos,CPoint(x,y),nPly);
}

void CMoveGenerater::GNT_ShuaiMove(int Map[10][9],CPoint pos,int nPly)
{
	int x, y;
	for(x=7 ; x<10 ; x++)
		for(y=3 ; y<6 ; y++)
			if(IsValidMove(Map,pos,CPoint(x,y)))
				AddMove(pos,CPoint(x,y),nPly);
}

void CMoveGenerater::GNT_BJuMove(int Map[10][9],CPoint pos,int nPly)
{
	int x,  y;
	int nChessID;

	nChessID = Map[pos.x][pos.y];

	x=pos.x;
	y=pos.y+1;
	while(y < 9)
	{
		if( NOCHESS == Map[x][y] )
			AddMove(pos,CPoint(x, y),nPly);
		else
		{
			if(!IsSameSide(nChessID, Map[x][y]))
				AddMove(pos,CPoint(x,y),nPly);
			break;
		}
		y++;
	}

	x = pos.x;
	y = pos.y-1;
	while(y >= 0)
	{
		if( NOCHESS == Map[x][y] )
			AddMove(pos, CPoint(x, y), nPly);
		else
		{
			if(!IsSameSide(nChessID, Map[x][y]))
				AddMove(pos,CPoint( x, y), nPly);
			break;
		}
		y--;
	}

	x=pos.x+1;
	y=pos.y;//
	while(x < 10)
	{
		if( NOCHESS == Map[x][y])
			AddMove(pos, CPoint(x, y), nPly);
		else
		{
			if(!IsSameSide(nChessID, Map[x][y]))
				AddMove(pos, CPoint(x, y), nPly);
			break;
		}
		x++;
	}

	x = pos.x-1;
	y = pos.y;//
	while(x>=0)	{
		if( NOCHESS == Map[x][y])
			AddMove(pos, CPoint(x, y), nPly);
		else {
			if(!IsSameSide(nChessID, Map[x][y]))
				AddMove(pos, CPoint(x, y), nPly);
			break;
		}
		x--;
	}
}

void CMoveGenerater::GNT_BMaMove(int Map[10][9],CPoint pos,int nPly)
{
	int x,  y;

	x=pos.x+1;
	y=pos.y+2;
	if((x < 9 && y < 10) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos , CPoint(x,y), nPly);

	x=pos.x-1;
	y=pos.y+2;
	if((y < 9 && x >= 0) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x+1;
	y=pos.y-2;
	if((y >= 0 && x < 10) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x-1;
	y=pos.y-2;
	if((x >= 0 && y >= 0) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x+2;
	y=pos.y+1;
	if((x < 9 && y < 10) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);
	x=pos.x+2;
	y=pos.y-1;
	if((y >= 0 && x < 10) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);
	x=pos.x-2;
	y=pos.y+1;
	if((y < 9 && x >= 0) &&IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);
	x=pos.x-2;
	y=pos.y-1;
	if((x >= 0 && y >= 0) &&IsValidMove(Map,pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);
}

void CMoveGenerater::GNT_BPaoMove(int Map[10][9],CPoint pos,int nPly)
{
	int x, y;
	BOOL	flag;
	int nChessID;

	nChessID = Map[pos.x][pos.y];

	x=pos.x;		//各种不同的判断实在是太二了
	y=pos.y+1;
	flag=FALSE;
	while(y < 9)		
	{
		if( NOCHESS == Map[x][y] ){
			if(!flag)
				AddMove(pos, CPoint(x, y), nPly);
		}
		else{
			if(!flag)
				flag=TRUE;
			else {
				if(!IsSameSide(nChessID, Map[x][y]))
					AddMove(pos, CPoint(x, y), nPly);
				break;
			}
		}
		y++;
	}

	y=pos.y-1;
	flag=FALSE;	
	while(y>=0)
	{
		if( NOCHESS == Map[x][y] ){
			if(!flag)
				AddMove(pos, CPoint(x, y), nPly);
		}
		else{
			if(!flag)
				flag=TRUE;
			else {
				if(!IsSameSide(nChessID, Map[y][x]))
					AddMove(pos, CPoint(x, y), nPly);
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
		if( NOCHESS == Map[x][y] ){
			if(!flag)
				AddMove(pos, CPoint(x, y), nPly);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				if(!IsSameSide(nChessID, Map[x][y]))
					AddMove(pos, CPoint(x, y), nPly);
				break;
			}
		}
		x++;
	}

	x=pos.x-1;	//
	flag=FALSE;	
	while(x>=0)
	{
		if( NOCHESS == Map[x][y] ) {
			if(!flag)
				AddMove(pos, CPoint(x, y), nPly);
		}
		else {
			if(!flag)
				flag=TRUE;
			else {
				if(!IsSameSide(nChessID, Map[x][y]))
					AddMove(pos, CPoint(x, y), nPly);
				break;
			}
		}
		x--;
	}

}

void CMoveGenerater::GNT_BXiangMove(int Map[10][9] , CPoint pos , int nPly)
{
	int x,  y;

	x=pos.x+2;
	y=pos.y+2;
	if(y < 9 && x < 10  && IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x-2;
	y=pos.y+2;
	if(y < 9 && x>=0  &&  IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x+2;
	y=pos.x-2;
	if(y>=0 && x < 10  && IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);

	x=pos.x-2;
	y=pos.y-2;
	if(x>=0 && y>=0  && IsValidMove(Map, pos, CPoint(x, y)))
		AddMove(pos, CPoint(x, y), nPly);
}

void CMoveGenerater::GNT_BShiMove(int Map[10][9],CPoint pos,int nPly)
{
	int x,  y;
	for (x = 0; x < 3; x++)
		for (y = 3; y < 6; y++)
			if (IsValidMove(Map,  pos, CPoint(x, y)))
				AddMove( pos, CPoint(x, y), nPly);
}

void CMoveGenerater::GNT_RShiMove(int Map[10][9],CPoint pos , int nPly)
{
	int x,  y;
	for (x = 7; x < 10; x++)
		for (y = 3; y < 6; y++)
			if (IsValidMove(Map,  pos, CPoint(x, y)))
				AddMove( pos, CPoint(x, y), nPly);
}

void CMoveGenerater::GNT_BZuMove(int Map[10][9],CPoint pos , int nPly)
{
	int x, y;
	int nChessID;

	nChessID = Map[pos.x][pos.y];

	x = pos.x +1;
	y = pos.y;

	if(x < 10 && !IsSameSide(nChessID, Map[x][y]))
		AddMove(pos, CPoint(x, y), nPly);

	if( x > 4)
	{
		y = pos.y+1;
		x = pos.x;
		if(y < 9 && !IsSameSide(nChessID, Map[x][y]))
			AddMove(pos, CPoint(x, y), nPly);
		y=pos.y-1;
		if(y >= 0 && !IsSameSide(nChessID, Map[x][y]))
			AddMove(pos, CPoint(x, y), nPly);
	}
}

void CMoveGenerater::GNT_RBingMove(int Map[10][9],CPoint pos , int nPly)
{
	int x, y;
	int nChessID;

	nChessID = Map[pos.x][pos.y];

	x = pos.x -1;
	y = pos.y;

	if( x>0 && !IsSameSide(nChessID, Map[x][y]))
		AddMove(pos, CPoint(x, y), nPly);

	if( x <5 )
	{
		y = pos.y+1;
		x = pos.x;
		if(y < 9 && !IsSameSide(nChessID, Map[x][y]))
			AddMove(pos, CPoint(x, y), nPly);
		y=pos.y-1;
		if(y >= 0 && !IsSameSide(nChessID, Map[x][y]))
			AddMove(pos, CPoint(x, y), nPly);
	}
}
