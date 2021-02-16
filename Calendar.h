#include "pch.h"
#include "MealPlannerDlg.h"

#ifndef CALENDAR_H
#define CALENDAR_H

class Calendar
{
private:
	int monthLength;
	int startDay;
	COleDateTime dateTime;
	CRect getDayRect(CRect&);


public:
	Calendar();
	Calendar(COleDateTime&);
	void paint(CPaintDC&, CMealPlannerDlg&);
	void incrementMonth();
	void decrementMonth();
	CString getMonthAsString();
	void setDateTime(COleDateTime);

};

#endif