#include "pch.h"
#include "afxdialogex.h"
#include "framework.h"
#include "resource.h"
#include "GetStrDlg.h"

AddStringDlg::AddStringDlg(CString wndName, CString lblName, CWnd* pParent /*= nullptr*/)
	: CDialog(IDD_DIALOGMEAL)
	, d_stringCaptured(_T(""))
	, d_lblText(_T(""))
{
	d_wndName = wndName;
	d_lblText = lblName;
}

AddStringDlg::~AddStringDlg() { }

void AddStringDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEWMEAL, d_stringCaptured);
	DDX_Text(pDX, IDC_STATIC_TEXT, d_lblText);
}

BOOL AddStringDlg::OnInitDialog() {
	CDialog::OnInitDialog();

	SetWindowText(d_wndName);

	return TRUE;
}

// Return value of the user's input to be used after OK returned
CString AddStringDlg::GetInput() {
	return d_stringCaptured;
}