// IngredientsDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "global.h"
#include "MealPlanner.h"
#include "afxdialogex.h"
#include "AddIngDlg.h"
#include "Calendar.h"
#include "IngredientsDlg.h"
#include <set>


// IngredientsDlg dialog

IMPLEMENT_DYNAMIC(IngredientsDlg, CDialogEx)

IngredientsDlg::IngredientsDlg(std::vector<std::pair<int, CString>>& onHandList, Calendar& calendar, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIST, pParent)
	, dateStart(COleDateTime::GetCurrentTime())
	, dateEnd(COleDateTime::GetCurrentTime())
	, c{ calendar }
{
	onHand = onHandList;
}

IngredientsDlg::~IngredientsDlg()
{
}

void IngredientsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_START, dateStart);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_END, dateEnd);
}


BEGIN_MESSAGE_MAP(IngredientsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SHOP, &IngredientsDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_HAND, &IngredientsDlg::OnBnClickedButtonHand)
	ON_BN_CLICKED(IDC_BUTTON_GENERATE, &IngredientsDlg::OnBnClickedButtonGenerate)
END_MESSAGE_MAP()

BOOL IngredientsDlg::OnInitDialog() {
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

	// Set window size
	CRect w_rect;
	this->GetWindowRect(w_rect);
	MoveWindow(w_rect.left, w_rect.top, 450, 450, FALSE);

	// Test values
	shoppingList.push_back(L"Green Beans");
	shoppingList.push_back(L"Potatoes");
	shoppingList.push_back(L"Tomato Soup");
	return TRUE;
}

// IngredientsDlg message handlers

void IngredientsDlg::OnPaint() {
	CDialogEx::OnPaint();

	// Clear old stuff
	Invalidate(TRUE);

	// Init Painter
	CPaintDC dc(this);
	dc.SetBkMode(0xFF000000);
	
	// Get the client rect
	CRect c_rect;
	GetClientRect(c_rect);

	//
	// Build Rects

	// Build left and right container Rects
	int padding = 10;
	CRect leftRect(
		c_rect.left + padding,
		c_rect.top + padding,
		c_rect.right/2 - padding/2,
		c_rect.bottom - padding);
	CRect rightRect(
		c_rect.right/2 + padding/2,
		c_rect.top + padding,
		c_rect.right - padding,
		c_rect.bottom - padding);

	// Build on-hand ingredients text Rects
	std::vector<CRect> oh_rects;
	CRect baseRect(
		leftRect.left + 20,
		leftRect.top + 20,
		leftRect.right,
		leftRect.top + 40);
	for (int i = 0; i < onHand.size(); i++) {
		baseRect.OffsetRect(0, 20);
		oh_rects.push_back(CRect(baseRect));
	}

	// Build shopping list text Rects
	std::vector<CRect> sl_rects;
	baseRect = CRect(
		rightRect.left + 20,
		rightRect.top + 20,
		rightRect.right,
		rightRect.top + 40);
	for (int i = 0; i < shoppingList.size(); i++) {
		baseRect.OffsetRect(0, 20);
		sl_rects.push_back(CRect(baseRect));
	}

	// Build remove on-hand ingredient button Rects
	rmvOH_rects.clear();
	for (int i = 0; i < oh_rects.size(); i++) {
		baseRect = CRect(0, 0, 15, 15);
		baseRect.OffsetRect(leftRect.left + 3, oh_rects[i].top);
		rmvOH_rects.push_back(CRect(baseRect));
	}

	// Build remove shopping item button Rects
	rmvSL_rects.clear();
	for (int i = 0; i < sl_rects.size(); i++) {
		baseRect = CRect(0, 0, 15, 15);
		baseRect.OffsetRect(rightRect.left + 3, sl_rects[i].top);
		rmvSL_rects.push_back(CRect(baseRect));
	}

	//
	// Draw to the dc

	// Draw container rects and titles
	dc.Rectangle(leftRect);
	dc.Rectangle(rightRect);
	dc.DrawTextW(L"On-Hand Ingredients", leftRect, DT_CENTER);
	dc.DrawTextW(L"Shopping List", rightRect, DT_CENTER);

	// Draw list items
	dc.SelectObject(normFont);
	for (int i = 0; i < oh_rects.size(); i++) {
		dc.DrawTextW(onHand[i].second, oh_rects[i], DT_LEFT);
	}
	for (int i = 0; i < sl_rects.size(); i++) {
		dc.DrawTextW(shoppingList[i], sl_rects[i], DT_LEFT);
	}

	// Draw remove buttons
	for (int i = 0; i < rmvOH_rects.size(); i++) {
		dc.Rectangle(rmvOH_rects[i]);
		dc.DrawTextW(L"-", rmvOH_rects[i], DT_CENTER);
	}
	for (int i = 0; i < rmvSL_rects.size(); i++) {
		dc.Rectangle(rmvSL_rects[i]);
		dc.DrawTextW(L"-", rmvSL_rects[i], DT_CENTER);
	}
}

