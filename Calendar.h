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
	void buildDays();
	std::vector<Day> days;
	CRect dayRects[7 * 6];
	CRect getBaseDayRect(CRect&);
	void buildDayRects(CRect&);

public:
	Calendar();
	Calendar(COleDateTime&);
	void paint(CPaintDC&, CMealPlannerDlg&);
	void setDateTime(COleDateTime);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	int getYear();

	std::pair<Day, int> getClickedDay(CPoint&);

	void addMeal(CString&, int);

};

#endif