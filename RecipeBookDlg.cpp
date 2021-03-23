// RecipeBookDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "global.h"
#include "afxdialogex.h"
#include "Recipe.h"
#include "MealPlanner.h"
#include "RecipeBookDlg.h"
#include "RecipeDlg.h"


// RecipeBookDlg dialog

IMPLEMENT_DYNAMIC(RecipeBookDlg, CDialogEx)

RecipeBookDlg::RecipeBookDlg(CWnd* pParent /*=nullptr*/)
	: RecipeBookDlg(FALSE, pParent)
{
}

RecipeBookDlg::RecipeBookDlg(BOOL select, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
	, scrollPos{ 0 }
	, m_searchTerm(_T(""))
	, isSelect{ select }
{

}

RecipeBookDlg::~RecipeBookDlg()
{
}

Recipe RecipeBookDlg::recipeClickedID() {
	return recipes[selectedRecipeID];
}

//int RecipeBookDlg::recipeClickedID() {
//	if (select == FALSE)
//		return -1;
//	else {
//		return selectedRecipeID;
//	}
//}

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

	// Build recipe list from sql database
	try {
		std::vector<int> ids;

		// Get all ids from DB
		CStringA query;
		query.Format("SELECT idrecipe FROM recipe");
		stmt = con->createStatement();
		res = stmt->executeQuery((const char*)query);
		while (res->next()) {
			ids.push_back(res->getInt("idrecipe"));
		}

		// Create a new recipe and add it to the recipe book by id
		for (int i = 0; i < ids.size(); i++) {
			recipes.push_back(Recipe(ids[i]));
		}
	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
		MessageBox(errMsg);
		EndDialog(TRUE);
		return FALSE;
	}

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

	// If the Recipe Book is in select mode,
	//	set the selectedID and close window
	if (isSelect) {
		//selectedRecipeID = recipes[index].r_id;
		selectedRecipeID = index;
		EndDialog(IDOK);
		return;
	}

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
