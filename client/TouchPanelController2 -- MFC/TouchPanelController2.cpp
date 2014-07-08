// TouchPanelController2.cpp : Defines the class behaviors for the application.
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
// CTouchPanelControllerApp

BEGIN_MESSAGE_MAP(CTouchPanelControllerApp, CWinApp)
	//{{AFX_MSG_MAP(CTouchPanelControllerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTouchPanelControllerApp construction

CTouchPanelControllerApp::CTouchPanelControllerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	serverConnected = false;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTouchPanelControllerApp object

CTouchPanelControllerApp theApp;
CTouchPanelControllerApp* CTouchPanelControllerApp::m_pInstance = NULL; // static member should be defined twice

CTouchPanelControllerApp &CTouchPanelControllerApp::getInstance(){
	if (CTouchPanelControllerApp::m_pInstance == NULL)  
		CTouchPanelControllerApp::m_pInstance = &theApp;  
	return *CTouchPanelControllerApp::m_pInstance;
}
/////////////////////////////////////////////////////////////////////////////
// CTouchPanelControllerApp initialization

BOOL CTouchPanelControllerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		//AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTouchPanelController2Dlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


bool CTouchPanelControllerApp::loadSocketLib(){
	int err;
	
	WORD versionRequired;
	WSADATA wsaData;
	versionRequired = MAKEWORD(1, 1);
	err = WSAStartup(versionRequired, &wsaData);
	
	if (LOBYTE( wsaData.wVersion ) != 1 || HIBYTE( wsaData.wVersion ) != 1)
		WSACleanup();
	
	bool isSuccessful = !err;
	return isSuccessful;
}

void CTouchPanelControllerApp::createSocket(){
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
}


string CTouchPanelControllerApp::startConnect(){	
	SOCKADDR_IN clientsock_in;
	clientsock_in.sin_addr.S_un.S_addr = inet_addr(ser_addr.c_str());
	clientsock_in.sin_family = AF_INET;
	clientsock_in.sin_port= htons(port);
	
	connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));
	
	char *a = "Hello, Server!";
	send(clientSocket, a, strlen(a) + 1, 0);
	
	char welcome[50];
	recv(clientSocket, welcome, strlen(welcome) + 1, 0);
	cout << "Server say: " << welcome << endl;
	string rr(welcome);
	return rr;
}

void CTouchPanelControllerApp::closeSocket(){
	closesocket(clientSocket);
	WSACleanup();
}

string CTouchPanelControllerApp::initialize(){
	if(!loadSocketLib()){
		std::cout << "Client initialize failed: load Socket lib error!" << endl;
		return false;
	}
	createSocket();
	serverConnected = true;
	return startConnect();
}

bool CTouchPanelControllerApp::sendCommand(const string cmd){
	
	string rslt = "FAILURE";
	if(sendMsg(cmd)){
		rslt = recieveMsg();
		cout << "The result is :" << rslt << endl;
	}
	return (rslt.compare("FAILURE") == 0);
}

bool CTouchPanelControllerApp::sendMsg(const string msg){
	cout << "Sending Message:" << msg << endl;
	
	send(clientSocket, msg.c_str(), strlen(msg.c_str()) + 1, 0);
	return true;
}

string CTouchPanelControllerApp::recieveMsg(){
	char result[50];
	recv(clientSocket, result, strlen(result) + 1, 0);
	string rr(result);
	return rr;
}

unsigned int CTouchPanelControllerApp::recieveData(){
	char result[5];
	recv(clientSocket, result, strlen(result) + 1, 0);
	unsigned int data = atoi(result);
	return data;
}
