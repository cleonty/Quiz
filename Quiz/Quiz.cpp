// Quiz.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Quiz.h"
#include "QuizDlg.h"
#include "StartDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CQuizApp

BEGIN_MESSAGE_MAP(CQuizApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CQuizApp construction

CQuizApp::CQuizApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CQuizApp object

CQuizApp theApp;


// CQuizApp initialization

BOOL CQuizApp::InitInstance()
{
	CWinApp::InitInstance();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	// of your final executable, you should remove from the following
	// the specific initialization routines you do not need
	// Change the registry key under which our settings are stored
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	INT_PTR nResponse;
	CStartDialog start;
	CString filename;

	CQuizDlg dlg;

	nResponse = start.DoModal();
	if(nResponse == IDOK) {
		filename = CString("quiz\\") + start.filename + ".qz";
		if(dlg.LoadQuestions(filename) < 0) {
				MessageBoxA(NULL, "Не удалось загрузить файл с вопросами", "Ошибка", MB_OK | MB_ICONERROR);
				return FALSE;
		}
		dlg.quizfile = start.filename;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
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
		
		return TRUE;
	} else {
		return FALSE;
	}


	
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
