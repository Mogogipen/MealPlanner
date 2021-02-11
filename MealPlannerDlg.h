
// MealPlannerDlg.h : header file
//

#pragma once


// CMealPlannerDlg dialog
class CMealPlannerDlg : public CDialogEx
{
// Construction
public:
	CMealPlannerDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MEALPLANNER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDateTimeCtrl m_DPicker;
	CString m_strDate;
	afx_msg void OnDtnDatetimechangeDatepicker(NMHDR* pNMHDR, LRESULT* pResult);

//
// My additions
//
public:
#ifndef CALENDAR_H
#define CALENDAR_H
	class Calendar;
	Calendar *calendar;
#endif
};
