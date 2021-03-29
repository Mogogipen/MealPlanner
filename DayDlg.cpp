// DayDlg.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include <vector>
#include "MealPlanner.h"
#include "DayDlg.h"
#include "afxdialogex.h"
#include "Day.h"
#include "AddStringDlg.h"
#include "RecipeBookDlg.h"
#include "RecipeDlg.h"


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

	// Clear CRect vectors
	dishRects.clear();
	rmDish_btns.clear();

	// Build drawing rect area
	CPaintDC dc(this);
	CRect c_rect;
	GetClientRect(c_rect);
	CRect draw_rect(
		c_rect.left + 10,
		c_rect.top + 40,
		c_rect.right - 10,
		c_rect.bottom - 10);

	// Init drawing
	dc.SetBkMode(0xFF000000);
	dc.SelectObject(normFont);

	//
	// Draw Recipes

	// Build Recipes
	int width = draw_rect.Width() / 2;
	int topMargin = 50;
	int height = 250;
	int padding = 10;
	for (int i = 0; i < day.getDishCount() && i < 4; i++) {
		CRect tmpRect(c_rect.left, c_rect.top, c_rect.left + width, c_rect.top + height);
		int col = i % 2;
		int row = i / 2;
		int tmpLeft = draw_rect.left + (col * width);
		int tmpTop = draw_rect.top + (row * height);
		tmpRect.OffsetRect(
			tmpLeft,
			tmpTop);
		CRect dishRect(tmpRect.left, tmpRect.top, tmpRect.right, tmpRect.bottom);
		CRect rmvBtn_Rect = day.getDishRecipe(i).buildRect(tmpRect.left, tmpRect.top, tmpRect.right, tmpRect.bottom, padding);
		dishRects.push_back(dishRect);
		rmDish_btns.push_back(rmvBtn_Rect);
	}
	
}

// New meal button pushed
//	Opens GetStrDlg to get the meal name from the user
//	Adds a new meal to the day based on user input
void DayDlg::OnBnClickedButtonNewmeal()
{
	// Create Dlg
	RecipeBookDlg ad_dlg(TRUE);
	INT_PTR nResponse = ad_dlg.DoModal();
	if (nResponse == IDOK) {
		// If OK pushed, add dish to day's selected meal
		Recipe dishRecipe = ad_dlg.getRecipeClicked();
		day.addDish(dishRecipe);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
	else if (nResponse == -1) {
		TRACE(traceAppMsg, 0, "Warning: dialog creation failed, so application is terminating unexpectedly.\n");
		TRACE(traceAppMsg, 0, "Warning: if you are using MFC controls on the dialog, you cannot #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS.\n");
	}
}

// Left Mouse button released
//	Checks to see if the LMB was released on a pseudo button.
void DayDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	
	// Find what was clicked
	int index = clickOnBtnSearch(point, rmDish_btns);
	if (index < 0) {
		index = clickOnBtnSearch(point, dishRects);
		if (index < 0) return;

		// Clicked on a dish
		else {
			// Display the RecipeDlg for the dish's recipe
			RecipeDlg r_dlg(day.getDishRecipe(index));
			r_dlg.DoModal();
		}
	}
	// Clicked remove dish button
	else {
		// Remove the dish selected
		bool dishRmved = day.rmDish(index);
		if (!dishRmved) {
			CString s;
			s.Format(L"Bad index: %d", index);
			MessageBox(s);
		}
	}
	// Redraw if anything should have changed
	if (index > -1) {
		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}

//
// Misc Methods
//

// Returns index in the given vector if the mousePoint is in a Rect within the searchList, -1 otherwise
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