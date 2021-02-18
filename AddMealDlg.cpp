#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "resource.h"
#include "AddMealDlg.h"

AddMealDlg::AddMealDlg()
	: CDialog(IDD_DIALOGMEAL)
	, d_staticText(_T("Meal Name"))
	, d_newMealName(_T(""))
{ }

// Pass day data to the dialog
AddMealDlg::AddMealDlg(int day)
	: CDialog(IDD_DIALOGMEAL)
	, d_staticText(_T("Meal Name"))
	, d_newMealName(_T("")) {
	CString text;
	text.Format(L"%d", day);
	d_staticText = text;
}

AddMealDlg::~AddMealDlg() { }

void AddMealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, d_staticText);
	DDX_Text(pDX, IDC_EDIT_NEWMEAL, d_newMealName);
}

CString AddMealDlg::GetMealName() {
	return d_newMealName;
}