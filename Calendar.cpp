#include "pch.h"
#include "Calendar.h"

Calendar::Calendar() : Calendar(COleDateTime::GetCurrentTime()) { }

Calendar::Calendar(COleDateTime& date) {
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

void Calendar::setMonthLength(int len) {
	monthLength = len;
}
