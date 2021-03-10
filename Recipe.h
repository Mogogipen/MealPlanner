#pragma once

#include <vector>

class Recipe
{

private:
	CString title;
	CString author;
	std::vector<CString> ingredients;
	CString instructions;

	CRect titleRect;
	CRect authorRect;
	std::vector<CRect> ingredientRects;
	CRect instRect;

public:
	Recipe();
	Recipe(int);
	Recipe(CString, CString, std::vector<CString>, CString);
	~Recipe();

	CString getTitle();
	CString getAuthor();

	void buildRect(int, int, int, int, int);
	void paint(CPaintDC&);

	CRect mainRect;
};