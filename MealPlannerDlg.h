
// MealPlannerDlg.h : header file
//

#pragma once

#include <vector>

#ifndef CALENDAR	
#define CALENDAR
class Calendar;
#endif

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


//
// My additions
//
public:
	Calendar *calendar;

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
	afx_msg void OnDtnDatetimechangeDatepickerEnd(NMHDR* pNMHDR, LRESULT* pResult);

	afx_msg void OnDtnDatetimechangeDatepickerstart(NMHDR* pNMHDR, LRESULT* pResult);
};
