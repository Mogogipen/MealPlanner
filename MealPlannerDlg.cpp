
// MealPlannerDlg.cpp : implementation file
//

#include <map>
#include "pch.h"
#include "framework.h"
#include "MealPlanner.h"
#include "MealPlannerDlg.h"
#include "afxdialogex.h"
#include "Calendar.h"
#include "Day.h"
#include "DayDlg.h"

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
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CMealPlannerDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CMealPlannerDlg::OnBnClickedButtonLoad)
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

	// Build Fonts
	normFont.CreateFont(
		14,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));

	bigFont.CreateFont(
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

	// Init Month label
	GetDlgItem(IDC_STATIC_TEXT)->SetFont(&bigFont);
	reset_m_staticText();
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
		dc.SelectObject(normFont);
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
	reset_m_staticText();

	UpdateData(FALSE);
	Invalidate(TRUE);
	UpdateWindow();
}

// When the right button is clicked, increment month and display name
void CMealPlannerDlg::OnBnClickedButtonR()
{
	calendar.incrementMonth();
	reset_m_staticText();

	UpdateData(FALSE);
	Invalidate(TRUE);
	UpdateWindow();
}

// L Mouse button up event handler
//	Gets and displays the day clicked on via message box
void CMealPlannerDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	std::pair<Day&, int> day = calendar.getClickedDay(point);
	
	// If it's a valid day selected, display a dialog
	if (day.second) {

		DayDlg d_dlg(day.first);
		INT_PTR nResponse = d_dlg.DoModal();
		// Repaint window after closing
		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}

// Used to reset the Calendar text according to the current month
void CMealPlannerDlg::reset_m_staticText() {
	m_staticText.Format(L"%s %d", calendar.getMonthAsString(), calendar.getYear());
}

void CMealPlannerDlg::OnBnClickedButtonSave()
{
	CString cal_string = calendar.toString();
	MessageBox(cal_string);
	// Open explorer dialog for file name input
	const TCHAR szFilter[] = L"Meal Plan Files (*.mpl)|*.mpl|All Files (*.*)|*.*||";
	CFileDialog f_dlg(FALSE, L"mpl", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (f_dlg.DoModal() == IDOK) {
		CString sFilePath = f_dlg.GetPathName();
		
		// Write to the file
		CStdioFile file;
		file.Open(sFilePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.WriteString(L"Smiley! :)");
		file.Close();
	}
}


void CMealPlannerDlg::OnBnClickedButtonLoad()
{
	// Open explorer dialog for file name input
	const TCHAR szFilter[] = L"Meal Plan Files (*.mpl)|*.mpl|All Files (*.*)|*.*||";
	CFileDialog f_dlg(TRUE, L"mpl", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (f_dlg.DoModal() == IDOK) {
		CString sFilePath = f_dlg.GetPathName();

		// Read the file and display string in a message box
		CString mb_text;
		CStdioFile file;
		file.Open(sFilePath, CFile::modeRead | CFile::typeText);
		file.ReadString(mb_text);
		file.Close();
		MessageBox(mb_text);
	}
}
