#include "pch.h"
#include "Calendar.h"

Calendar::Calendar() : Calendar(COleDateTime::GetCurrentTime()) { }

Calendar::Calendar(COleDateTime& date) {
	setDateTime(date);
}

// Calendar paints itself
void Calendar::paint(CPaintDC& dc, CMealPlannerDlg& m_dlg) {
	
	// Build calendar rect
	CRect c_rect;
	m_dlg.GetClientRect(&c_rect);
	CRect calRect(c_rect.left+20, c_rect.top+70, c_rect.right-20, c_rect.bottom-20);

	//
	// Build day rects


	buildDayRects(calRect);

	CString a;
	int dayCount = 1;
	int days = 7 * 6;

	// Initialize drawing
	dc.SetBkMode(0xFF000000);
	
	// Draw each rect and day number
	// TODO: In the future maybe change to draw lines instead of rects
	for (int i = 0; i < days; i++) {
		dc.Rectangle(dayRects[i]);

		// Add numbers to days
		if (i + 1 >= startDay && dayCount <= monthLength) {
			a.Format(L"%d", dayCount);
			dc.DrawTextW(a, &dayRects[i], DT_LEFT);
			dayCount++;
		}
	}
}

// Splits the calendar rectangle into a 7 (days) by 6 (weeks) grid
CRect Calendar::getDayRect(CRect& calRect) {
	int days = 7;
	int weeks = 6;
	CRect result(0, 0, calRect.right/days, calRect.bottom/weeks);
	return result;
}

// Builds the day rects, without drawing them
void Calendar::buildDayRects(CRect& calRect) {

	// Get base dayRect
	CRect dayRect = getDayRect(calRect);

	// Prepare for calculations
	int count = 0;
	int dayWidth = (calRect.right - calRect.left) / 7;
	int dayHeight = (calRect.bottom - calRect.top) / 6;

	// i and j hold values for offset dayRect
	for (int j = calRect.top; j < calRect.bottom - dayHeight + 1; j += dayHeight) {
		for (int i = calRect.left; i < calRect.right - dayWidth + 1; i += dayWidth) {

			// Create and offset currect dayRect
			dayRects[count] = CRect(dayRect);
			dayRects[count].OffsetRect(i, j);
			count++;
		}
	}

}

// Sets the current dateTime object 
//	as well as the month length and starting day of the week
void Calendar::setDateTime(COleDateTime date) {

	dateTime = date;

	int month = date.GetMonth();
	date.SetDate(date.GetYear(), date.GetMonth(), 1);
	startDay = date.GetDayOfWeek();

	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
		monthLength = 31;
	else if (month == 2)
		monthLength = 28;
	else
		monthLength = 30;

}

// Resets the dateTime object with the next month
void Calendar::incrementMonth() {
	int year = dateTime.GetYear();
	int month = dateTime.GetMonth();

	// If the month is greater than 12, set it to 1 and increment year
	if (month + 1 > 12) {
		year++;
		month = 1;
	}
	else {
		month++;
	}
	dateTime.SetDate(year, month, 1);

	setDateTime(dateTime);
}

// Resets the dateTime object with the previous month
void Calendar::decrementMonth() {
	int year = dateTime.GetYear();
	int month = dateTime.GetMonth();

	// If the month is less than 1, set it to 12 and decrement year
	if (month - 1 < 1) {
		year--;
		month = 12;
	}
	else {
		month--;
	}
	dateTime.SetDate(year, month, 1);

	setDateTime(dateTime);
}

// Returns a string value for the selected month
CString Calendar::getMonthAsString() {
	int month = dateTime.GetMonth();
	CString result;
	if (month == 1)
		result = L"January";
	else if (month == 2)
		result = L"February";
	else if (month == 3)
		result = L"March";
	else if (month == 4)
		result = L"April";
	else if (month == 5)
		result = L"May";
	else if (month == 6)
		result = L"June";
	else if (month == 7)
		result = L"July";
	else if (month == 8)
		result = L"August";
	else if (month == 9)
		result = L"September";
	else if (month == 10)
		result = L"October";
	else if (month == 11)
		result = L"November";
	else if (month == 12)
		result = L"December";
	else
		result = L"Unknown";
	return result;
}

//
// Events
//

int Calendar::getClickedDay(CPoint& p) {
	for (int i = 0; i < 7 * 6; i++) {
		if (p.x > dayRects[i].left && 
			p.x < dayRects[i].right && 
			p.y > dayRects[i].top && 
			p.y < dayRects[i].bottom) {

			if (i >= startDay-1 && i <= monthLength)
				return (i + startDay - 2);
		}
	}
	return 0;
}