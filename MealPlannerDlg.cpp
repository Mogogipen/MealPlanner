
// MealPlannerDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MealPlanner.h"
#include "MealPlannerDlg.h"
#include "afxdialogex.h"
#include "Calendar.h"
#include "AddMealDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMealPlannerDlg dialog



CMealPlannerDlg::CMealPlannerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MEALPLANNER_DIALOG, pParent)
	, m_staticText(_T("test"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	calendar = Calendar();
}

void CMealPlannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_staticText);
}

BEGIN_MESSAGE_MAP(CMealPlannerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_L, &CMealPlannerDlg::OnBnClickedButtonL)
	ON_BN_CLICKED(IDC_BUTTON_R, &CMealPlannerDlg::OnBnClickedButtonR)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMealPlannerDlg message handlers

BOOL CMealPlannerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// Init Month label
	CFont font;
	font.CreateFont(
		20,
		0,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));
	GetDlgItem(IDC_STATIC_TEXT)->SetFont(&font);
	m_staticText.Format(L"%s %d", calendar.getMonthAsString(), calendar.getYear());
	UpdateData(FALSE);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMealPlannerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting
		dc.MoveTo(95, 125);
		dc.LineTo(230, 125);


		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);


	}
	else
	{

		CDialogEx::OnPaint();
		// Clear old stuff
		Invalidate(TRUE);
		UpdateWindow();

		// Paint the calendar
		CPaintDC dc(this);
		calendar.paint(dc, *this);
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMealPlannerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


// When the left button is clicked, decrement month and display name
void CMealPlannerDlg::OnBnClickedButtonL()
{
	calendar.decrementMonth();
	m_staticText = calendar.getMonthAsString();

	UpdateData(FALSE);
	Invalidate(TRUE);
	UpdateWindow();
}

// When the right button is clicked, increment month and display name
void CMealPlannerDlg::OnBnClickedButtonR()
{
	calendar.incrementMonth();
	m_staticText = calendar.getMonthAsString();

	UpdateData(FALSE);
	Invalidate(TRUE);
	UpdateWindow();
}

// L Mouse button up event handler
//	Gets and displays the day clicked on via message box
// TODO: Create a dialog to get the users requested meal/dish
void CMealPlannerDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	int day = calendar.getClickedDay(point);
	
	// If it's a valid day selected, display a dialog
	if (day > 0) {
		AddMealDlg tmpDlg(day);
		INT_PTR nResponse = tmpDlg.DoModal();
		if (nResponse == IDOK) {
			CString mealName = tmpDlg.GetMealName();
			CPoint end(point.x + 50, point.y + 15);
			CRect test(point, end);
			calendar.addMeal(mealName, day);

			UpdateData(FALSE);
			Invalidate(TRUE);
			UpdateWindow();
		}
		else if (nResponse == -1) {
			TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
			TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
		}
	}
}
