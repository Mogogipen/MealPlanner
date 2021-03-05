// RecipeBookDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "afxdialogex.h"
#include "Recipe.h"
#include "MealPlanner.h"
#include "RecipeBookDlg.h"


// RecipeBookDlg dialog

IMPLEMENT_DYNAMIC(RecipeBookDlg, CDialogEx)

RecipeBookDlg::RecipeBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
{

}

RecipeBookDlg::~RecipeBookDlg()
{
}

void RecipeBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RecipeBookDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// RecipeBookDlg message handlers
BOOL RecipeBookDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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
	UpdateData(FALSE);

	recipes.push_back(Recipe(1));
	recipes.push_back(Recipe(2));
	recipes.push_back(Recipe(3));
	recipes.push_back(Recipe(4));
	recipes.push_back(Recipe(5));
	recipes.push_back(Recipe(6));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void RecipeBookDlg::OnPaint() {
	CDialogEx::OnPaint();

	// Clear old stuff
	Invalidate(TRUE);
	UpdateWindow();

	// Init DC object
	CPaintDC dc(this);
	dc.SelectObject(normFont);
	dc.SetBkMode(0xFF000000);

	CRect c_rect;
	GetClientRect(c_rect);

	// Build Recipes
	int width = c_rect.Width() / 3;
	int topMargin = 50;
	int height = 200;
	int padding = 10;
	for (int i = 0; i < recipes.size(); i++) {
		CRect tmpRect(c_rect.left, c_rect.top + topMargin, c_rect.left + width, c_rect.top + topMargin + height);
		int col = i % 3;
		int row = i / 3;
		int tmpLeft = c_rect.left + (col * width);
		int tmpTop = c_rect.top + (row * height);
		tmpRect.OffsetRect(
			tmpLeft,
			tmpTop);
		recipes[i].buildRect(tmpRect.left, tmpRect.top, tmpRect.right, tmpRect.bottom, padding);
	}

	// Paint Recipes
	for (int i = 0; i < recipes.size(); i++) {
		recipes[i].paint(dc);
	}
}