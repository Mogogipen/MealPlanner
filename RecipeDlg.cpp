// RecipeDlg.cpp : implementation file
//

#include "pch.h"
#include "MealPlanner.h"
#include "Recipe.h"
#include "RecipeDlg.h"
#include "afxdialogex.h"


// RecipeDlg dialog

IMPLEMENT_DYNAMIC(RecipeDlg, CDialogEx)

RecipeDlg::RecipeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(_T(""))
	, m_textAuthor(_T(""))
{

}

RecipeDlg::RecipeDlg(Recipe r, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(r.getTitle())
	, m_textAuthor(r.getAuthor())
	, recipe {r}
{

}

RecipeDlg::~RecipeDlg()
{
}

Recipe RecipeDlg::getRecipe() {
	return recipe;
}

void RecipeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_TITLE, m_editTitle);
	DDX_Control(pDX, IDC_EDIT_AUTHOR, m_editAuthor);
	DDX_Text(pDX, IDC_EDIT_TITLE, m_textTitle);
	DDX_Text(pDX, IDC_EDIT_AUTHOR, m_textAuthor);
}


BEGIN_MESSAGE_MAP(RecipeDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// RecipeDlg message handlers
BOOL RecipeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Build Fonts
	normFont.CreateFont(
		14,
		0,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));

	bigFont.CreateFont(
		18,
		0,
		0,
		0,
		FW_BOLD,
		FALSE,
		FALSE,
		0,
		ANSI_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_SWISS,
		_T("Arial"));

	// Set fonts
	m_editTitle.SetFont(&bigFont);
	UpdateData(FALSE);

	return TRUE;
}

// Paint
void RecipeDlg::OnPaint() {

	Invalidate(TRUE);
	CPaintDC dc(this);

	CRect c_rect;
	GetClientRect(c_rect);
	CRect draw_rect(c_rect.left + 10, c_rect.top + 80, c_rect.right/2, c_rect.bottom - 10);

	dc.Rectangle(draw_rect);

	int rmBtn_leftMargin = 5;
	int rmBtnSize = 15;
	int ing_leftMargin = 5;
	int ingHeight = 20;

}