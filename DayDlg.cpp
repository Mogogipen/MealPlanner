// DayDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include <vector>
#include "MealPlanner.h"
#include "DayDlg.h"
#include "afxdialogex.h"
#include "Day.h"
#include "AddMealDlg.h"


// DayDlg dialog

IMPLEMENT_DYNAMIC(DayDlg, CDialog)

DayDlg::DayDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_DAY, pParent)
	, m_staticDate(_T(""))
	, day(Day())
{ }

DayDlg::DayDlg(Day& day_, CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_DAY, pParent)
	, day(day_)
{
	//day = day_;
	COleDateTime date = day.getDate();
	m_staticDate.Format(L"%d/%d/%d", date.GetMonth(), date.GetDay(), date.GetYear());
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
	ON_BN_CLICKED(IDC_BUTTON_NEWMEAL, &DayDlg::OnBnClickedButtonNewmeal)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// DayDlg message handlers

void DayDlg::OnPaint() {
	
	CDialog::OnPaint();

	// Clear old paint
	Invalidate(TRUE);
	UpdateWindow();

	// Clear CRect vectors
	rmMeal_btns.clear();
	addDish_btns.clear();
	rmDish_btns.clear();
	rmDish_indices.clear();

	// Build drawing rect area
	CPaintDC dc(this);
	CRect c_rect;
	GetClientRect(c_rect);
	CRect draw_rect(c_rect);
	draw_rect.OffsetRect(c_rect.left, c_rect.top + 40);

	// Init drawing
	dc.SetBkMode(0xFF000000);
	dc.SelectObject(normFont);

	//
	// Draw meals
	//

	// Button template
	CRect btn(0, 0, 15, 15);

	// Prep rect calculations
	int m_width;
	int m_count = day.getMealCount();
	if (m_count > 0)
		m_width = c_rect.Width() / m_count;
	else
		m_width = c_rect.Width();

	// Init rect containers
	std::vector<CRect> mealRects;
	std::vector<CRect> dishRects;
	for (int i = 0; i < m_count; i++) {
		// Draw meal
		CRect nextRect(
			draw_rect.left + (i*m_width),
			draw_rect.top,
			draw_rect.left + (i*m_width + m_width),
			draw_rect.bottom);
		mealRects.push_back(nextRect);
		dc.Rectangle(nextRect);
		dc.DrawTextW(day.getMealName(i), nextRect, DT_CENTER);

		// Build rm button
		CRect rmMeal_btn(btn);
		rmMeal_btn.OffsetRect(nextRect.left + 2, nextRect.top + 2);
		rmMeal_btns.push_back(rmMeal_btn);

		// Draw rm button
		dc.Rectangle(rmMeal_btn);
		dc.DrawTextW(L"-", rmMeal_btn, DT_CENTER);

		// Build add button
		CRect addDish_btn(btn);
		addDish_btn.OffsetRect(nextRect.right - 17, nextRect.top + 2);
		addDish_btns.push_back(addDish_btn);

		// Draw add button
		dc.Rectangle(addDish_btn);
		dc.DrawTextW(L"+", addDish_btn, DT_CENTER);

		//
		// Draw dishes
		for (int j = 0; j < day.getDishCount(i); j++) {
			CRect nextDishRect(
				nextRect.left + 5,
				nextRect.top + (j * 15),
				nextRect.right - 5,
				nextRect.top + (j * 15 + 15));
			dc.DrawTextW(day.getDishName(i, j), nextDishRect, DT_LEFT);

			// Build rm button
			CRect rmDish_btn(btn);
			rmDish_btn.OffsetRect(nextDishRect.right - 17, nextDishRect.top + 2);
			rmDish_btns.push_back(rmDish_btn);
			rmDish_indices.push_back(int(j));

			// Draw rm button
			dc.Rectangle(rmDish_btn);
			dc.DrawTextW(L"-", rmDish_btn, DT_CENTER);
		}
	}
}

void DayDlg::OnBnClickedButtonNewmeal()
{
	AddMealDlg am_dlg;
	INT_PTR nResponse = am_dlg.DoModal();
	if (nResponse == IDOK) {
		CString mealName = am_dlg.GetMealName();
		day.addMeal(mealName);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
	else if (nResponse == -1) {
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
}

void DayDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	int index = clickOnBtnSearch(point, rmMeal_btns);
	if (index < 0) {
		index = clickOnBtnSearch(point, addDish_btns);
		if (index < 0) {
			index = clickOnBtnSearch(point, rmDish_btns);
			if (index < 0);
				//return;
			// Clicked remove dish button
			else {

			}
		}
		// Clicked add dish button
		else {

		}
	}
	// Clicked remove meal
	else {

	}

	CString s;
	s.Format(L"index found: %d", index);
	MessageBox(s);
}

int DayDlg::clickOnBtnSearch(CPoint& mousePoint, std::vector<CRect>& searchList) {
	for (int i = 0; i < searchList.size(); i++) {
		if (mousePoint.x > searchList[i].left &&
			mousePoint.x < searchList[i].right &&
			mousePoint.y > searchList[i].top &&
			mousePoint.y < searchList[i].bottom)
		{
			return i;
		}
	}
	return -1;
}