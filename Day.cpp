#include <vector>
#include <map>
#include "pch.h"
#include "Day.h"


Day::Day() { }

Day::Day(COleDateTime date) {
	Day::date = date;
}

void Day::buildRects() {
	CRect previousRect;
	for (int i = 0; i < meals.size(); i++) {

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
	}
}

void Day::buildEditRects() {

}

COleDateTime Day::getDate() {
	return date;
}

CRect Day::getRect() {
	return dayRect;
}

int Day::getMealCount() {
	return meals.size();
}

CString Day::getMealName(int index) {
	return meals[index].name;
}

int Day::getDishCount(int index) {
	return meals[index].dishes.size();
}

CString Day::getDishName(int m_index, int d_index) {
	return meals[m_index].dishes[d_index];
}

void Day::setRect(CRect rect) {
	dayRect = rect;
	buildRects();
}

void Day::addMeal(CString mealName) {
	Meal newMeal;
	newMeal.name = mealName;
	meals.push_back(newMeal);

	buildRects();
}

bool Day::addDish(CString& mealName, CString dishName) {
	Meal meal;
	meal.name = "";
	for (int i = 0; i < meals.size(); i++) {
		if (mealName == meals[i].name) {
			meal = meals[i];
		}
	}
	if (meal.name == "")
		return false;

	meal.dishes.push_back(dishName);

	CRect newDishRect;
	if (meal.dishRects.size() < 1) {
		CRect rect = &meal.rect;
		newDishRect = CRect(rect.left + 3, rect.top + 5,
			rect.right - 10, rect.top + 20);
	}
	else {
		CRect bottomRect = meal.dishRects[meal.dishRects.size() - 1];
		newDishRect = CRect(bottomRect.left, bottomRect.bottom,
			bottomRect.right, bottomRect.bottom + bottomRect.Height());
	}
	meal.dishRects.push_back(newDishRect);

	return true;
}

void Day::paintMeals(CPaintDC& dc) {
	for (int i = 0; i < meals.size(); i++) {
		dc.DrawTextW(meals[i].name, &meals[i].rect, DT_LEFT);
	}
}