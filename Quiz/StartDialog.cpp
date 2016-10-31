// StartDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Quiz.h"
#include "StartDialog.h"


// CStartDialog dialog

IMPLEMENT_DYNAMIC(CStartDialog, CDialog)

CStartDialog::CStartDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CStartDialog::IDD, pParent)
	, filename(_T(""))
{

}

CStartDialog::~CStartDialog()
{
}

void CStartDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_QUIZCOMBO, quizes);
}


BEGIN_MESSAGE_MAP(CStartDialog, CDialog)
	ON_BN_CLICKED(IDOK, &CStartDialog::OnBnClickedOk)
END_MESSAGE_MAP()


// CStartDialog message handlers

void CStartDialog::GetQuizes(void)
{
	HANDLE hSearch = NULL;
	BOOL res = TRUE;
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(WIN32_FIND_DATA));
	for(hSearch = FindFirstFile("quiz\\*.qz", &wfd); hSearch != NULL && res; res = FindNextFile(hSearch, &wfd))
	{
		CString s = wfd.cFileName;
		quizes.AddString(s.Left(s.GetLength() - 3));
	}
}


BOOL CStartDialog::OnInitDialog(void)
{
	CDialog::OnInitDialog();

	GetQuizes();
	quizes.SetCurSel(0);
	return 0;
}

void CStartDialog::OnBnClickedOk()
{
	quizes.GetLBText(quizes.GetCurSel(), filename);
	OnOK();
}
