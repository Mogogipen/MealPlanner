#pragma once

class AddStringDlg : public CDialog
{
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_GET_STR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL OnInitDialog();
	CString d_wndName;
	CString d_stringCaptured;
	CString d_lblText;

public:
	AddStringDlg(CString, CString, CWnd* pParent = nullptr);
	~AddStringDlg();

	CString GetInput();
};

