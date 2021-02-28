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

	void loadFromFile(CString&);

public:
	Calendar();
	Calendar(COleDateTime&);
	Calendar(CString& fileName);

	void setDateTime(COleDateTime);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	int getYear();

	CString toString();

	void paint(CPaintDC&, CMealPlannerDlg&);

	std::pair<Day&, bool> getClickedDay(CPoint&);

};

#endif