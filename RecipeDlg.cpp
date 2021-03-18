// RecipeDlg.cpp : implementation file
//

#include "pch.h"
#include "MealPlanner.h"
#include "Recipe.h"
#include "RecipeDlg.h"
#include "GetStrDlg.h"
#include "afxdialogex.h"


// RecipeDlg dialog

IMPLEMENT_DYNAMIC(RecipeDlg, CDialogEx)

RecipeDlg::RecipeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(_T(""))
	, m_textAuthor(_T(""))
	, m_textInstructions(_T(""))
{

}

RecipeDlg::RecipeDlg(Recipe r, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(r.getTitle())
	, m_textAuthor(r.getAuthor())
	, recipe {r}
{
	ingredients = recipe.ingredients;
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
	DDX_Text(pDX, IDC_EDIT_INSTR, m_textInstructions);
}


BEGIN_MESSAGE_MAP(RecipeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDOK, &RecipeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_ADD_ING, &RecipeDlg::OnBnClickedButtonAddIng)
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

	// Set recipe title font
	m_editTitle.SetFont(&bigFont);

	UpdateData(FALSE);

	return TRUE;
}

// Paint
void RecipeDlg::OnPaint() {

	// Init DC
	Invalidate(TRUE);
	CPaintDC dc(this);
	dc.SelectObject(normFont);
	dc.SetBkMode(0xFF000000);

	// Build draw area
	CRect c_rect;
	GetClientRect(c_rect);
	CRect draw_rect(c_rect.left + 10, c_rect.top + 80, c_rect.right/2, c_rect.bottom - 10);

	// Draw draw area
	dc.Rectangle(draw_rect);

	//
	// Draw ingredients
	//

	// Prepare to create rects
	int topMargin = 5;
	int rmBtn_leftMargin = 5;
	int rmBtnSize = 15;
	int ing_leftMargin = 5;
	int ingHeight = 20;

	// Create ingredient rects
	//	and remove ingredient button rects.
	std::vector<CRect> textRects;
	rmv_iRects.clear();
	for (int i = 0; i < ingredients.size(); i++) {
		CRect rmBtn(
			draw_rect.left + rmBtn_leftMargin,
			draw_rect.top + i * (topMargin + ingHeight) + topMargin,
			draw_rect.left + rmBtn_leftMargin + rmBtnSize,
			draw_rect.top + i * (topMargin + ingHeight) + topMargin + rmBtnSize);
		CRect textRect(
			rmBtn.right + ing_leftMargin,
			draw_rect.top + i * (topMargin + ingHeight) + topMargin,
			draw_rect.right,
			draw_rect.top + i * (topMargin + ingHeight) + topMargin + ingHeight);
		rmv_iRects.push_back(rmBtn);
		textRects.push_back(textRect);
	}

	// Draw ingredient text within ingredient rects
	//	and remove ingredient button rects with a "-" inside.
	for (int i = 0; i < ingredients.size(); i++) {
		dc.DrawTextW(ingredients[i], textRects[i], DT_LEFT);
		dc.Rectangle(rmv_iRects[i]);
		dc.DrawTextW(L"-", rmv_iRects[i], DT_CENTER);
	}

}

void RecipeDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here

	UpdateData(TRUE);

	if (m_textTitle.GetLength() == 0 ||
		m_textAuthor.GetLength() == 0) {
		CString msg = L"Please enter something for the title and author.";
		MessageBox(msg);
		return;
	}

	recipe.title = m_textTitle;
	recipe.author = m_textAuthor;
	recipe.ingredients = ingredients;
	recipe.instructions = m_textInstructions;

	CDialogEx::OnOK();
}

void RecipeDlg::OnLButtonUp(UINT nFlags, CPoint mousePoint) {

	int index = -1;

	// Find the recipe clicked on, return otherwise
	for (int i = 0; i < rmv_iRects.size(); i++) {
		CRect r_rect = &rmv_iRects[i];
		if (mousePoint.y > r_rect.top &&
			mousePoint.y < r_rect.bottom &&
			mousePoint.x > r_rect.left &&
			mousePoint.x < r_rect.right) {

			index = i;
			break;
		}
	}
	if (index < 0) return;

	ingredients.erase(ingredients.begin() + index);

	UpdateData(FALSE);
	Invalidate(TRUE);
	UpdateWindow();

}


void RecipeDlg::OnBnClickedButtonAddIng()
{
	AddStringDlg as_dlg(L"Add an ingredient", L"Ingredient");
	INT_PTR nResponse = as_dlg.DoModal();

	if (nResponse == IDOK) {
		// If OK, add an ingredient to the shopping list
		CString ingredient = as_dlg.GetMealName();
		ingredients.push_back(ingredient);

		UpdateData(FALSE);
		Invalidate(TRUE);
		UpdateWindow();
	}
}
