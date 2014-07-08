// SettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TouchPanelController2.h"
#include "SettingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SettingDlg dialog


SettingDlg::SettingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SettingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SettingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->ipAddr = "192.168.1.118";
	this->port = 8990;
	this->interval = 1000;
	this->threshold = 10;
}


void SettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SettingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SettingDlg, CDialog)
	//{{AFX_MSG_MAP(SettingDlg)
	ON_BN_CLICKED(IDC_BTN_CANCEL, OnBtnCancelClick)
	ON_BN_CLICKED(IDC_BTN_CONNECT, OnBtnConnectClick)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, OnBtnDisconnectClick)
	ON_BN_CLICKED(IDC_BTN_OK, OnBtnOkClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SettingDlg message handlers

void SettingDlg::OnBtnCancelClick() 
{
	// TODO: Add your control notification handler code here
	CTouchPanelControllerApp::getInstance().close();
	setConBtnStates(!CTouchPanelControllerApp::getInstance().isServerConnected());
}

void SettingDlg::OnBtnConnectClick() 
{
	// TODO: Add your control notification handler code here
	char str_ip[20], str_port[6];
	((CEdit *)GetDlgItem(IDC_EDT_IPADDR))->GetWindowText(str_ip, 20);
	((CEdit *)GetDlgItem(IDC_EDT_PORT))->GetWindowText(str_port, 6);
	
	string t_ipAddr = string(str_ip);
	int t_port = atoi(str_port);
	
	
	CTouchPanelControllerApp::getInstance().setIpAdder(t_ipAddr);
	CTouchPanelControllerApp::getInstance().setPort(t_port);
	string result = CTouchPanelControllerApp::getInstance().initialize();
	
	if(result.compare("SUCCESS")){
		MessageBox(result.c_str(), "连接成功", MB_OK);
		setConBtnStates(!CTouchPanelControllerApp::getInstance().isServerConnected());
		
		// Only all things are right, just reocrd this infos
		ipAddr = string(str_ip);
		port = atoi(str_port);
	} else{
		MessageBox(result.c_str(), "连接失败", MB_OK);
	}	
}

void SettingDlg::OnBtnDisconnectClick() 
{
	// TODO: Add your control notification handler code here
	char str_interval[10];
	itoa(interval, str_interval, 10);
	((CEdit *)GetDlgItem(IDC_EDT_INTERVAL))->SetWindowText(str_interval);
	
	char str_threshold[4];
	itoa(threshold, str_threshold, 10);
	((CEdit *)GetDlgItem(IDC_EDT_THRESHOLD))->SetWindowText(str_threshold);	
}

void SettingDlg::OnBtnOkClick() 
{
	// TODO: Add your control notification handler code here
	char str_interval[10];
	((CEdit *)GetDlgItem(IDC_EDT_INTERVAL))->GetWindowText(str_interval, 9);
	
	char str_threshold[4];
	((CEdit *)GetDlgItem(IDC_EDT_THRESHOLD))->GetWindowText(str_threshold, 3);
	
	unsigned long t_interval = atoi(str_interval);
	unsigned long t_threshold = atoi(str_threshold);
	
	this->interval = t_interval;
	this->threshold = t_threshold;
	
	MessageBox("参数设置成功", "设置成功", MB_OK);	
}

void SettingDlg::setConBtnStates(bool status){
	((CButton *)GetDlgItem(IDC_BTN_CONNECT))->EnableWindow(!status);
	((CButton *)GetDlgItem(IDC_BTN_DISCONNECT))->EnableWindow(status);
}


BOOL SettingDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	((CEdit *)GetDlgItem(IDC_EDT_IPADDR))->SetWindowText(ipAddr.c_str());
	
	char str_port[6];
	itoa(port, str_port, 10);
	((CEdit *)GetDlgItem(IDC_EDT_PORT))->SetWindowText(str_port);
	
	char str_interval[10];
	itoa(interval, str_interval, 10);
	((CEdit *)GetDlgItem(IDC_EDT_INTERVAL))->SetWindowText(str_interval);
	
	char str_threshold[4];
	itoa(threshold, str_threshold, 10);
	((CEdit *)GetDlgItem(IDC_EDT_THRESHOLD))->SetWindowText(str_threshold);
	
	setConBtnStates(CTouchPanelControllerApp::getInstance().isServerConnected());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
