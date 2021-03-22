#pragma once


// AddIngDlg dialog
#include <vector>

class AddIngDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddIngDlg)

public:
	AddIngDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~AddIngDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_ING };
#endif

protected:
	CComboBox m_comboBox;
	int selected;
	std::vector<int> ids;
	std::vector<CString> names;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnCbnSelchangeCombo();

public:
	std::pair<int, CString> GetIngredient();

};
