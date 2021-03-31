// ConfirmDlg.cpp : implementation file
//

#include "pch.h"
#include "MealPlanner.h"
#include "ConfirmDlg.h"
#include "afxdialogex.h"


// ConfirmDlg dialog

IMPLEMENT_DYNAMIC(ConfirmDlg, CDialogEx)

ConfirmDlg::ConfirmDlg(CString question, CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONFIRM, pParent)
	, d_question(question)
{

}

ConfirmDlg::~ConfirmDlg()
{
}

void ConfirmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC_TEXT, d_question);
}


BEGIN_MESSAGE_MAP(ConfirmDlg, CDialogEx)
END_MESSAGE_MAP()


// ConfirmDlg message handlers
