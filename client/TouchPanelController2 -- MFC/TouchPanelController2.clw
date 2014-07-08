; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=SettingDlg
LastTemplate=CStatic
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "TouchPanelController2.h"

ClassCount=4
Class1=CTouchPanelControllerApp
Class2=CTouchPanelController2Dlg

ResourceCount=4
Resource2=IDD_TOUCHPANELCONTROLLER_DIALOG
Resource1=IDR_MAINFRAME
Class3=SettingDlg
Class4=CLineChartCtrl
Resource3=IDD_SETTINGS
Resource4=IDR_MENU

[CLS:CTouchPanelControllerApp]
Type=0
HeaderFile=TouchPanelController2.h
ImplementationFile=TouchPanelController2.cpp
Filter=N

[CLS:CTouchPanelController2Dlg]
Type=0
HeaderFile=TouchPanelController2Dlg.h
ImplementationFile=TouchPanelController2Dlg.cpp
Filter=D
LastObject=CTouchPanelController2Dlg
BaseClass=CDialog
VirtualFilter=dWC



[CLS:SettingDlg]
Type=0
HeaderFile=SettingDlg.h
ImplementationFile=SettingDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BTN_CANCEL
VirtualFilter=dWC

[CLS:CLineChartCtrl]
Type=0
HeaderFile=LineChartCtrl.h
ImplementationFile=LineChartCtrl.cpp
BaseClass=CStatic
Filter=W
LastObject=CLineChartCtrl

[DLG:IDD_TOUCHPANELCONTROLLER_DIALOG]
Type=1
Class=CTouchPanelController2Dlg
ControlCount=4
Control1=IDC_BTN_CLEAR,button,1342242816
Control2=IDC_BTN_STOP,button,1342242816
Control3=IDC_BTN_START,button,1342242816
Control4=IDC_PLOT,static,1350701056

[DLG:IDD_SETTINGS]
Type=1
Class=SettingDlg
ControlCount=16
Control1=IDC_GRP_CONNECTION,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDT_IPADDR,edit,1350631552
Control5=IDC_EDT_PORT,edit,1350631552
Control6=IDC_BTN_CONNECT,button,1342242816
Control7=IDC_BTN_DISCONNECT,button,1342242816
Control8=IDC_GRP_PARAMSET,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_EDT_INTERVAL,edit,1350631552
Control12=IDC_EDT_THRESHOLD,edit,1350631552
Control13=IDC_BTN_OK,button,1342242816
Control14=IDC_BTN_CANCEL,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_EDIT1,edit,1350631552

[MNU:IDR_MENU]
Type=1
Class=?
Command1=IDM_FILE_EXPORT
Command2=IDM_FILE_EXIT
Command3=IDM_TOOL_SETTING
CommandCount=3

