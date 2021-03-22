#include "pch.h"
#include <vector>
#include <map>
#include "MealPlannerDlg.h"
#include "Calendar.h"
#include "Day.h"

Calendar::Calendar() : Calendar(COleDateTime::GetCurrentTime()) { }

Calendar::Calendar(COleDateTime& date) {
	setDateTime(date);
}

Calendar::Calendar(CString& fileName) : Calendar(COleDateTime::GetCurrentTime()) {
	loadFromFile(fileName);
}

// Returns the date as an int
//	Format: YYYYMMDD
int Calendar::getSelectedDateAsInt() {
	return selectedDate.GetYear() * 10000 + selectedDate.GetMonth() * 100 + selectedDate.GetDay();
}

// Creates day vector using the current date
void Calendar::buildDays() {
	if (days.count(getSelectedDateAsInt()) > 0)
		return;
	for (int i = 1; i <= monthLength; i++) {
		COleDateTime dayDate(selectedDate);
		int dayHash = getSelectedDateAsInt() + i - 1;
		dayDate.SetDate(selectedDate.GetYear(), selectedDate.GetMonth(), i);
		days[dayHash] = Day(dayDate);
	}
}

// Builds the day rects, without drawing them
void Calendar::buildDayRects(CRect& calRect) {

	// Prepare for calculations
	int count = getSelectedDateAsInt();
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
				if (count < getSelectedDateAsInt() + monthLength) {
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
	for (int i = getSelectedDateAsInt(); i < getSelectedDateAsInt() + monthLength; i++) {
		dc.Rectangle(days[i].getRect());

		// Add numbers to days
		a.Format(L"%d ", days[i].getDate().GetDay());
		dc.DrawTextW(a, &days[i].getRect(), DT_RIGHT);
	}

	// Draw meals
	for (int i = getSelectedDateAsInt(); i < getSelectedDateAsInt() + monthLength; i++) {
		days[i].paintMeals(dc);
	}

}

// Sets the current dateTime object to the first day of the month
//	as well as the month length and starting day of the week
void Calendar::setDateTime(COleDateTime date) {
	int month = date.GetMonth();
	date.SetDate(date.GetYear(), date.GetMonth(), 1);

	selectedDate = date;

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
	int year = selectedDate.GetYear();
	int month = selectedDate.GetMonth();

	// If the month is greater than 12, set it to 1 and increment year
	if (month + 1 > 12) {
		year++;
		month = 1;
	}
	else {
		month++;
	}
	selectedDate.SetDate(year, month, 1);

	setDateTime(selectedDate);
}

// Resets the dateTime object with the previous month
void Calendar::decrementMonth() {
	int year = selectedDate.GetYear();
	int month = selectedDate.GetMonth();

	// If the month is less than 1, set it to 12 and decrement year
	if (month - 1 < 1) {
		year--;
		month = 12;
	}
	else {
		month--;
	}
	selectedDate.SetDate(year, month, 1);

	setDateTime(selectedDate);
}

// Returns a string value for the selected month
CString Calendar::getMonthAsString() {
	int month = selectedDate.GetMonth();
	CString result;
	CString months[] = {
		L"January",
		L"February",
		L"March",
		L"April",
		L"May",
		L"June",
		L"July",
		L"August",
		L"September",
		L"October",
		L"November",
		L"December"};
	if (month > 0 && month < 13)
		result = months[month - 1];
	return result;
}

// Return the year of the current DateTime
int Calendar::getYear() {
	return selectedDate.GetYear();
}

//
// I/O methods
//

// Returns the entire calendar as a multi-line string to be written to a file
CString Calendar::toString() {
	CString result;
	int dateAsInt = getSelectedDateAsInt();
	for (int i = dateAsInt; i < dateAsInt + monthLength; i++) {
		if (i == dateAsInt + monthLength - 1)
			result += days[i].toString();
		else
			result += days[i].toString() + L"\n";
	}
	return result;
}

void Calendar::loadFromFile(CString& filePath) {
	CString line;
	CStdioFile file;

	file.Open(filePath, CFile::modeRead | CFile::typeText);
	BOOL eof = !file.ReadString(line);
	while (!eof && line != L"#") {
		// Prep this day's date
		COleDateTime d_date = COleDateTime::GetCurrentTime();
		int year = _ttoi(line.Mid(0, 4));
		int month = _ttoi(line.Mid(4, 2));
		int day = _ttoi(line.Mid(6, 2));
		d_date.SetDate(year, month, day);
		int dateAsInt = _ttoi(line.Mid(0, 8));

		// Create a new day at the date built
		days[dateAsInt] = Day(d_date, line);

		eof = !file.ReadString(line);
	}
	file.Close();
}

//
// Events
//

// Returns the day and true if a the Point p is in a day's Rect, new day and false otherwise
std::pair<Day&, bool> Calendar::getClickedDay(CPoint& p) {
	for (int i = getSelectedDateAsInt(); i < getSelectedDateAsInt() + monthLength; i++) {
		CRect dayRect = &days[i].getRect();
		if (p.x > dayRect.left && 
			p.x < dayRect.right && 
			p.y > dayRect.top && 
			p.y < dayRect.bottom) {

			int resulti(i);
			return std::pair<Day&, bool>(days[resulti], true);
		}
	}
	return std::pair<Day&, bool>(Day(), false);
}
