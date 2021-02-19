#include <vector>
#include <map>
#include "pch.h"
#include "Day.h"


Day::Day(COleDateTime date) {
	Day::date = date;
}

void Day::addMeal(CString mealName) {
	Meal newMeal;
	newMeal.name = mealName;
	meals.push_back(newMeal);

	CRect newMealRect;
	if (mealRects.size() < 1) {
		newMealRect = CRect(dayRect.left+3, dayRect.top+3,
			dayRect.right-3, dayRect.top + 10);
	}
	else {
		CRect bottomRect = mealRects[mealRects.size() - 1];
		newMealRect = CRect(bottomRect.left, bottomRect.bottom,
			bottomRect.right, bottomRect.bottom + bottomRect.Height());
	}
	mealRects.push_back(newMealRect);
}

CString& Day::pointInMealRect(CPoint& mousePoint) {
	for (int i = 0; i < mealRects.size(); i++) {
		if (mousePoint.x > mealRects[i].left && mousePoint.x < mealRects[i].right
			&& mousePoint.y > mealRects[i].top && mousePoint.y < mealRects[i].bottom) {
			return meals[i].name;
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