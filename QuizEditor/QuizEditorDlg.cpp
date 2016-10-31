// QuizEditorDlg.cpp : implementation file
//
#include "stdafx.h"
#include "QuizEditor.h"
#include "QuizEditorDlg.h"
#include <fstream>

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


// CQuizEditorDlg dialog




CQuizEditorDlg::CQuizEditorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuizEditorDlg::IDD, pParent)
	, questions(1, EmptyQuestion)
	, n(questions.begin())
	, num(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CQuizEditorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ANSWER1, answers[0]);
	DDX_Control(pDX, IDC_ANSWER2, answers[1]);
	DDX_Control(pDX, IDC_ANSWER3, answers[2]);
	DDX_Control(pDX, IDC_ANSWER4, answers[3]);
	DDX_Control(pDX, IDC_ANSWER5, answers[4]);

	DDX_Control(pDX, IDC_RANSWER1, banswers[0]);
	DDX_Control(pDX, IDC_RANSWER2, banswers[1]);
	DDX_Control(pDX, IDC_RANSWER3, banswers[2]);
	DDX_Control(pDX, IDC_RANSWER4, banswers[3]);
	DDX_Control(pDX, IDC_RANSWER5, banswers[4]);

	DDX_Text(pDX, IDC_QUESTION, question);

	DDX_Text(pDX, IDC_ANSWER1, strAnswers[0]);
	DDX_Text(pDX, IDC_ANSWER2, strAnswers[1]);
	DDX_Text(pDX, IDC_ANSWER3, strAnswers[2]);
	DDX_Text(pDX, IDC_ANSWER4, strAnswers[3]);
	DDX_Text(pDX, IDC_ANSWER5, strAnswers[4]);
}

