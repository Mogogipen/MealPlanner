#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "resource.h"
#include "AddMealDlg.h"

AddMealDlg::AddMealDlg(CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_DIALOGMEAL)
	, d_newMealName(_T(""))
{ }

AddMealDlg::~AddMealDlg() { }

void AddMealDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWMEAL, d_newMealName);
}

CString AddMealDlg::GetMealName() {
	return d_newMealName;
}