#include "pch.h"
#include "Calendar.h"

Calendar::Calendar() : Calendar(COleDateTime::GetCurrentTime()) { }

Calendar::Calendar(COleDateTime& date) {
	setDateTime(date);
}

void Calendar::paint(CPaintDC& dc, CMealPlannerDlg& m_dlg) {
	
	// Build calendar rect
	CRect c_rect;
	m_dlg.GetClientRect(&c_rect);
	CRect calRect(c_rect.left+10, c_rect.top+50, c_rect.right-10, c_rect.bottom-10);

	// Build day rects
	CRect dayRect = getDayRect(calRect);
	dc.SetBkMode(0xFF000000);
	CRect dayRects[7*6];
	int dayCount = 1;
	int count = 0;
	int dayWidth = (calRect.right - calRect.left) / 7;
	int dayHeight = (calRect.bottom - calRect.top) / 6;
	for (int j = calRect.top; j < calRect.bottom-dayHeight+1; j += dayHeight) {
		for (int i = calRect.left; i < calRect.right-dayWidth+1; i += dayWidth) {
			dayRects[count] = CRect(dayRect);
			dayRects[count].OffsetRect(i, j);
			dc.Rectangle(dayRects[count]);

			// Add numbers to days
			if (count+1 >= startDay && dayCount <= monthLength) {
				CString a;
				a.Format(L"%d", dayCount);
				dc.DrawTextW(a, &dayRects[count], DT_LEFT);
				dayCount++;
			}
			count++;
		}
	}
}

CRect Calendar::getDayRect(CRect& calRect) {
	int days = 7;
	int weeks = 6;
	CRect result(0, 0, calRect.right/days, calRect.bottom/weeks);
	return result;
}

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

void Calendar::incrementMonth() {
	int year = dateTime.GetYear();
	int month = dateTime.GetMonth();
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

void Calendar::decrementMonth() {
	int year = dateTime.GetYear();
	int month = dateTime.GetMonth();
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