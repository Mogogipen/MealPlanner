#pragma once

#include <vector>

class Recipe
{

private:

	CRect titleRect;
	CRect authorRect;
	std::vector<CRect> ingredientRects;
	CRect instRect;

public:
	int id;
	CString title;
	CString author;
	std::vector<CString> ingredients;
	CString instructions;

	Recipe();
	Recipe(int);
	Recipe(CString, CString, std::vector<CString>, CString);
	~Recipe();

	CString getTitle();
	CString getAuthor();
	CString getInstructions();

	void buildRect(int, int, int, int, int);
	void paint(CPaintDC&);

	CRect mainRect;
};