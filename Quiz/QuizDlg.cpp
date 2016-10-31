// QuizDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Quiz.h"
#include "QuizDlg.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

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


// CQuizDlg dialog




CQuizDlg::CQuizDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuizDlg::IDD, pParent),
	n(0)
	
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuizDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_ANSWER1, banswers[0]);
	DDX_Control(pDX, IDC_ANSWER2, banswers[1]);
	DDX_Control(pDX, IDC_ANSWER3, banswers[2]);
	DDX_Control(pDX, IDC_ANSWER4, banswers[3]);
	DDX_Control(pDX, IDC_ANSWER5, banswers[4]);

	DDX_Control(pDX, IDC_QUESTION, tquestion);
	DDX_Control(pDX, IDC_ANSWERS, ganswers);
}

BEGIN_MESSAGE_MAP(CQuizDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_PREV, &CQuizDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_NEXT, &CQuizDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_RESULTS, &CQuizDlg::OnBnClickedResults)
END_MESSAGE_MAP()


// CQuizDlg message handlers

BOOL CQuizDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
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
	ClearAnswers();
	SetQuestion();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQuizDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQuizDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

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
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CQuizDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQuizDlg::ClearAnswers(void)
{
	FOREACH(i) {
		banswers[i].SetCheck(FALSE);
	}
}

int CQuizDlg::GetChoice(void)
{
	UpdateData(TRUE);
	FOREACH(i) {
		if(banswers[i].GetCheck())
			return i;
	}
	return -1;
}

void CQuizDlg::SetQuestion()
{
	tquestion.SetWindowTextA(questions[n].question);
	FOREACH(i) {
		if(questions[n].answers[i][0] != '\0') {
			banswers[i].SetWindowTextA(questions[n].answers[i]);
			banswers[i].ShowWindow(SW_SHOW);
		} else {
			banswers[i].ShowWindow(SW_HIDE);
		}
	}
	ClearAnswers();
	SetAnswer();
	SetTitle();
}

int CQuizDlg::LoadQuestions(const char *filename)
{
	return questions_load(filename, questions);
}


void CQuizDlg::OnBnClickedPrev()
{
	SaveChoice();
	if(n == 0) return;
	n--;
	SetQuestion();
}

void CQuizDlg::OnBnClickedNext()
{
	SaveChoice();
	if(n == (questions.size() - 1)) return;
	n++;
	SetQuestion();
}

void CQuizDlg::ShowResults(void)
{
	SaveChoice();
	CString msg;
	msg.Format("Вы ответили правильно на %d вопросов из %d.", GetScore(), questions.size());
	MessageBox(msg, "Результаты теста", MB_OK | MB_ICONINFORMATION);
#ifndef _DEBUG
	OnOK();
#endif
}

void CQuizDlg::SetAnswer(void)
{
	if(questions[n].choice != -1) {
		banswers[questions[n].choice].SetCheck(TRUE);
	}
}

int CQuizDlg::GetScore(void)
{
	int score = 0;
	for(unsigned i = 0; i < questions.size(); i++) {
		if(questions[i].answer == questions[i].choice)
			score++;
	}
	return score;
}


void CQuizDlg::SetTitle(const char *title)
{
	CString t;
	if(title == 0) {
		t.Format("Тест - [%s] - Вопрос %d из %d", quizfile, n + 1, questions.size());
	} else {
		t.Format("Тест - [%s] - %s", quizfile, title);
	}
	this->SetWindowTextA(t);
}

void CQuizDlg::OnBnClickedResults()
{
	ShowResults();
}
