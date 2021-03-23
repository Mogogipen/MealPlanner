// AddIngDlg.cpp : implementation file
//

#include <vector>
#include "pch.h"
#include "global.h"
#include "MealPlanner.h"
#include "AddIngDlg.h"
#include "afxdialogex.h"


// AddIngDlg dialog

IMPLEMENT_DYNAMIC(AddIngDlg, CDialogEx)

AddIngDlg::AddIngDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_ING, pParent)
{

}

AddIngDlg::~AddIngDlg()
{
}

// Returns the id of the ingredient selected
std::pair<int, CString> AddIngDlg::GetIngredient() {
	std::pair<int, CString> result;
	if (names.size() > 0) {
		result.first = ids[selected];
		result.second = names[selected];
	}
	return result;
}

void AddIngDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_comboBox);
}

BOOL AddIngDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	try {

		// SQL Query
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM ingredient");

		while (res->next()) {
			// Fill comboBox with ingredient names and add to id vector
			CString s( res->getString("name").c_str() );
			m_comboBox.AddString(s);
			names.push_back(s);
			ids.push_back( res->getInt("idingredient") );
		}

		m_comboBox.SetCurSel(0);

	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
		MessageBox(errMsg);
		EndDialog(TRUE);
		return FALSE;
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(AddIngDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO, &AddIngDlg::OnCbnSelchangeCombo)
END_MESSAGE_MAP()


// AddIngDlg message handlers

// Combo box changed event handler
// Sets the "selected" var to the idingredient of the ingredient selected
void AddIngDlg::OnCbnSelchangeCombo()
{
	selected = m_comboBox.GetCurSel();
}
