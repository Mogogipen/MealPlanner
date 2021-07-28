// IngToRecDlg.cpp : implementation file
//

#include "pch.h"
#include <vector>
#include "global.h"
#include "MealPlanner.h"
#include "IngToRecDlg.h"
#include "AddStringDlg.h"
#include "afxdialogex.h"


// IngToRecDlg dialog

IMPLEMENT_DYNAMIC(IngToRecDlg, CDialogEx)

IngToRecDlg::IngToRecDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ING_TO_RECIPE, pParent)
	, m_qty(_T(""))
{

}

IngToRecDlg::~IngToRecDlg()
{
}

// Refreshes the list of ingredients
BOOL IngToRecDlg::refreshList() {

	// Clear lists
	m_comboBox.ResetContent();
	ids.clear();
	names.clear();

	try {

		// SQL Query to get all ingredients
		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM ingredient");

		while (res->next()) {
			// Fill comboBox with ingredient names and add to id vector
			CString s(res->getString("name").c_str());
			m_comboBox.AddString(s);
			names.push_back(s);
			ids.push_back(res->getInt("idingredient"));
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

// Returns the id and name of the ingredient selected
std::pair<int, CString> IngToRecDlg::GetIngredient() {
	std::pair<int, CString> result;
	if (names.size() > 0) {
		result.first = ids[selected];
		result.second = names[selected];
	}
	return result;
}

CString IngToRecDlg::GetQuantity() {
	return qty;
}

void IngToRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO, m_comboBox);
	DDX_Text(pDX, IDC_EDIT1, m_qty);
}

BOOL IngToRecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	return refreshList();
}

BEGIN_MESSAGE_MAP(IngToRecDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO, &IngToRecDlg::OnCbnSelchangeCombo)
	ON_BN_CLICKED(IDC_BUTTON1, &IngToRecDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &IngToRecDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// IngToRecDlg message handlers

// Combo box changed event handler
// Sets the "selected" var to the idingredient of the ingredient selected
void IngToRecDlg::OnCbnSelchangeCombo()
{
	selected = m_comboBox.GetCurSel();
	CString itemText;
	m_comboBox.GetLBText(selected, itemText);

	for (int i = 0; i < names.size(); i++) {
		if (itemText == names[i])
			selected = i;
	}
}


void IngToRecDlg::OnBnClickedButton1()
{
	AddStringDlg as_dlg(L"Add an ingredient", L"Ingredient:");
	INT_PTR nResponse = as_dlg.DoModal();

	if (nResponse == IDOK) {
		CString ingName = as_dlg.GetInput();

		try {

			// Insert new ingredient into ingredient table.
			CString query;
			query.Format(L"INSERT INTO ingredient (name) VALUES (\"%s\")", ingName);
			stmt = con->createStatement();
			stmt->execute((const char*)(CStringA)query);


		}
		catch (sql::SQLException& e) {
			CString errMsg;
			CString what(e.what());
			int errCode = e.getErrorCode();
			CString SQLState(e.getSQLStateCStr());
			errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
			MessageBox(errMsg);
		}

		refreshList();
	}
}


void IngToRecDlg::OnBnClickedOk()
{
	// Stop if the user failed to enter a quantity
	UpdateData(TRUE);

	if (m_qty.GetLength() == 0) {
		MessageBox(L"Please enter a quantity.");
		return;
	}
	qty = m_qty;

	CDialogEx::OnOK();
}
