#include "pch.h"
#include "Calendar.h"




void Calendar::paint(CMealPlannerDlg& m_dlg) {
	CPaintDC dc(&m_dlg);
	CRect cal_rect;
	m_dlg.GetClientRect(&cal_rect);
	cal_rect.OffsetRect(50, -50);
	dc.Rectangle(cal_rect);

}