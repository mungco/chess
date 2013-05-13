
// chessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "chess.h"
#include "chessDlg.h"
#include "afxdialogex.h"
#include "global.h"
#include "NegamaxEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CchessDlg �Ի���




CchessDlg::CchessDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CchessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CchessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CchessDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CchessDlg ��Ϣ�������

BOOL CchessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	memcpy(m_ChessBoard,InitChessBoard,90*sizeof(int));
	m_chessman.Create(41,41,ILC_COLOR24 | ILC_MASK ,14 , 0);
	CBitmap bm;
	bm.LoadBitmapW(IDB_CHESSMAN);
	m_chessman.Add(&bm,RGB(0,255,0));
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_pSE=new CNegamaxEngine;
	m_pMG=new CMoveGenerater;
	m_pEva=new CEvaluation;
	m_pSE->SetEvaluator(m_pEva);
	m_pSE->SetMoveGenerator(m_pMG);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CchessDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CchessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	CDC *pDC=this->GetDC();
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	m_chessboard.LoadBitmapW(IDB_CHESSBOARD);
	BITMAP bm;
	m_chessboard.GetObject(sizeof(BITMAP),&bm);
	CBitmap *old=memDC.SelectObject(&m_chessboard);
	CPoint pt;
	for(int i=0 ; i<10 ; i++){
		for(int j=0 ; j<9 ; j++){
			if(m_ChessBoard[i][j]){
				pt.x=j*GRILLEWIDTH+BOARDERWIDTH;
				pt.y=i*GRILLEHEIGHT+BOARDERHEIGHT;
				m_chessman.Draw(&memDC,m_ChessBoard[i][j]-1,pt,ILD_TRANSPARENT);
			}
		}
	}
	if(m_move.ChessID!=NOCHESS)
		m_chessman.Draw(&memDC,m_move.ChessID-1,m_move.pos,ILD_TRANSPARENT);
	pDC->BitBlt(0,0,bm.bmWidth,bm.bmHeight,&memDC,0,0,SRCCOPY);
	memDC.SelectObject(&old);
	memDC.DeleteDC();
	m_chessboard.DeleteObject();
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CchessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x=(point.y-BOARDERHEIGHT)/GRILLEHEIGHT;
	int y=(point.x-BOARDERWIDTH)/GRILLEWIDTH;
	m_from.pos.x=x;
	m_from.pos.y=y;
	m_from.ChessID=m_ChessBoard[x][y];
	if(x>=0 && y>=0 && y<9 && x<10 && IsRed(m_ChessBoard[x][y])){
		point.x-=22;
		point.y-=22;
		m_move.pos=point;
		m_move.ChessID=m_ChessBoard[x][y];
		m_ChessBoard[x][y]=NOCHESS;
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CchessDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int x=(point.y-BOARDERHEIGHT)/GRILLEHEIGHT;
	int y=(point.x-BOARDERWIDTH)/GRILLEWIDTH;
	m_to.pos.x=x;
	m_to.pos.y=y;
	m_ChessBoard[m_from.pos.x][m_from.pos.y]=m_from.ChessID;
	if(m_move.ChessID && m_to!=m_from && CMoveGenerater::IsValidMove(m_ChessBoard,m_from.pos,m_to.pos)){
		m_ChessBoard[x][y]=m_move.ChessID;
		m_pSE->SearchAGoodMove(m_ChessBoard);
		m_ChessBoard[m_from.pos.x][m_from.pos.y]=NOCHESS;
	}
	else
		m_ChessBoard[m_from.pos.x][m_from.pos.y]=m_from.ChessID;		
	m_move.ChessID=NOCHESS;
	InvalidateRect(NULL,FALSE);
	UpdateWindow();
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CchessDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(m_move.ChessID){
		if(point.x<BOARDERWIDTH)
			point.x=BOARDERWIDTH;
		if(point.y<BOARDERHEIGHT)
			point.y=BOARDERHEIGHT;
		if(point.x>NBOARDWIDTH)
			point.x=NBOARDWIDTH;
		if(point.y>NBOARDHEIGHT)
			point.y=NBOARDHEIGHT;
		point.x-=22;
		point.y-=22;
		m_move.pos=point;
		InvalidateRect(NULL,FALSE);
		UpdateWindow();
	}
	CDialogEx::OnMouseMove(nFlags, point);
}
