// RecipeDlg.cpp : implementation file
//

#include "pch.h"
#include "global.h"
#include "MealPlanner.h"
#include "Recipe.h"
#include "RecipeDlg.h"
#include "IngToRecDlg.h"
#include "afxdialogex.h"


// RecipeDlg dialog

IMPLEMENT_DYNAMIC(RecipeDlg, CDialogEx)

RecipeDlg::RecipeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(_T(""))
	, m_textAuthor(_T(""))
	, m_textInstructions(_T(""))
	, makeNew{TRUE}
{
}

RecipeDlg::RecipeDlg(Recipe r, CWnd* pParent)
	: CDialogEx(IDD_DIALOG_RECIPE, pParent)
	, m_textTitle(r.getTitle())
	, m_textAuthor(r.getAuthor())
	, m_textInstructions(r.getInstructions())
	, recipe {r}
	, ingredients{ recipe.ingredients }
	, qtys{ recipe.i_qtys }
	, i_ids{ recipe.i_ids }
	, makeNew{ FALSE }
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
		CString ing;
		ing = qtys[i] + " " + ingredients[i];
		dc.DrawTextW(ing, textRects[i], DT_LEFT);
		dc.Rectangle(rmv_iRects[i]);
		dc.DrawTextW(L"-", rmv_iRects[i], DT_CENTER);
	}

}

void RecipeDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_textTitle.GetLength() == 0 ||
		m_textAuthor.GetLength() == 0) {
		CString msg = L"Please enter something for the title and author.";
		MessageBox(msg);
		return;
	}

	// Update recipe
	recipe.title = m_textTitle;
	recipe.author = m_textAuthor;
	recipe.ingredients = ingredients;
	recipe.i_ids = i_ids;
	recipe.i_qtys = qtys;
	recipe.instructions = m_textInstructions;

	//
	// Update database

	try {
		// If new, add new entry to DB
		CString query;
		if (makeNew) {
			query.Format(L"INSERT INTO recipe (title, author, instructions) VALUES (\"%s\", \"%s\", \"%s\")", recipe.title, recipe.author, recipe.instructions);
			stmt = con->createStatement();
			stmt->execute((const char*)(CStringA)query);

			// Get the new recipe's id
			res = stmt->executeQuery("SELECT idrecipe FROM recipe ORDER BY idrecipe");
			int id = 0;
			while (res->next()) {
				int t_id = res->getInt("idrecipe");
				if (t_id > id)
					id = t_id;
			}
			recipe.id = id;
		}
		
		// If changing, alter entry in DB
		else {
			
			// Update recipe
			query.Format(
				L"UPDATE recipe SET title = \"%s\", author = \"%s\", instructions = \"%s\" WHERE(idrecipe = %d);",
				recipe.title, recipe.author, recipe.instructions, recipe.id);
			stmt = con->createStatement();
			stmt->execute((const char*)(CStringA)query);

			// Remove old ingredients list
			query.Format(L"DELETE FROM recipe_has_ingredient WHERE recipe_idrecipe = %d;", recipe.id);
			stmt = con->createStatement();
			stmt->execute((const char*)(CStringA)query);
		}

		// Insert all new ingredients
		for (int i = 0; i < recipe.i_ids.size(); i++) {
			query.Format(L"INSERT INTO recipe_has_ingredient (recipe_idrecipe, ingredient_idingredient, ingQty) VALUES (%d, %d, \"%s\")", recipe.id, recipe.i_ids[i], recipe.i_qtys[i]);
			stmt = con->createStatement();
			stmt->execute((const char*)(CStringA)query);
		}
	}
	catch (sql::SQLException& e) {
		CString errMsg;
		CString what(e.what());
		int errCode = e.getErrorCode();
		CString SQLState(e.getSQLStateCStr());
		errMsg.Format(L"Error: %s\nSQL Exception Code: %d, SQL State: %s", what, errCode, SQLState);
		MessageBox(errMsg);
		return;
	}

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

	i_ids.erase(i_ids.begin() + index);
	ingredients.erase(ingredients.begin() + index);
	qtys.erase(qtys.begin() + index);

	Invalidate(TRUE);
	UpdateWindow();

}


void RecipeDlg::OnBnClickedButtonAddIng()
{
	IngToRecDlg ai_dlg;
	INT_PTR nResponse = ai_dlg.DoModal();

	if (nResponse == IDOK) {
		// If OK, add an ingredient to the shopping list
		std::pair<int, CString> ingredient = ai_dlg.GetIngredient();
		i_ids.push_back(ingredient.first);
		ingredients.push_back(ingredient.second);
		qtys.push_back(ai_dlg.GetQuantity());

		Invalidate(TRUE);
		UpdateWindow();
	}
}
