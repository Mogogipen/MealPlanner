#include "pch.h"
#include "Calendar.h"


void Calendar::paint(CPaintDC& dc, CMealPlannerDlg& m_dlg) {
	CRect c_rect;
	m_dlg.GetClientRect(&c_rect);
	CRect cal_rect(c_rect.left+10, c_rect.top+50, c_rect.right-10, c_rect.bottom-10);
	dc.Rectangle(cal_rect);
	CPoint p1(cal_rect.left, cal_rect.bottom);
	CPoint p2(cal_rect.right, cal_rect.top);
	dc.MoveTo(p1);
	dc.LineTo(p2);
}
