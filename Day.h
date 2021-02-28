#pragma once

#include <vector>

struct Meal {
	CString name;
	CRect rect;
	std::vector<CString> dishes;
};

class Day
{
private:
	COleDateTime date;
	CRect dayRect;
	std::vector<Meal> meals;

	void buildRects();
	int getDateAsInt();

	void loadFromString(CString&);

public:
	Day();
	Day(COleDateTime);
	Day(COleDateTime, CString&);

	COleDateTime getDate();
	CRect getRect();
	int getMealCount();
	CString getMealName(int);
	int getDishCount(int);
	CString getDishName(int, int);
	void setRect(CRect);

	CString toString();

	void addMeal(CString);
	bool rmMeal(int);
	bool addDish(int, CString);
	bool rmDish(int, int);

	void paintMeals(CPaintDC&);
};

