#pragma once

#include <vector>

class Recipe
{

private:
	CString title;
	CRect titleRect;
	CString author;
	CRect authorRect;
	std::vector<CString> ingredients;
	std::vector<CRect> ingredientRects;

public:
	Recipe();
	Recipe(int);
	Recipe(CString, CString, std::vector<CString>);
	~Recipe();

	void buildRect(int, int, int, int, int);
	void paint(CPaintDC&);

	CRect mainRect;
};