// Handle Left mouse button up
//	If on a rmv button, remove the item from the list
void IngredientsDlg::OnLButtonUp(UINT nFlags, CPoint point) {
	int index = clickOnBtnSearch(point, rmvOH_rects);
	if (index < 0) {
		index = clickOnBtnSearch(point, rmvSL_rects);
		if (index < 0) return;

		// Clicked remove shopping list item button
		else {
			// Remove the ingredient selected
			shoppingList.erase(shoppingList.begin() + index);
		}
	}
	
	// Clicked remove on-hand item button
	else {
		// Remove the ingredient selected
		onHand.erase(onHand.begin() + index);
	}

	// Redraw the window if something changed
	if (index > -1) {
		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}
// Companion to OnLButtonUp()
// Returns index in the given vector if the mousePoint is in a Rect within the searchList, -1 otherwise
int IngredientsDlg::clickOnBtnSearch(CPoint& mousePoint, std::vector<CRect>& searchList) {
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

// Add an item to the on-hand ingredients button pushed
void IngredientsDlg::OnBnClickedButtonHand()
{
	AddIngDlg ai_dlg;
	INT_PTR nResponse = ai_dlg.DoModal();
	if (nResponse == IDOK) {
		// If OK, add an ingredient to the on-hand ingredients list
		std::pair<int, CString> ingredient = ai_dlg.GetIngredient();
		onHand.push_back(ingredient);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}

// Add an item to the shopping list button pushed
void IngredientsDlg::OnBnClickedButtonSave()
{
	//AddStringDlg as_dlg(L"Add to shopping list", L"Ingredient");
	//INT_PTR nResponse = as_dlg.DoModal();
	//if (nResponse == IDOK) {
	//	// If OK, add an ingredient to the shopping list
	//	CString ingredient = as_dlg.GetInput();
	//	shoppingList.push_back(ingredient);

	//	UpdateData(FALSE);
	//	Invalidate(TRUE);
	//	UpdateWindow();
	//}
}


void IngredientsDlg::OnBnClickedButtonGenerate()
{
	UpdateData(TRUE);

	if (dateStart > dateEnd) return;

	// Get all recipe IDs within selected date range
	COleDateTimeSpan dayCount = dateEnd - dateStart;
	COleDateTimeSpan day(1, 0, 0, 0);
	int days = dayCount.GetDays();
	std::set<int> recipeIDs;
	for (int i = 0; i <= days; i++) {
		std::vector<Recipe> recipes;
		int dateHash = c.getDateAsInt(dateStart);
		recipes = c.getDayRecipes(dateHash);
		for (int i = 0; i < recipes.size(); i++) {
			recipeIDs.insert(recipes[i].id);
		}
		dateStart += day;
	}

	// Copy from set to vector
	std::vector<int> r_ids(recipeIDs.size());
	std::copy(recipeIDs.begin(), recipeIDs.end(), std::back_inserter(r_ids));

	// Get all ingredient names within selected date range
	CString list;
	if (r_ids.size() <= 0) return;
	list.Format(L"%d", r_ids[0]);
	for (int i = 1; i < r_ids.size(); i++) {
		CString tmp;
		tmp.Format(L", %d", r_ids[i]);
		list += tmp;
	}

	try {
		CString query;
		query.Format(L"SELECT name FROM ingredient, recipe_has_ingredient WHERE(recipe_idrecipe) IN (%s) AND ingredient_idingredient = idingredient GROUP BY idingredient;", list);
		stmt = con->createStatement();
		res = stmt->executeQuery((const char*)(CStringA)query);
		while (res->next()) {
			CString ingredient(res->getString("name").c_str());
			shoppingList.push_back(ingredient);
		}
	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
		MessageBox(errMsg);
	}
}
