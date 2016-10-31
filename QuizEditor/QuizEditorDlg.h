// QuizEditorDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include <list>
#include "../quiz/question.h"


// CQuizEditorDlg dialog
class CQuizEditorDlg : public CDialog
{
// Construction
public:
	CQuizEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_QUIZEDITOR_DIALOG };

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
public:
	typedef std::list<Question> Questions;
	typedef Questions::iterator Qit;
private:
	Questions questions;
	Qit n;
	unsigned num;
	void ClearAll(void);
	CString question;
	CString strAnswers[NANSWERS];
	CEdit answers[NANSWERS];
	CButton banswers[NANSWERS];
	
	CString quizfile;

	void Reset(void);
	void SaveQuestion(void);
	void LoadQuestion(void);
	int GetAnswer(void) const;
	void SetAnswer(int answer);
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedPrev();
	void SetTitle();
	int SaveQuestions(void);
	afx_msg void OnBnClickedSaveas();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedClose();
	afx_msg void OnBnClickedQusetionNew();
	afx_msg void OnBnClickedQuesetionNew();
	afx_msg void OnBnClickedQuestionNew();
	afx_msg void OnBnClickedQuestionRemove();
	afx_msg void OnBnClickedQuestionClear();
	afx_msg void OnBnClickedOk();
};
