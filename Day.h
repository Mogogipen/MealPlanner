#pragma once

#include <vector>

struct Meal {
	CString name;
	CRect rect;
	std::vector<CString> dishes;
	std::vector<CRect> dishRects;
	std::vector<CRect> dishBtnRects;
};

class Day
{
private:
	COleDateTime date;
	CRect dayRect;
	std::vector<Meal> meals;

	void buildRects();

public:
	Day();
	Day(COleDateTime);
	COleDateTime getDate();
	CRect getRect();
	int getMealCount();
	CString getMealName(int);
	int getDishCount(int);
	CString getDishName(int, int);
	void setRect(CRect);

	void addMeal(CString);
	bool rmMeal(int);
	bool addDish(int, CString);
	bool rmDish(int, int);

	void paintMeals(CPaintDC&);
};

