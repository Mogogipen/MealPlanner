#pragma once

#include "Day.h"

// DayDlg dialog

class DayDlg : public CDialog
{
	DECLARE_DYNAMIC(DayDlg)

public:
	DayDlg(CWnd* pParent = nullptr);   // standard constructor
	DayDlg(Day&, CWnd* pParent = nullptr);
	virtual ~DayDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DAY };
#endif

private:
	Day day;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_staticDate;
};
