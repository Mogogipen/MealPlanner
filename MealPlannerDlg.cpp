
// MealPlannerDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "framework.h"
#include "MealPlanner.h"
#include "MealPlannerDlg.h"
#include "afxdialogex.h"
#include "Calendar.h"

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
	m_staticText = calendar.getMonthAsString();

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
		//Clear old stuff
		Invalidate(TRUE);
		UpdateWindow();

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





void CMealPlannerDlg::OnBnClickedButtonL()
{
	// TODO: Add your control notification handler code here
	calendar.decrementMonth();
	m_staticText = calendar.getMonthAsString();

	UpdateData();
	Invalidate(TRUE);
	UpdateWindow();
}


void CMealPlannerDlg::OnBnClickedButtonR()
{
	// TODO: Add your control notification handler code here
	calendar.incrementMonth();
	m_staticText = calendar.getMonthAsString();

	UpdateData();
	Invalidate(TRUE);
	UpdateWindow();
}
