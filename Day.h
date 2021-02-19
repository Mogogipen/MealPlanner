#pragma once

#include <vector>

struct Meal {
	CString name;
	CRect rect;
	CRect editRect;
	CRect btnRect;
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
	void buildEditRects();

public:
	Day();
	Day(COleDateTime);
	COleDateTime getDate();
	CRect getRect();
	void setRect(CRect);

	void addMeal(CString);
	bool addDish(CString&, CString);

	void paintMeals(CPaintDC&);
};

