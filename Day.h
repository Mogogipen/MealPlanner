#pragma once

#include <vector>
#include "Recipe.h"

class Day
{
private:
	COleDateTime date;
	CRect dayRect;
	std::vector<Recipe> dishes;
	std::vector<CRect> dishRects;

	void buildRects();
	int getDateAsInt();

	void loadFromString(CString&);

public:
	Day();
	Day(COleDateTime);
	Day(COleDateTime, CString&);

	COleDateTime getDate();
	CRect getRect();
	int getDishCount();
	CString getDishName(int);
	Recipe getDishRecipe(int);
	void setRect(CRect);

	CString toString();

	void addDish(Recipe);
	bool rmDish(int);

	void paintDishes(CPaintDC&);
};

