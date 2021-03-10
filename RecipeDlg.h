#pragma once


// RecipeDlg dialog

class RecipeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RecipeDlg)

public:
	RecipeDlg(CWnd* pParent = nullptr);   // standard constructor
	RecipeDlg(Recipe, CWnd* pParent = nullptr);
	virtual ~RecipeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RECIPE };
#endif

private:
	Recipe recipe;
	std::vector<CString> ingredients;
	std::vector<CRect> rmv_iRects;

	CFont normFont;
	CFont bigFont;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editTitle;
	CString m_textTitle;
	CEdit m_editAuthor;
	CString m_textAuthor;
};
