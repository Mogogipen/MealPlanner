#include <vector>
#include "pch.h"
#include "Recipe.h"
#include "Day.h"


Day::Day() { }

Day::Day(COleDateTime date) {
	Day::date = date;
}

Day::Day(COleDateTime date, CString& fileLine) {
	Day::date = date;
	loadFromString(fileLine);
}

//
// Private methods
//

// Build the rects to be filled with text in Calendar
void Day::buildRects() {
	dishRects.clear();
	CRect previousRect;
	for (int i = 0; i < dishes.size(); i++) {

		// Build each meal Rect offset within the day Rect
		if (i == 0) {
			CRect dishRect(CRect(dayRect.left + 5, dayRect.top + 5,
				dayRect.right - 3, dayRect.top + 20));
			dishRects.push_back(dishRect);
			previousRect = &dishRects[i];
		}
		else {
			CRect dishRect(previousRect.left, previousRect.bottom,
				previousRect.right, previousRect.bottom + previousRect.Height());
			dishRects.push_back(dishRect);
			previousRect = &dishRects[i];
		}
	}
}

// Returns the Day's Date as an int
//	Format: YYYYMMDD
int Day::getDateAsInt() {
	return date.GetYear() * 10000 + date.GetMonth() * 100 + date.GetDay();
}

//
// Getters & Setters
//

// Return a copy of the day's DateTime
COleDateTime Day::getDate() {
	return date;
}

// Return a copy of the day's Rect
CRect Day::getRect() {
	return dayRect;
}

// Return how many dishes there are within a meal at the givent index
int Day::getDishCount() {
	return dishes.size();
}

// Return the name of a dish at the given meal and dish indices
CString Day::getDishName(int d_index) {
	return dishes[d_index].getTitle();
}

// Return the recipe of a dish at the given meal and dish indices
Recipe Day::getDishRecipe(int d_index) {
	return dishes[d_index];
}

// Sets the day's Rect
void Day::setRect(CRect rect) {
	dayRect = rect;
	buildRects();
}

//
// I/O methods
//

// Returns a one-line String to be written to a file
CString Day::toString() {
	CString result;
	result.Format(L"%d|", getDateAsInt());
	for (int i = 0; i < dishes.size(); i++) {
		result += dishes[i].id + L"|";
	}
	return result;
}

// Builds the day from a given string (loaded from a file)
//	Possibly only used from the constructor??
void Day::loadFromString(CString& line) {
	bool dateFound = false;
	CString dateString;

	CString rID_str;

	for (int i = 0; i < line.GetLength(); i++) {
		// If the current character is '|' the word or date is finished
		if (line[i] == '|') {
			// Mark the date as finished
			if (!dateFound)
				dateFound = true;
			else {
				// Add a new dish at the current location using the recipe id
				int rID = _ttoi(rID_str);
				dishes.push_back(Recipe(rID));
				rID_str = L"";
			}
			continue;
		}

		// Skip over the date
		if (!dateFound);
		// Build the next name
		else {
			rID_str += line[i];
		}
	}

	buildRects();
}

// Adds a new dish with the given name to the meal at the given index
void Day::addDish(Recipe newDish) {
	dishes.push_back(newDish);
}

// Removes a dish at the given meal and dish vector indices
bool Day::rmDish(int dishIndex) {
	if (dishIndex > -1 && dishIndex < dishes.size()) {
		dishes.erase(dishes.begin() + dishIndex);
		return true;
	}
	return false;
}

// Paint meal text in their respective Rects (for use in Calendar)
void Day::paintDishes(CPaintDC& dc) {
	for (int i = 0; i < dishes.size(); i++) {
		dc.DrawTextW(dishes[i].title, &dishRects[i], DT_LEFT);
	}
}