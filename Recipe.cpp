
#include <vector>
#include "pch.h"
#include "global.h"
#include "Recipe.h"

// Constructors
Recipe::Recipe()
	: id(0)
	, title(L"")
	, instructions(L"")
{
}

Recipe::Recipe(int r_id) : Recipe() {

	// Generate recipe from SQL database
	try {
		CStringA query;
		query.Format("SELECT * FROM recipe WHERE idrecipe = %d", r_id);
		stmt = con->createStatement();
		res = stmt->executeQuery((const char*)query);
		if (res->next()) {
			// Build recipe info
			id = res->getInt("idrecipe");
			title = res->getString("title").c_str();
			author = res->getString("author").c_str();
			instructions = res->getString("instructions").c_str();

			// Build recipe ingredients list
			query.Format("SELECT name, ingQty FROM ingredient, recipe_has_ingredient WHERE idingredient = ingredient_idingredient AND recipe_idrecipe = %d", id);
			res = stmt->executeQuery((const char*)query);
			while (res->next()) {
				CString line(res->getString("ingQty").c_str());
				line += res->getString("name").c_str();
				ingredients.push_back(line);
			}
		}
	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
	}
}

Recipe::Recipe(CString title, CString author, std::vector<CString> ingredients, CString instructions = L"") {
	this->title = title;
	this->author = author;
	this->ingredients = ingredients;
	this->instructions = instructions;
}

Recipe::~Recipe() { }

//
// Getters
//

CString Recipe::getTitle() {
	return title;
}
CString Recipe::getAuthor() {
	return author;
}
CString Recipe::getInstructions() {
	return instructions;
}

//
// Painting
//

// Builds the Recipe Rect (main and text rects)
void Recipe::buildRect(int left, int top, int right, int bottom, int padding) {
	// Build independant rects (main, title, author, and instructions)
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
	CString a_text = L"By: " + author;
	dc.DrawTextW(a_text, &authorRect, DT_LEFT);
	for (int i = 0; i < ingredients.size(); i++) {
		dc.DrawTextW(ingredients[i], &ingredientRects[i], DT_LEFT);
	}
}