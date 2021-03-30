#pragma once

class AddStringDlg : public CDialog
{
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GET_STR };
#endif

protected:
	CString d_wndName;
	CString d_stringCaptured;
	CString d_lblText;

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedOk();
public:
	AddStringDlg(CString, CString, CWnd* pParent = nullptr);
	~AddStringDlg();

	CString GetInput();
};

