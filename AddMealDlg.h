#pragma once

class AddMealDlg : public CDialog
{
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMEAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

public:
	AddMealDlg();
	AddMealDlg(int);
	~AddMealDlg();

	CString GetMealName();

	CString d_staticText;
	CString d_newMealName;
};

