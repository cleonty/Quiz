#pragma once
#include "afxwin.h"



// CStartDialog dialog

class CStartDialog : public CDialog
{
	DECLARE_DYNAMIC(CStartDialog)

public:
	CStartDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CStartDialog();

// Dialog Data
	enum { IDD = IDD_STARTDIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox quizes;
public:
	void GetQuizes(void);
public:
	afx_msg void OnBnClickedButton1();
public:
	BOOL OnInitDialog(void);
public:
	CString filename;
public:
	afx_msg void OnBnClickedOk();
};
