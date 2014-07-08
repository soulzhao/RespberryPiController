#if !defined(AFX_SETTINGDLG_H__C378C318_ABF9_421E_8214_2FA886FC29E6__INCLUDED_)
#define AFX_SETTINGDLG_H__C378C318_ABF9_421E_8214_2FA886FC29E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SettingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SettingDlg dialog

class SettingDlg : public CDialog
{
// Construction
public:
	SettingDlg(CWnd* pParent = NULL);   // standard constructor

	string ipAddr;
	unsigned int port;
	unsigned int interval;
	unsigned int threshold;
// Dialog Data
	//{{AFX_DATA(SettingDlg)
	enum { IDD = IDD_SETTINGS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SettingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SettingDlg)
	afx_msg void OnBtnCancelClick();
	afx_msg void OnBtnConnectClick();
	afx_msg void OnBtnDisconnectClick();
	afx_msg void OnBtnOkClick();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void setConBtnStates(bool status);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETTINGDLG_H__C378C318_ABF9_421E_8214_2FA886FC29E6__INCLUDED_)