BEGIN_MESSAGE_MAP(CQuizEditorDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_NEXT, &CQuizEditorDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_PREV, &CQuizEditorDlg::OnBnClickedPrev)
	ON_BN_CLICKED(IDC_SAVEAS, &CQuizEditorDlg::OnBnClickedSaveas)
	ON_BN_CLICKED(IDC_SAVE, &CQuizEditorDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_BUTTON1, &CQuizEditorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON3, &CQuizEditorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_QUESTION_NEW, &CQuizEditorDlg::OnBnClickedQuestionNew)
	ON_BN_CLICKED(IDC_QUESTION_REMOVE, &CQuizEditorDlg::OnBnClickedQuestionRemove)
	ON_BN_CLICKED(IDC_QUESTION_CLEAR, &CQuizEditorDlg::OnBnClickedQuestionClear)
	ON_BN_CLICKED(IDOK, &CQuizEditorDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CQuizEditorDlg message handlers

BOOL CQuizEditorDlg::OnInitDialog()
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
	Reset();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CQuizEditorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQuizEditorDlg::OnPaint()
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
HCURSOR CQuizEditorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CQuizEditorDlg::ClearAll(void)
{
	FOREACH(i) {
		strAnswers[i] = "";
		banswers[i].SetCheck(FALSE);
	}
	question = "";
	UpdateData(FALSE);
}



void CQuizEditorDlg::Reset(void)
{
	quizfile = "";
	questions.clear();
	questions.push_back(EmptyQuestion);
	n = questions.begin();
	num = 0;
	ClearAll();
	SetTitle();
}

void CQuizEditorDlg::SaveQuestion(void)
{
	UpdateData(TRUE);
	strcpy_s((*n).question, QUEST_SIZE, (LPCTSTR)question);
	FOREACH(i) {
		strcpy_s((*n).answers[i], ANSWER_SIZE, (LPCTSTR)strAnswers[i]);
	}
	(*n).answer = GetAnswer();
}

int CQuizEditorDlg::GetAnswer(void) const
{
	FOREACH(i) {
		if(banswers[i].GetCheck() == TRUE)
			return i;
	}
	return -1;
}

void CQuizEditorDlg::SetAnswer(int answer)
{
	FOREACH(i) banswers[i].SetCheck(FALSE);
	if(answer != -1)
		banswers[answer].SetCheck(TRUE);
}


void CQuizEditorDlg::LoadQuestion(void)
{
	question = (*n).question;
	FOREACH(i) {
		strAnswers[i] = (*n).answers[i];
	}
	SetAnswer((*n).answer);
	UpdateData(FALSE);
}


void CQuizEditorDlg::OnBnClickedNext()
{
	SaveQuestion();
	Qit end = questions.end(), last = --end;
	if(n == last) {
		return;
	}
	ClearAll();
	++n; ++num;
	LoadQuestion();
	SetTitle();
}

void CQuizEditorDlg::OnBnClickedPrev()
{
	SaveQuestion();
	if(n == questions.begin()) return;
	--n; --num;
	ClearAll();
	LoadQuestion();
	SetTitle();
}

void CQuizEditorDlg::SetTitle()
{
	CString title;
	title.Format("Редактор вопросов - [%s] - Вопрос %d из %d", quizfile, num + 1, questions.size());
	this->SetWindowTextA(title);
}

int CQuizEditorDlg::SaveQuestions(void)
{
	return questions_save(quizfile, questions);
}

void CQuizEditorDlg::OnBnClickedSaveas()
{
	CString fileName;
	static char BASED_CODE filter[] = "Файлы вопросов (*.qz)|*.qz|Все файлы (*.*)|*.*||"; 
	CFileDialog fdlg(FALSE, "qz", 0, 4|2, filter, this);
	SaveQuestion();
	if(fdlg.DoModal() == IDOK) {
		fileName = fdlg.GetPathName();
		if( questions_save(fileName, questions) < 0) {
			MessageBox("Ошибка сохранения файла вопросов", "Ошибка", MB_OK | MB_ICONERROR);
		} else {
			quizfile = fileName;
			SetTitle();
		}
	}
}

void CQuizEditorDlg::OnBnClickedSave()
{
	SaveQuestion();
	if(quizfile != "") {
		if( SaveQuestions() < 0) {
			MessageBox("Ошибка сохранения файла вопросов", "Ошибка", MB_OK | MB_ICONERROR);
			return;
		} 
	} else {
		OnBnClickedSaveas();
	}
}

void CQuizEditorDlg::OnBnClickedButton1()
{
	if(quizfile != "") {
		if(MessageBox(CString("Файл  вопросов ") + quizfile + " не сохранен.\nСохранить?", "Подтверждение", MB_YESNO | MB_ICONQUESTION) == IDYES)
			OnBnClickedSave();
	}
	Questions q;
	CString fileName;
	static char BASED_CODE filter[] = "Файлы вопросов (*.qz)|*.qz|Все файлы (*.*)|*.*||"; 
	CFileDialog fdlg(TRUE, "qz", 0, 4|2, filter, this);
	if(fdlg.DoModal() == IDOK) {
		fileName = fdlg.GetPathName();
		if(questions_load(fileName, q) < 0) {
			MessageBox("Ошибка загрузки файла вопросов", "Ошибка", MB_OK | MB_ICONERROR);
			return;
		} else {
			questions = q;
			quizfile = fileName;
			n = questions.begin(); num = 0;
			ClearAll();
			LoadQuestion();
			SetTitle();
		}
	}
}

void CQuizEditorDlg::OnBnClickedButton3()
{
	if(quizfile != "") {
		if(MessageBox(CString("Файл ") + quizfile + " не сохранен.\nСохранить?", "Подтверждение", MB_YESNO | MB_ICONQUESTION) == IDYES)
			OnBnClickedSave();
	}
	Reset();
}



void CQuizEditorDlg::OnBnClickedQuestionNew()
{
	SaveQuestion();
	Qit it = n;
	++it;
	n = questions.insert(it, EmptyQuestion);
	num++;
	LoadQuestion();
	SetTitle();
}

void CQuizEditorDlg::OnBnClickedQuestionRemove()
{
	if(questions.size() == 1) {
		OnBnClickedQuestionClear();
		return;
	}

	Qit it = n;
	if(n == questions.begin()) {
		++n;
	} else {
		--n;
		--num;
	}
	questions.erase(it);
	LoadQuestion();
	SetTitle();
}

void CQuizEditorDlg::OnBnClickedQuestionClear()
{
	ClearAll();	
}

void CQuizEditorDlg::OnBnClickedOk()
{
	if(quizfile != "") {
		if(MessageBox(CString("Файл  вопросов ") + quizfile + " не сохранен.\nСохранить?", "Подтверждение", MB_YESNO | MB_ICONQUESTION) == IDYES)
			OnBnClickedSave();
	}
	OnOK();
}
