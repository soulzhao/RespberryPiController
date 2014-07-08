// TouchPanelController2Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "TouchPanelController2.h"
#include "TouchPanelController2Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTouchPanelController2Dlg dialog

CTouchPanelController2Dlg::CTouchPanelController2Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTouchPanelController2Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTouchPanelController2Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	hasStarted = false;
}

void CTouchPanelController2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTouchPanelController2Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	
	DDX_Control(pDX, IDC_PLOT, m_plot);
}

BEGIN_MESSAGE_MAP(CTouchPanelController2Dlg, CDialog)
	//{{AFX_MSG_MAP(CTouchPanelController2Dlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_FILE_EXIT, OnFileExitClick)
	ON_COMMAND(IDM_FILE_EXPORT, OnFileExportClick)
	ON_COMMAND(IDM_TOOL_SETTING, OnToolSettingClick)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_START, OnBtnStartClick)
	ON_BN_CLICKED(IDC_BTN_CLEAR, OnBtnClearClick)
	ON_BN_CLICKED(IDC_BTN_STOP, OnBtnStopClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTouchPanelController2Dlg message handlers

BOOL CTouchPanelController2Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	GetWindowRect(&m_rectOldWindow);
	((CButton*)GetDlgItem(IDC_BTN_START))->GetClientRect(&m_rectBtns);
	m_plot.GetWindowRect(&m_rectOldPlotWindow);
	
	ScreenToClient(&m_rectOldPlotWindow);
	
	m_plot.AddLine(PS_SOLID,RGB(255,0,0));	// red line 
	m_plot.AddLine(PS_SOLID,RGB(0,255,0));	// green
	
	m_plot.GetAxisY().m_color=RGB(0,255,0);
	m_plot.GetAxisY().m_dMinValue=0;
	m_plot.GetAxisY().m_dMaxValue=255;
	m_plot.CalcLayout();
	
	setCtrlBtnStatus(hasStarted);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CTouchPanelController2Dlg::setCtrlBtnStatus(bool status){
	((CButton*)GetDlgItem(IDC_BTN_START))->EnableWindow(!status);
	((CButton*)GetDlgItem(IDC_BTN_STOP))->EnableWindow(status);
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTouchPanelController2Dlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTouchPanelController2Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTouchPanelController2Dlg::OnFileExitClick() 
{
	// TODO: Add your command handler code here
	if(hasStarted){
		KillTimer(1);
		m_plot.Stop();
		m_plot.Invalidate();
		
		hasStarted = false;
	}
	
	::DestroyWindow(this->m_hWnd);
}

void CTouchPanelController2Dlg::OnFileExportClick() 
{
	// TODO: Add your command handler code here
	
}

void CTouchPanelController2Dlg::OnToolSettingClick() 
{
	// TODO: Add your command handler code here
	// (CDialog*)GetDlgItem(IDD_SETTINGS);
	settings.Create(IDD_SETTINGS, this);
	//settings.SetParent(this);
	::ShowWindow(settings.m_hWnd, SW_SHOW);
}

void CTouchPanelController2Dlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	
}

void CTouchPanelController2Dlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	BOOL bAxisYChanged = FALSE;
	//In fact, x values are not used when draw lines
	//If you want to use x values in any way, 
	//you may calculate point x in the way that point y is calculated.
	//see also: DrawLines(CDC* pDC);
	double x = time(0);
	double y0 = (double)settings.threshold;
	double y1 = (double)GET_RANDOM(0, 255);
	if(y0 < m_plot.GetAxisY().m_dMinValue)
	{
		m_plot.GetAxisY().m_dMinValue=y0*0.95;
		bAxisYChanged = TRUE;
	}else if(y0>m_plot.GetAxisY().m_dMaxValue)
	{
		m_plot.GetAxisY().m_dMaxValue=y0*1.05;
		bAxisYChanged = TRUE;
	}
	if(y1<m_plot.GetAxisY().m_dMinValue)
	{
		m_plot.GetAxisY().m_dMinValue=y1*0.95;
		bAxisYChanged = TRUE;
	}else if(y1>m_plot.GetAxisY().m_dMaxValue)
	{
		m_plot.GetAxisY().m_dMaxValue=y1*1.05;
		bAxisYChanged = TRUE;
	}
	
	if(bAxisYChanged)
	{
		m_plot.CalcLayout();
	}
	
	m_plot.GetLine(0).AddPoint(x, y0);
	m_plot.GetLine(1).AddPoint(x, y1);	
	
	//CDialog::OnTimer(nIDEvent);
}

void CTouchPanelController2Dlg::OnBtnStartClick() 
{
	// TODO: Add your control notification handler code here
	SetTimer(1, 1, NULL);
	m_plot.SetRate(1);
	m_plot.Start();
	
	hasStarted = true;
	setCtrlBtnStatus(hasStarted);
	
}

void CTouchPanelController2Dlg::OnBtnClearClick() 
{
	// TODO: Add your control notification handler code here
	for(int i=0;i<m_plot.GetLineCount();i++)
	{
		m_plot.GetLine(i).RemoveAllPoints();
	}
	m_plot.Invalidate();
}

void CTouchPanelController2Dlg::OnBtnStopClick() 
{
	// TODO: Add your control notification handler code here
	
	KillTimer(1);
	m_plot.Stop();
	m_plot.Invalidate();
	
	hasStarted = false;
	setCtrlBtnStatus(hasStarted);	
}
