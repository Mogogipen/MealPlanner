#pragma once

class AddMealDlg : public CDialog
{
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOGMEAL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP();

public:
	AddMealDlg();
	AddMealDlg(int);
	~AddMealDlg();

	CString GetMealName();

	CString d_staticText;
	CString d_newMealName;
};

