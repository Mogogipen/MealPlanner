// IngredientsDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "MealPlanner.h"
#include "IngredientsDlg.h"
#include "afxdialogex.h"


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
	UpdateData();

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
		leftRect.left + 10,
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
		rightRect.left + 10,
		rightRect.top + 20,
		rightRect.right,
		rightRect.top + 40);
	for (int i = 0; i < onHand.size(); i++) {
		baseRect.OffsetRect(0, 20);
		sl_rects.push_back(CRect(baseRect));
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
}