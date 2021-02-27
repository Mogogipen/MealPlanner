#include <vector>
#include "pch.h"
#include "Day.h"


Day::Day() { }

Day::Day(COleDateTime date) {
	Day::date = date;
}

// Build the rects to be filled with text
void Day::buildRects() {
	CRect previousRect;
	for (int i = 0; i < meals.size(); i++) {

		// Build each meal Rect
		if (i == 0) {
			meals[i].rect = CRect(dayRect.left + 5, dayRect.top + 5,
				dayRect.right - 3, dayRect.top + 20);
			previousRect = &meals[i].rect;
		}
		else {
			meals[i].rect = CRect(previousRect.left, previousRect.bottom,
				previousRect.right, previousRect.bottom + previousRect.Height());
			previousRect = &meals[i].rect;
		}

		for (int j = 0; j < meals[i].dishes.size(); j++) {

			// Build each dish Rect and add it to the vector of Rects
			CRect newDishRect;
			if (meals[i].dishRects.size() < 1) {
				CRect rect = &meals[i].rect;
				newDishRect = CRect(rect.left + 3, rect.top + 5,
					rect.right - 10, rect.top + 20);
			}
			else {
				CRect bottomRect = meals[i].dishRects[meals[i].dishRects.size() - 1];
				newDishRect = CRect(bottomRect.left, bottomRect.bottom,
					bottomRect.right, bottomRect.bottom + bottomRect.Height());
			}
			meals[i].dishRects.push_back(newDishRect);
		}
	}
}

// Return a copy of the day's DateTime
COleDateTime Day::getDate() {
	return date;
}

// Return a copy of the day's Rect
CRect Day::getRect() {
	return dayRect;
}

// Return how many meals there are
int Day::getMealCount() {
	return meals.size();
}

// Return the name for a meal at the given index
CString Day::getMealName(int index) {
	return meals[index].name;
}

// Return how many dishes there are within a meal at the givent index
int Day::getDishCount(int index) {
	return meals[index].dishes.size();
}

// Return the name of a dish at the given meal and dish indices
CString Day::getDishName(int m_index, int d_index) {
	return meals[m_index].dishes[d_index];
}

// Sets the day's Rect
void Day::setRect(CRect rect) {
	dayRect = rect;
	buildRects();
}

// Adds a new meal to the day with the given name
void Day::addMeal(CString mealName) {
	Meal newMeal;
	newMeal.name = mealName;
	meals.push_back(newMeal);

	buildRects();
}

// Adds a new dish with the given name to the meal at the given index
bool Day::addDish(int mealIndex, CString dishName) {
	if (mealIndex > -1 && mealIndex < meals.size()) {
		meals[mealIndex].dishes.push_back(dishName);
		return true;
	}
	return false;
}

// Removes a meal at the given index
bool Day::rmMeal(int mealIndex) {
	if (mealIndex > -1 && mealIndex < meals.size()) {
		meals.erase(meals.begin() + mealIndex);
		return true;
	}
	return false;
}

// Removes a dish at the given meal and dish vector indices
bool Day::rmDish(int mealIndex, int dishIndex) {
	if (mealIndex > -1 && mealIndex < meals.size()) {
		if (dishIndex > -1 && dishIndex < meals[mealIndex].dishes.size()) {
			Meal& m = meals[mealIndex];
			m.dishes.erase(m.dishes.begin() + dishIndex);
			return true;
		}
	}
	return false;
}

// Paint meal text in their respective Rects (for use in Calendar)
void Day::paintMeals(CPaintDC& dc) {
	for (int i = 0; i < meals.size(); i++) {
		dc.DrawTextW(meals[i].name, &meals[i].rect, DT_LEFT);
	}
}