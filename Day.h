#pragma once

#include <vector>

struct Meal {
	CString name;
	std::vector<CString> dishes;
	std::vector<CRect> dishRects;
};

class Day
{
private:
	COleDateTime date;
	CRect dayRect;
	std::vector<Meal> meals;
	std::vector<CRect> mealRects; // Don't draw

	void rebuildRects();

public:
	Day();
	Day(COleDateTime);
	COleDateTime getDate();
	CRect getRect();
	void setRect(CRect);

	void addMeal(CString);
	bool addDish(CString&, CString);
	//CString& pointInMealRect(CPoint&);

	void paintMeals(CPaintDC&);
};

