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
	CRect getBaseDayRect(CRect&);
	void buildDayRects(CRect&);

public:
	Calendar();
	Calendar(COleDateTime&);
	void setDateTime(COleDateTime);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	int getYear();

	void paint(CPaintDC&, CMealPlannerDlg&);

	std::pair<Day&, int> getClickedDay(CPoint&);

};

#endif