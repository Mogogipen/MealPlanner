// IngredientsDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "MealPlanner.h"
#include "IngredientsDlg.h"
#include "afxdialogex.h"
#include "GetStrDlg.h"


// IngredientsDlg dialog

IMPLEMENT_DYNAMIC(IngredientsDlg, CDialogEx)

IngredientsDlg::IngredientsDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIST, pParent)
{
}

IngredientsDlg::~IngredientsDlg()
{
}

void IngredientsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(IngredientsDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BUTTON_SHOP, &IngredientsDlg::OnBnClickedButtonShop)
	ON_BN_CLICKED(IDC_BUTTON_HAND, &IngredientsDlg::OnBnClickedButtonHand)
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

	// Set window size?
	//CRect w_rect;
	//GetWindowRect(w_rect);
	//SetWindowPos(NULL, 0, 0, w_rect.right, w_rect.bottom, 0);

	// Test values
	onHand.push_back(L"Salt");
	onHand.push_back(L"Milk");
	onHand.push_back(L"Ground Beef");
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
		dc.DrawTextW(onHand[i], oh_rects[i], DT_LEFT);
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
	
}

// Add an item to the on-hand ingredients button pushed
void IngredientsDlg::OnBnClickedButtonHand()
{
	AddStringDlg as_dlg(L"Add an ingredient", L"Ingredient");
	INT_PTR nResponse = as_dlg.DoModal();
	if (nResponse == IDOK) {
		// If OK, add an ingredient to the on-hand ingredients list
		CString ingredient = as_dlg.GetMealName();
		onHand.push_back(ingredient);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}

// Add an item to the shopping list button pushed
void IngredientsDlg::OnBnClickedButtonShop()
{
	AddStringDlg as_dlg(L"Add to shopping list", L"Ingredient");
	INT_PTR nResponse = as_dlg.DoModal();
	if (nResponse == IDOK) {
		// If OK, add an ingredient to the shopping list
		CString ingredient = as_dlg.GetMealName();
		shoppingList.push_back(ingredient);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}
