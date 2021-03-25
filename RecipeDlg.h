#pragma once


// RecipeDlg dialog

class RecipeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecipeDlg)

public:
	RecipeDlg(CWnd* pParent = nullptr);   // standard constructor
	RecipeDlg(Recipe, CWnd* pParent = nullptr);
	RecipeDlg(Recipe, BOOL, CWnd* pParent = nullptr);
	virtual ~RecipeDlg();
	Recipe getRecipe();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECIPE };
#endif

private:
	Recipe recipe;
	std::vector<int> i_ids;
	std::vector<CString> ingredients;
	std::vector<CString> qtys;
	std::vector<CRect> rmv_iRects;

	BOOL makeNew;

	CFont normFont;
	CFont bigFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedOk();
	afx_msg void OnLButtonUp(UINT, CPoint);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTitle;
	CString m_textTitle;
	CEdit m_editAuthor;
	CString m_textAuthor;
	CString m_textInstructions;
	afx_msg void OnBnClickedButtonAddIng();
};
