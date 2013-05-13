#pragma once


#define NOCHESS 0    //û������

#define B_KING       1  //��˧
#define B_CAR        2  //�ڳ�
#define B_HORSE      3  //����
#define B_CANON      4  //����
#define B_BISHOP     5  //��ʿ
#define B_ELEPHANT   6  //����
#define B_PAWN       7  //����
#define B_BEGIN      B_KING
#define B_END        B_PAWN

#define R_KING       8   //��˧
#define R_CAR        9   //�쳵
#define R_HORSE      10  //����
#define R_CANON      11  //����
#define R_BISHOP     12  //��ʿ
#define R_ELEPHANT   13  //����
#define R_PAWN       14  //���
#define R_BEGIN      R_KING
#define R_END        R_PAWN

#define IsBlack(x)  ((x)>=B_BEGIN && (x)<=B_END)
#define IsRed(x)  ((x)>=R_BEGIN&&(x)<=R_END)
#define IsSameSide(x,y)  ((IsBlack(x)&&IsBlack(y))||(IsRed(x)&&IsRed(y)))

const int InitChessBoard[10][9]=
{
	{B_CAR,   B_HORSE, B_ELEPHANT, B_BISHOP, B_KING,  B_BISHOP, B_ELEPHANT, B_HORSE, B_CAR},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{NOCHESS, B_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    B_CANON, NOCHESS},
	{B_PAWN,  NOCHESS, B_PAWN,     NOCHESS,  B_PAWN,  NOCHESS,  B_PAWN,     NOCHESS, B_PAWN},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},

	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{R_PAWN,  NOCHESS, R_PAWN,     NOCHESS,  R_PAWN,  NOCHESS,  R_PAWN,     NOCHESS, R_PAWN},
	{NOCHESS, R_CANON, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    R_CANON, NOCHESS},
	{NOCHESS, NOCHESS, NOCHESS,    NOCHESS,  NOCHESS, NOCHESS,  NOCHESS,    NOCHESS, NOCHESS},
	{R_CAR,   R_HORSE, R_ELEPHANT, R_BISHOP, R_KING,  R_BISHOP, R_ELEPHANT, R_HORSE, R_CAR}
};

#define BOARDERWIDTH 14
#define BOARDERHEIGHT 15
#define GRILLEWIDTH 50
#define GRILLEHEIGHT 50

#define NBOARDWIDTH 471
#define NBOARDHEIGHT 521

#define MaxInt 2147483647