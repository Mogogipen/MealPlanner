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
#include "ConfirmDlg.h"


// RecipeBookDlg dialog

IMPLEMENT_DYNAMIC(RecipeBookDlg, CDialogEx)

RecipeBookDlg::RecipeBookDlg(CWnd* pParent /*=nullptr*/)
	: RecipeBookDlg(FALSE, pParent)
{
}

RecipeBookDlg::RecipeBookDlg(BOOL select, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BOOK, pParent)
	, scrollPos{ 0 }
	, isSelect{ select }
{

}

RecipeBookDlg::~RecipeBookDlg()
{
}

BOOL RecipeBookDlg::refreshList() {
	try {
		// Clear old lists
		recipes.clear();
		rmvRec_btns.clear();

		// Get all ids from DB
		std::vector<int> ids;
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

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
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

	return TRUE;
}

// Returns index in the given vector if the mousePoint is in a Rect within the searchList, -1 otherwise
int RecipeBookDlg::clickOnBtnSearch(CPoint& mousePoint, std::vector<CRect>& searchList) {
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

// Removes the recipe at the given index from SQL and the list of Recipes
void RecipeBookDlg::removeRecipe(int index) {

	// Confirm user wants to remove a recipe
	CString question;
	question.Format(L"Are you sure you want to remove this recipe (%s)?", recipes[index].title);
	ConfirmDlg c_dlg(question);
	INT_PTR nResponse = c_dlg.DoModal();

	// If user responds no, return; otherwise, proceed
	if (nResponse == IDOK);
	else return;

	try {
		// Remove ingredient links to recipe
		int rID = recipes[index].id;
		CString query;
		query.Format(L"DELETE FROM recipe_has_ingredient WHERE recipe_idrecipe = %d;", rID);
		stmt = con->createStatement();
		stmt->execute((const char*)(CStringA)query);

		// Remove recipe entry
		query.Format(L"DELETE FROM recipe WHERE idrecipe = %d;", rID);
		stmt = con->createStatement();
		stmt->execute((const char*)(CStringA)query);
	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
		MessageBox(errMsg);
	}
	
	refreshList();
}

// Returns the Recipe clicked on
Recipe RecipeBookDlg::getRecipeClicked() {
	return recipes[selectedRecipe];
}

void RecipeBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SEARCH, searchBox);
}


BEGIN_MESSAGE_MAP(RecipeBookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_ADD, &RecipeBookDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UP, &RecipeBookDlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &RecipeBookDlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &RecipeBookDlg::OnBnClickedButtonSearch)
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

	// Init Labels
	UpdateData(FALSE);
	searchBox.SetLimitText(32);

	// Build recipe list from sql database
	refreshList();

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
		rmvRec_btns.push_back(recipes[r_index].getRmvRect());
	}

	// Paint Recipes
	for (int i = 0; i < recipes.size() && i < 6; i++) {
		// Draw based on scroll position
		int r_index = i + scrollPos * 6;
		if (r_index >= recipes.size()) break;
		recipes[r_index].paint(dc);
	}
}

void RecipeBookDlg::OnLButtonUp(UINT nFlags, CPoint mousePoint) {

	// Removes a recipe if a remove recipe button was clicked
	int index = clickOnBtnSearch(mousePoint, rmvRec_btns);
	if (index >= 0 && !isSelect) {
		removeRecipe(index);
		return;
	}

	// Opens a dlg if a recipe was clicked
	for (int i = 0; i < recipes.size(); i++) {
		CRect r_rect = &recipes[i].getRect();
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
		selectedRecipe = index;
		EndDialog(IDOK);
		return;
	}

	// Create RecipeDlg from the recipe clicked on
	RecipeDlg r_dlg(recipes[index]);
	INT_PTR nResponse = r_dlg.DoModal();

	if (nResponse == IDOK) {
		refreshList();
	}

}

void RecipeBookDlg::OnBnClickedButtonAdd()
{
	RecipeDlg r_dlg;
	INT_PTR nResponse = r_dlg.DoModal();

	if (nResponse == IDOK) {
		refreshList();
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

// Navigate down button event handler
void RecipeBookDlg::OnBnClickedButtonDown()
{
	int tmp = (scrollPos + 1) * 6 - 1;
	if (tmp < recipes.size()) {
		scrollPos++;

		Invalidate(TRUE);
		UpdateWindow();
	}
}

// Search button event handler
void RecipeBookDlg::OnBnClickedButtonSearch()
{
	CString s;
	searchBox.GetWindowTextW(s);
	searchBox.SetWindowTextW(L"");
	
	// Check for valid string (if empty refresh the recipe list)
	if (s.GetLength() == 0) refreshList();
	
	// Build search results
	std::vector<Recipe> searchResults;
	for (int i = 0; i < recipes.size(); i++) {
		if (recipes[i].getTitle().Find(s) > -1 ||
			recipes[i].getAuthor().Find(s) > -1)
			searchResults.push_back(recipes[i]);
	}
	recipes = searchResults;

	// Repaint
	Invalidate(TRUE);
	UpdateWindow();
}
