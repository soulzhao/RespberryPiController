// TouchPanelController2.h : main header file for the TOUCHPANELCONTROLLER2 application
//

#if !defined(AFX_TOUCHPANELCONTROLLER2_H__C365C21F_CC23_4FDA_B43F_7FFB8F2F8B95__INCLUDED_)
#define AFX_TOUCHPANELCONTROLLER2_H__C365C21F_CC23_4FDA_B43F_7FFB8F2F8B95__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include <windows.h>
#include <string>
#include <iostream>
using namespace std;
#define WIN32_LEAN_AND_MEAN

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTouchPanelControllerApp:
// See TouchPanelController2.cpp for the implementation of this class
//

class CTouchPanelControllerApp : public CWinApp
{
public:
	CTouchPanelControllerApp();
	
	string initialize();
	void close(){closeSocket(); serverConnected = false;};
	
	bool isServerConnected(){return serverConnected;};
	
	void setPort(int p){ port = p;};
	void setIpAdder(string ip){ ser_addr = ip; };
	
	static CTouchPanelControllerApp &getInstance();
	bool sendCommand(const string cmd);
	
	class CGarbo // 它的唯一工作就是在析构函数中删除CSingleton的实例  
	{  
	public:  
		~CGarbo(){  
			if (CTouchPanelControllerApp::m_pInstance) {
				delete CTouchPanelControllerApp::m_pInstance;
				CTouchPanelControllerApp::m_pInstance = NULL;
			}
		}
	};   
	static CGarbo Garbo; // 定义一个静态成员，在程序结束时，系统会调用它的析构函数  
	static CTouchPanelControllerApp* m_pInstance;
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTouchPanelControllerApp)
	public:
		virtual BOOL InitInstance();
		//}}AFX_VIRTUAL
		
		// Implementation
		
		//{{AFX_MSG(CTouchPanelControllerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
			
	private:
		string			ser_addr;
		int				port;
		SOCKET			clientSocket;
		
		bool			serverConnected;
		bool sendMsg(const string msg);
		string recieveMsg();
		unsigned int recieveData();
		
		bool loadSocketLib();
		void createSocket();
		string startConnect();
		void closeSocket();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOUCHPANELCONTROLLER2_H__C365C21F_CC23_4FDA_B43F_7FFB8F2F8B95__INCLUDED_)
