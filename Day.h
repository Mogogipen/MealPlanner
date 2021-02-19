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

public:
	Day(COleDateTime);
	void addMeal(CString);
	CString& pointInMealRect(CPoint&);
	COleDateTime getDate();
	CRect getRect();
	void setRect(CRect);
	bool addDish(CString&, CString);
};

