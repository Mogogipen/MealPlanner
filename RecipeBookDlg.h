#pragma once

#include "Recipe.h"

// RecipeBookDlg dialog

class RecipeBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecipeBookDlg)

private:
	CFont normFont;
	CFont bigFont;

public:
	RecipeBookDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~RecipeBookDlg();
	std::vector<Recipe> recipes;

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
	afx_msg void OnBnClickedButtonAdd();
};
