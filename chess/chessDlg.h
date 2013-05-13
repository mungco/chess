
// chessDlg.h : ͷ�ļ�
//

#pragma once

#include "MoveGenerater.h"
#include "SearchEngine.h"
#include "Evaluation.h"
// CchessDlg �Ի���
class CchessDlg : public CDialogEx
{
// ����
public:
	CchessDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CHESS_DIALOG };
	struct ChessNode{
		CPoint pos;
		int ChessID;
		ChessNode(CPoint npos=CPoint(0,0),int nChessID=0){pos=npos,ChessID=nChessID;}
		bool operator!=(const ChessNode& n){if(n.pos==this->pos && n.ChessID==this->ChessID)return false;return true;}
	};
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	int m_ChessBoard[10][9];
	int m_BackupChessBoard[10][9];
	CImageList m_chessman;
	CBitmap m_chessboard;
	ChessNode m_from;
	ChessNode m_to;
	ChessNode m_move;
	CSearchEngine *m_pSE;
	CMoveGenerater *m_pMG;
	CEvaluation *m_pEva;
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
