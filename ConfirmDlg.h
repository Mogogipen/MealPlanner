#pragma once


// ConfirmDlg dialog

class ConfirmDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ConfirmDlg)

public:
	ConfirmDlg(CString, CWnd* pParent = nullptr);   // standard constructor
	virtual ~ConfirmDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CONFIRM };
#endif

protected:
	CString d_question;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
