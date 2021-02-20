// DayDlg.cpp : implementation file
//

#include "pch.h"
#include "MealPlanner.h"
#include "DayDlg.h"
#include "afxdialogex.h"
#include "Day.h"


// DayDlg dialog

IMPLEMENT_DYNAMIC(DayDlg, CDialog)

DayDlg::DayDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_DAY, pParent)
	, m_staticDate(_T(""))
{

}

DayDlg::DayDlg(Day& day, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_DAY, pParent)
{
	this->day = day;
	COleDateTime date = day.getDate();
	m_staticDate.Format(L"%d/%d/%d", date.GetMonth(), date.GetDay(), date.GetYear());
}

DayDlg::~DayDlg()
{
}

void DayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_staticDate);
}


BEGIN_MESSAGE_MAP(DayDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// DayDlg message handlers

void DayDlg::OnPaint() {
	CPaintDC dc(this);
	CRect c_rect;
	GetClientRect(c_rect);
	CRect tmpRect(c_rect);
	tmpRect.OffsetRect(c_rect.left, c_rect.top + 40);
	dc.Rectangle(tmpRect);
}