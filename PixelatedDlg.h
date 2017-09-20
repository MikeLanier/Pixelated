
// PixelatedDlg.h : header file
//

#pragma once


// CPixelatedDlg dialog
class CPixelatedDlg : public CDialog
{
// Construction
public:
	CPixelatedDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_PIXELATED_DIALOG };

	int		m_nBoard[16][9];
	CRect	m_rcButton[7];
	int		m_nMoves;
	void SetColor( int i, int j, int ccolor, int ncolor );

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
