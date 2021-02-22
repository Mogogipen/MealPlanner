#include "pch.h"
#include <vector>
#include "MealPlannerDlg.h"
#include "Calendar.h"
#include "Day.h"

Calendar::Calendar() : Calendar(COleDateTime::GetCurrentTime()) { }

Calendar::Calendar(COleDateTime& date) {
	setDateTime(date);
}

// Creates day vector using the current date
void Calendar::buildDays() {
	if (days.size() > 0) {
		days.clear();
	}
	for (int i = 1; i <= monthLength; i++) {
		COleDateTime dayDate(dateTime);
		dayDate.SetDate(dateTime.GetYear(), dateTime.GetMonth(), i);
		days.push_back(Day(dayDate));
	}
}

// Builds the day rects, without drawing them
void Calendar::buildDayRects(CRect& calRect) {

	// Prepare for calculations
	int count = 0;
	int dayWidth = calRect.Width() / 7;
	int dayHeight = calRect.Height() / 6;
	bool build = false;

	// i and j hold values for offset dayRect
	for (int j = 0; j < 6; j++) {
		for (int i = 0; i < 7; i++) {
			if (i >= startDay - 1)
				build = true;

			if (build) {

				// Create and offset currect dayRect
				if (count < monthLength) {
					CRect tmpRect(
						calRect.left + i * dayWidth, 
						calRect.top + j * dayHeight,
						calRect.left + ((i + 1) * dayWidth)+1,
						calRect.top + ((j + 1) * dayHeight)+1);
					days[count].setRect(tmpRect);
				}
				count++;
			}
		}
	}

}

// Calendar paints itself
void Calendar::paint(CPaintDC& dc, CMealPlannerDlg& m_dlg) {
	
	// Build calendar rect
	CRect c_rect;
	m_dlg.GetClientRect(&c_rect);
	CRect calRect(c_rect.left+20, c_rect.top+80, c_rect.right-20, c_rect.bottom-20);

	// Build days of the week rects
	CRect weekRects[7];
	int width = calRect.Width() / 7;
	for (int i = 0; i < 7; i++) {
		weekRects[i] = CRect(
			calRect.left + (i * width),
			calRect.top - 20,
			calRect.left + ((i * width) + width),
			calRect.top);
	}

	// Draw day of the week labels with undrawn rects
	dc.DrawText(L"Sunday", &weekRects[0], DT_CENTER);
	dc.DrawText(L"Monday", &weekRects[1], DT_CENTER);
	dc.DrawText(L"Tuesday", &weekRects[2], DT_CENTER);
	dc.DrawText(L"Wednesday", &weekRects[3], DT_CENTER);
	dc.DrawText(L"Thursday", &weekRects[4], DT_CENTER);
	dc.DrawText(L"Friday", &weekRects[5], DT_CENTER);
	dc.DrawText(L"Saturday", &weekRects[6], DT_CENTER);


	//
	// Build day rects

	buildDayRects(calRect);

	CString a;

	// Initialize drawing
	dc.SetBkMode(0xFF000000);
	
	// Draw each rect and day number
	// TODO: In the future maybe change to draw lines instead of rects
	for (int i = 0; i < days.size(); i++) {
		dc.Rectangle(days[i].getRect());

		// Add numbers to days
		a.Format(L"%d ", i+1);
		dc.DrawTextW(a, &days[i].getRect(), DT_RIGHT);
	}

	// Draw meals
	for (int i = 0; i < days.size(); i++) {
		days[i].paintMeals(dc);
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

	buildDays();

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

int Calendar::getYear() {
	return dateTime.GetYear();
}

//
// Events
//

std::pair<Day&, int> Calendar::getClickedDay(CPoint& p) {
	for (int i = 0; i < days.size(); i++) {
		CRect dayRect = &days[i].getRect();
		if (p.x > dayRect.left && 
			p.x < dayRect.right && 
			p.y > dayRect.top && 
			p.y < dayRect.bottom) {

			int resulti(i);
			return std::pair<Day&, int>(days[resulti], resulti);
		}
	}
	return std::pair<Day&, int>(Day(), -1);
}
