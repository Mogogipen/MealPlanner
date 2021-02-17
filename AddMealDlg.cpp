#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "resource.h"
#include "AddMealDlg.h"

AddMealDlg::AddMealDlg()
	: CDialog(IDD_DIALOGMEAL)
	, d_staticText(_T(""))
{ }

// Pass day data to the dialog
AddMealDlg::AddMealDlg(int day)
	: CDialog(IDD_DIALOGMEAL) {
	CString text;
	text.Format(L"%d", day);
	d_staticText = text;
}

AddMealDlg::~AddMealDlg() { }

void AddMealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, d_staticText);
}