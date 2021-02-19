#include <vector>
#include <map>
#include "pch.h"
#include "Day.h"


Day::Day() { }

Day::Day(COleDateTime date) {
	Day::date = date;
}

void Day::rebuildRects() {
	CRect previousRect;
	for (int i = 0; i < mealRects.size(); i++) {

		if (i == 0) {
			mealRects[i] = CRect(dayRect.left + 5, dayRect.top + 10,
				dayRect.right - 3, dayRect.top + 30);
			previousRect = &mealRects[i];
		}
		else {
			mealRects[i] = CRect(previousRect.left, previousRect.bottom,
				previousRect.right, previousRect.bottom + previousRect.Height());
			previousRect = &mealRects[i];
		}
	}
}

COleDateTime Day::getDate() {
	return date;
}

CRect Day::getRect() {
	return dayRect;
}

void Day::setRect(CRect rect) {
	dayRect = rect;
	rebuildRects();
}

void Day::addMeal(CString mealName) {
	Meal newMeal;
	newMeal.name = mealName;
	meals.push_back(newMeal);

	CRect newMealRect;
	mealRects.push_back(newMealRect);

	rebuildRects();
}

bool Day::addDish(CString& mealName, CString dishName) {
	Meal meal;
	meal.name = "";
	int meali = -1;
	for (int i = 0; i < meals.size(); i++) {
		if (mealName == meals[i].name) {
			meal = meals[i];
			meali = i;
		}
	}
	if (meal.name == "")
		return false;

	meal.dishes.push_back(dishName);

	CRect newDishRect;
	if (meal.dishRects.size() < 1) {
		newDishRect = CRect(mealRects[meali].left + 3, mealRects[meali].top + 3,
			mealRects[meali].right - 3, mealRects[meali].top + 10);
	}
	else {
		CRect bottomRect = meal.dishRects[meal.dishRects.size() - 1];
		newDishRect = CRect(bottomRect.left, bottomRect.bottom,
			bottomRect.right, bottomRect.bottom + bottomRect.Height());
	}
	mealRects.push_back(newDishRect);

	return true;
}

//CString& Day::pointInMealRect(CPoint& mousePoint) {
//	for (int i = 0; i < mealRects.size(); i++) {
//		if (mousePoint.x > mealRects[i].left && mousePoint.x < mealRects[i].right
//			&& mousePoint.y > mealRects[i].top && mousePoint.y < mealRects[i].bottom) {
//			return meals[i].name;
//		}
//	}
//}

void Day::paintMeals(CPaintDC& dc) {
	for (int i = 0; i < mealRects.size(); i++) {
		dc.DrawTextW(meals[i].name, &mealRects[i], DT_LEFT);
	}
}