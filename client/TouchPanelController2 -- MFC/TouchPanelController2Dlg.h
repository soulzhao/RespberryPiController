// TouchPanelController2Dlg.h : header file
//

#if !defined(AFX_TOUCHPANELCONTROLLER2DLG_H__69BE32E8_EE54_40E6_93D6_4AD8F21AB278__INCLUDED_)
#define AFX_TOUCHPANELCONTROLLER2DLG_H__69BE32E8_EE54_40E6_93D6_4AD8F21AB278__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LineChartCtrl.h"
#include "SettingDlg.h"

#define GET_RANDOM( min, max ) ((rand() % (int)(((max)+1) - (min))) + (min))


/////////////////////////////////////////////////////////////////////////////
// CTouchPanelController2Dlg dialog

class CTouchPanelController2Dlg : public CDialog
{
// Construction
public:
	CTouchPanelController2Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTouchPanelController2Dlg)
	enum { IDD = IDD_TOUCHPANELCONTROLLER_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTouchPanelController2Dlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTouchPanelController2Dlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnFileExitClick();
	afx_msg void OnFileExportClick();
	afx_msg void OnToolSettingClick();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnStartClick();
	afx_msg void OnBtnClearClick();
	afx_msg void OnBtnStopClick();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CLineChartCtrl m_plot;
	SettingDlg settings;
	
	
	CRect m_rectBtns;
	CRect m_rectOldWindow;
	CRect m_rectOldPlotWindow;
	
	bool hasStarted;
	void setCtrlBtnStatus(bool status);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOUCHPANELCONTROLLER2DLG_H__69BE32E8_EE54_40E6_93D6_4AD8F21AB278__INCLUDED_)
