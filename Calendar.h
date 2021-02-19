#include <vector>
#include "Day.h"

#ifndef CALENDAR_H
#define CALENDAR_H

class Calendar
{
private:
	int monthLength;
	int startDay;
	COleDateTime dateTime;

	// dayRects
	Day days[7 * 6];
	CRect getBaseDayRect(CRect&);
	void buildDayRects(CRect&);

	// Meal stuff
	CString mealTest;
	CRect mealTestRect;
	std::vector<CRect> mealRects[7 * 6];
	std::vector<CString> mealNames[7 * 6];

public:
	Calendar();
	Calendar(COleDateTime&);
	void paint(CPaintDC&, CMealPlannerDlg&);
	void setDateTime(COleDateTime);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	int getYear();

	int getClickedDay(CPoint&);

	void setMealTest(CString&);
	void setMealTestRect(CRect&);

};

#endif