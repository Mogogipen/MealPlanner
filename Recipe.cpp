
#include <vector>
#include "pch.h"
#include "Recipe.h"

Recipe::Recipe() {
	ingredients.push_back(L"Potatoes");
	ingredients.push_back(L"Green Beans");
	ingredients.push_back(L"Ground Beef");
	title = L"Shephard's Pie";
	author = L"Sharon Cornett";
}

// Used for testing, remove upon release
Recipe::Recipe(int count) : Recipe() {
	CString num;
	num.Format(L"%d", count);
	title += num;
}

Recipe::Recipe(CString title, CString author, std::vector<CString> ingredients) {
	this->title = title;
	this->author = author;
	this->ingredients = ingredients;
}

Recipe::~Recipe() { }

// Builds the Recipe Rect (main and text rects)
void Recipe::buildRect(int left, int top, int right, int bottom, int padding) {
	// Build independant rects (main, title, and author)
	mainRect = CRect(
		left + padding,
		top + padding,
		right - padding,
		bottom - padding);
	titleRect = CRect(
		mainRect.left + 5,
		mainRect.top + 5,
		mainRect.right - 5,
		mainRect.top + 30);
	authorRect = CRect(
		titleRect.left + 20, 
		titleRect.bottom + 5, 
		titleRect.right, 
		titleRect.bottom + 25);

	//
	// Build ingredient rects

	// Clear old rects
	if (!ingredientRects.empty())
		ingredientRects.clear();
	// Add padding and base values
	int i_left = mainRect.left + 10;
	int i_right = authorRect.right - 10;
	int height = 20;

	// Build rects with padding in between
	CRect previousRect;
	bool firstRect = true;
	for (int i = 0; i < ingredients.size(); i++) {
		if (firstRect) {
			previousRect = CRect(i_left, authorRect.bottom + 2, i_right, authorRect.bottom + 2 + height);
			firstRect = false;
		}
		else {
			previousRect = CRect(i_left, previousRect.bottom + 2, i_right, previousRect.bottom + 2 + height);
		}
		ingredientRects.push_back(previousRect);
	}
}

// Paints the Recipe
void Recipe::paint(CPaintDC& dc) {
	dc.Rectangle(&mainRect);
	dc.DrawTextW(title, &titleRect, DT_CENTER);
	dc.DrawTextW(author, &authorRect, DT_LEFT);
	for (int i = 0; i < ingredients.size(); i++) {
		dc.DrawTextW(ingredients[i], &ingredientRects[i], DT_LEFT);
	}
}