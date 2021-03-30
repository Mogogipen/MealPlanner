#pragma once

#include "Recipe.h"

// RecipeBookDlg dialog

class RecipeBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecipeBookDlg)

private:
	BOOL isSelect;
	int selectedRecipe = -1;

	CFont normFont;
	CFont bigFont;

	int scrollPos;

	BOOL refreshList();
	int clickOnBtnSearch(CPoint&, std::vector<CRect>&);
	void removeRecipe(int);

public:
	RecipeBookDlg(CWnd* pParent = nullptr);   // standard constructor
	RecipeBookDlg(BOOL, CWnd* pParent = nullptr);
	virtual ~RecipeBookDlg();
	Recipe getRecipeClicked();
	std::vector<Recipe> recipes;
	std::vector<CRect> rmvRec_btns;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_searchTerm;
	afx_msg void OnLButtonUp(UINT, CPoint);
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonDown();
};
