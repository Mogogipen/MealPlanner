// RecipeBookDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "afxdialogex.h"
#include "Recipe.h"
#include "MealPlanner.h"
#include "RecipeBookDlg.h"
#include "RecipeDlg.h"


// RecipeBookDlg dialog

IMPLEMENT_DYNAMIC(RecipeBookDlg, CDialogEx)

RecipeBookDlg::RecipeBookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
	, m_searchTerm(_T("Search..."))
	, scrollPos{ 0 }
{
}

RecipeBookDlg::~RecipeBookDlg()
{
}

void RecipeBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SEARCH, m_searchTerm);
}


BEGIN_MESSAGE_MAP(RecipeBookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &RecipeBookDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UP, &RecipeBookDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &RecipeBookDlg::OnBnClickedButtonDown)
END_MESSAGE_MAP()

//
// RecipeBookDlg message handlers
//

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

	// Used for testing, remove upon release
	recipes.push_back(Recipe(1));
	recipes.push_back(Recipe(2));
	recipes.push_back(Recipe(3));
	recipes.push_back(Recipe(4));
	recipes.push_back(Recipe(5));
	recipes.push_back(Recipe(6));
	recipes.push_back(Recipe(7));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void RecipeBookDlg::OnPaint() {
	CDialogEx::OnPaint();

	// Clear old stuff
	Invalidate(TRUE);

	// Init DC object
	CPaintDC dc(this);
	dc.SelectObject(normFont);
	dc.SetBkMode(0xFF000000);

	CRect c_rect;
	GetClientRect(c_rect);

	CRect draw_rect(
		c_rect.left,
		c_rect.top + 50,
		c_rect.right - 25,
		c_rect.bottom);

	// Build Recipes
	int width = draw_rect.Width() / 3;
	int topMargin = 50;
	int height = 250;
	int padding = 10;
	for (int i = 0; i < recipes.size() && i < 6; i++) {
		int r_index = i + scrollPos * 6;
		if (r_index >= recipes.size()) break;
		CRect tmpRect(c_rect.left, c_rect.top, c_rect.left + width, c_rect.top + height);
		int col = i % 3;
		int row = i / 3;
		int tmpLeft = draw_rect.left + (col * width);
		int tmpTop = draw_rect.top + (row * height);
		tmpRect.OffsetRect(
			tmpLeft,
			tmpTop);
		recipes[r_index].buildRect(tmpRect.left, tmpRect.top, tmpRect.right, tmpRect.bottom, padding);
	}

	// Paint Recipes
	for (int i = 0; i < recipes.size() && i < 6; i++) {
		int r_index = i + scrollPos * 6;
		if (r_index >= recipes.size()) break;
		recipes[r_index].paint(dc);
	}
}

void RecipeBookDlg::OnLButtonUp(UINT nFlags, CPoint mousePoint) {

	int index = -1;

	// Find the recipe clicked on, return otherwise
	for (int i = 0; i < recipes.size(); i++) {
		CRect r_rect = &recipes[i].mainRect;
		if (mousePoint.y > r_rect.top &&
			mousePoint.y < r_rect.bottom &&
			mousePoint.x > r_rect.left &&
			mousePoint.x < r_rect.right) {

			index = i;
			break;
		}
	}
	if (index < 0) return;

	// Create RecipeDlg from the recipe clicked on
	RecipeDlg r_dlg(recipes[index]);
	INT_PTR nResponse = r_dlg.DoModal();

	if (nResponse == IDOK) {
		recipes[index] = r_dlg.getRecipe();

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}

}

void RecipeBookDlg::OnBnClickedButtonAdd()
{
	RecipeDlg r_dlg;
	INT_PTR nResponse = r_dlg.DoModal();

	if (nResponse == IDOK) {
		recipes.push_back(r_dlg.getRecipe());

		Invalidate(TRUE);
		UpdateWindow();
	}
}


void RecipeBookDlg::OnBnClickedButtonUp()
{
	if (scrollPos > 0) {
		scrollPos--;

		Invalidate(TRUE);
		UpdateWindow();
	}
}


void RecipeBookDlg::OnBnClickedButtonDown()
{
	int tmp = scrollPos * 6;
	if (tmp < recipes.size()) {
		scrollPos++;

		Invalidate(TRUE);
		UpdateWindow();
	}
}
