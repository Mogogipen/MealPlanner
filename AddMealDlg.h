#pragma once

class AddMealDlg : public CDialog
{
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMEAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	CString d_newMealName;

public:
	AddMealDlg(CWnd* pParent = nullptr);
	~AddMealDlg();

	CString GetMealName();
};

