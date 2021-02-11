
// MealPlannerDlg.cpp : implementation file
//

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
	, m_strDate(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMealPlannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATEPICKER, m_DPicker);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_strDate);
}

BEGIN_MESSAGE_MAP(CMealPlannerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATEPICKER, &CMealPlannerDlg::OnDtnDatetimechangeDatepicker)
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
	SetScrollRange(1, 0, 0, TRUE);

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
		//dc.DrawIcon(x, y, m_hIcon);


	}
	else
	{
		CPaintDC dc(this);
		dc.MoveTo(0, 0);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width());
		int y = (rect.Height());
		dc.LineTo(x, y);

		calendar->paint(*this);

		CDialogEx::OnPaint();
	}

}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMealPlannerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMealPlannerDlg::OnDtnDatetimechangeDatepicker(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	CString tmp;
	GetDlgItemText(IDC_DATEPICKER, tmp);
	m_strDate = _T("Date chosen:\n") + tmp;
	UpdateData(FALSE);
	*pResult = 0;
}


