
// MealPlannerDlg.h : header file
//

#pragma once

// Know about CMealPlannerDlg
#ifndef DLG
#define DLG
class CMealPlannerDlg;
#endif

// Know everything about Calendar
#ifndef CALENDAR	
#define CALENDAR
#include "Calendar.h"
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
	Calendar calendar;
	bool hasDrawnOnce;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_staticText;
	afx_msg void OnBnClickedButtonL();
	afx_msg void OnBnClickedButtonR();
	afx_msg void OnLButtonUp(UINT, CPoint);
};
