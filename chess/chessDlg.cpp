
// chessDlg.cpp : 实现文件
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


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CchessDlg 对话框




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


// CchessDlg 消息处理程序

BOOL CchessDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	memcpy(m_ChessBoard,InitChessBoard,90*sizeof(int));
	m_chessman.Create(41,41,ILC_COLOR24 | ILC_MASK ,14 , 0);
	CBitmap bm;
	bm.LoadBitmapW(IDB_CHESSMAN);
	m_chessman.Add(&bm,RGB(0,255,0));
	// TODO: 在此添加额外的初始化代码
	m_pSE=new CNegamaxEngine;
	m_pMG=new CMoveGenerater;
	m_pEva=new CEvaluation;
	m_pSE->SetEvaluator(m_pEva);
	m_pSE->SetMoveGenerator(m_pMG);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CchessDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CchessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CchessDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
