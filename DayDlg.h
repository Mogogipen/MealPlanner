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
	CFont normFont;
	CFont bigFont;

protected:
	std::vector<CRect> rmMeal_btns;
	std::vector<CRect> addDish_btns;
	std::vector<CRect> rmDish_btns;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_staticDate;
	afx_msg void OnBnClickedButtonNewmeal();
	afx_msg void OnLButtonUp(UINT, CPoint);
};
