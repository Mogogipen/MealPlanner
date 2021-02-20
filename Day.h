#pragma once

#include <vector>

struct Meal {
	CString name;
	CRect rect;
	std::vector<CString> dishes;
	std::vector<CRect> dishRects;
};

class Day
{
private:
	COleDateTime date;
	CRect dayRect;
	std::vector<Meal> meals;

	void buildRects();
	void buildEditRects();

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
	bool addDish(CString&, CString);

	void paintMeals(CPaintDC&);
};

