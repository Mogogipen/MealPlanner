#pragma once

#include <vector>

class Recipe
{

private:

	CRect titleRect;
	CRect authorRect;
	CRect rmvBtn_rect;
	std::vector<CRect> ingredientRects;
	CRect instRect;

public:
	int id;
	CString title;
	CString author;
	std::vector<CString> ingredients;
	std::vector<CString> i_qtys;
	std::vector<int> i_ids;
	CString instructions;

	Recipe();
	Recipe(int);
	Recipe(CString, CString, std::vector<CString>, CString);
	~Recipe();

	CString getTitle();
	CString getAuthor();
	CString getInstructions();

	CRect buildRect(int, int, int, int, int);
	void paint(CPaintDC&);

	CRect mainRect;
};