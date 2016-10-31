// QuizDlg.h : header file
//
#include "question.h"
#pragma once
#include "afxwin.h"
#include <vector>


// CQuizDlg dialog
class CQuizDlg : public CDialog
{
// Construction
public:
	CQuizDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_QUIZ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void ClearAnswers(void);
	int GetChoice(void);
	void SetQuestion();
	afx_msg void OnBnClickedPrev();
	afx_msg void OnBnClickedNext();
	void ShowResults(void);
	void SetAnswer(void);

private:
	CButton banswers[NANSWERS];
	std::vector<Question> questions;
	int n;
	CStatic tquestion;
	CStatic ganswers;

public:
	int LoadQuestions(const char * filename);
	int GetScore(void);
	CString quizfile;
private:
	void SetTitle(const char *title = 0);
private:

	void SaveChoice(void)
	{
		questions[n].choice = GetChoice();
	}
	afx_msg void OnBnClickedResults();
};
