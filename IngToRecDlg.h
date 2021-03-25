#pragma once


// IngToRecDlg dialog

class IngToRecDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IngToRecDlg)

public:
	IngToRecDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~IngToRecDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ING_TO_RECIPE };
#endif

protected:
	CComboBox m_comboBox;
	CString m_qty;
	int selected;
	CString qty;
	std::vector<int> ids;
	std::vector<CString> names;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();

	void OnCbnSelchangeCombo();

	DECLARE_MESSAGE_MAP()
public:

	std::pair<int, CString> GetIngredient();
	CString GetQuantity();
	afx_msg void OnBnClickedButton1();
};
