
// PixelatedDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Pixelated.h"
#include "PixelatedDlg.h"
#include "Dice.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CPixelatedDlg dialog




CPixelatedDlg::CPixelatedDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPixelatedDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	for( int i=0; i<16; i++ )
	{
		for( int j=0; j<9; j++ )
		{
			m_nBoard[i][j] = Dice();
		}
	}

	for( int i=0; i<7; i++ )
	{
		m_rcButton[i] = CRect( i*60+25, 250, i*60+75, 275 );
	}

	m_nMoves = 0;
}

void CPixelatedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPixelatedDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CPixelatedDlg message handlers

BOOL CPixelatedDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPixelatedDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

static COLORREF	colors[] = 
{
	RGB( 0x00,0x00,0xff ),
	RGB( 0x00,0x77,0x00 ),
	RGB( 0xaa,0x00,0x00 ),
	RGB( 0xff,0xff,0x00 ),
	RGB( 0x77,0x00,0x77 ),
	RGB( 0x77,0x44,0x00 ),
	RGB( 0x00,0xff,0xff ),
	RGB( 0xff,0xff,0xff )
};

void CPixelatedDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();

		int	x = 0;
		int	y = 0;
		int	w = 25;
		for( int i=0; i<16; i++ )
		{
			for( int j=0; j<9; j++ )
			{
				x = i * w;
				y = j * w;

				dc.FillSolidRect( x, y, w, w, colors[m_nBoard[i][j]] );
			}
		}

		for( int i=0; i<7; i++ )
		{
			dc.FillSolidRect( m_rcButton[i], colors[i] );
		}

		CString	s;
		s.Format( L"Moves: %1d", m_nMoves );
		dc.TextOut( 10, 300, s );
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPixelatedDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CPixelatedDlg::SetColor( int i, int j, int ccolor, int ncolor )
{
	if( ccolor == ncolor ) return;

	if( i >= 0 && i < 16 )
	{
		if( j >= 0 && j< 9 )
		{
			if( m_nBoard[i][j] == ccolor )
			{
				m_nBoard[i][j] = ncolor;
				//SetColor( i-1, j-1, ccolor, ncolor );
				SetColor( i  , j-1, ccolor, ncolor );
				//SetColor( i+1, j-1, ccolor, ncolor );
				SetColor( i-1, j  , ccolor, ncolor );
				SetColor( i+1, j  , ccolor, ncolor );
				//SetColor( i-1, j+1, ccolor, ncolor );
				SetColor( i  , j+1, ccolor, ncolor );
				//SetColor( i+1, j+1, ccolor, ncolor );
			}
		}
	}
}

void CPixelatedDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	CDialog::OnLButtonUp(nFlags, point);

	for( int i=0; i<6; i++ )
	{
		if( m_rcButton[i].PtInRect(point) )
		{
			CDC* pDC = GetDC();
			CRect	rc = m_rcButton[i];
			rc.InflateRect(2,2,2,2);
			pDC->Rectangle( rc );
			pDC->FillSolidRect( m_rcButton[i], colors[i] );

			SetColor( 0, 0, m_nBoard[0][0], i );
			Invalidate();
			m_nMoves++;

			return;
		}
	}

	if( m_rcButton[6].PtInRect(point) )
	{
		m_nMoves = 0;
		for( int i=0; i<16; i++ )
		{
			for( int j=0; j<9; j++ )
			{
				m_nBoard[i][j] = Dice();
			}
		}

		Invalidate();
	}
}
