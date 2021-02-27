#include <vector>
#include "Day.h"

#ifndef CALENDAR_H
#define CALENDAR_H

class Calendar
{
private:
	int monthLength;
	int startDay;
	COleDateTime selectedDate;
	std::map<int, Day> days;

	void buildDays();
	void buildDayRects(CRect&);
	int getSelectedDateAsInt();

public:
	Calendar();
	Calendar(COleDateTime&);
	void setDateTime(COleDateTime);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	int getYear();

	void paint(CPaintDC&, CMealPlannerDlg&);

	std::pair<Day&, bool> getClickedDay(CPoint&);

};

#endif