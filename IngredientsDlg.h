#pragma once

#include <vector>

// IngredientsDlg dialog

class IngredientsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IngredientsDlg)

public:
	IngredientsDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~IngredientsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	std::vector<CString> onHand;
	std::vector<CString> shoppingList;
	std::vector<CRect> rmvOH_rects;
	std::vector<CRect> rmvSL_rects;
	CFont normFont;
	CFont bigFont;

	int clickOnBtnSearch(CPoint&, std::vector<CRect>&);
public:
	afx_msg void OnLButtonUp(UINT, CPoint);
	afx_msg void OnBnClickedButtonShop();
	afx_msg void OnBnClickedButtonHand();
};