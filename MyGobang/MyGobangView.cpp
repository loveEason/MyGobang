
// MyGobangView.cpp : CMyGobangView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MyGobang.h"
#endif

#include "MyGobangDoc.h"
#include "MyGobangView.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyGobangView

IMPLEMENT_DYNCREATE(CMyGobangView, CView)

BEGIN_MESSAGE_MAP(CMyGobangView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMyGobangView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_COLOR, &CMyGobangView::OnColor)
	ON_COMMAND(ID_EDIT_UNDO, &CMyGobangView::OnEditUndo)
	ON_COMMAND(ID_EDIT_REDO, &CMyGobangView::OnEditRedo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, &CMyGobangView::OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(ID_EDIT_REDO, &CMyGobangView::OnUpdateEditRedo)
	ON_UPDATE_COMMAND_UI(ID_INDICATOR_NEXTCHESS, OnUpdateNextChess)
END_MESSAGE_MAP()

// CMyGobangView 构造/析构

CMyGobangView::CMyGobangView()
{
	// TODO:  在此处添加构造代码
}

CMyGobangView::~CMyGobangView()
{
}

BOOL CMyGobangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMyGobangView 绘制

void CMyGobangView::OnDraw(CDC* pDC)
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	//将背景换成绿色

	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect, color);

	//画棋盘
	CString str;
	CPen pen;

	//画水平线
	for (int i = 0; i < STRING_NUM; i++) {
		pDC->MoveTo(DISTANCE, DISTANCE + i * DISTANCE);
		pDC->LineTo(STRING_NUM * DISTANCE, DISTANCE + i * DISTANCE);
	}

	//画垂直线
	for (int i = 0; i < STRING_NUM; i++) {
		pDC->MoveTo(DISTANCE + i * DISTANCE, DISTANCE);
		pDC->LineTo(DISTANCE + i * DISTANCE, STRING_NUM * DISTANCE);
	}

	//对于放大缩小窗口时进行重绘
	CBrush blackBrush = CBrush(RGB(0, 0, 0));	//黑色画刷
	CBrush whiteBrush = CBrush(RGB(255, 255, 255));	//白色画刷

	for (int i = 1; i < STRING_NUM + 1; i++)
	{
		for (int j = 1; j < STRING_NUM + 1; j++)
		{
			CRect chess_rect(i*DISTANCE - 15, j*DISTANCE - 15, i*DISTANCE + 15, j*DISTANCE + 15);
			if (pDoc->chess[i - 1][j - 1] == 1)
			{
				CBrush *pBrush = pDC->SelectObject(&blackBrush);
				pDC->Ellipse(chess_rect);
			}
			else if (pDoc->chess[i - 1][j - 1] == 2)
			{
				CBrush *pBrush = pDC->SelectObject(&whiteBrush);
				pDC->Ellipse(chess_rect);
			}
		}
	}
	canUndo();
	canRedo();
}


// CMyGobangView 打印


void CMyGobangView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyGobangView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMyGobangView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMyGobangView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CMyGobangView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMyGobangView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMyGobangView 诊断

#ifdef _DEBUG
void CMyGobangView::AssertValid() const
{
	CView::AssertValid();
}

void CMyGobangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGobangDoc* CMyGobangView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGobangDoc)));
	return (CMyGobangDoc*)m_pDocument;
}
#endif //_DEBUG


/*
* 判断输赢
* 0：还没决出胜负
* 1：黑子获胜
* 2：白子获胜
* 3：平局
*/
int CMyGobangView::judge() {
	//判断横着的
	for (int i = 0; i < STRING_NUM - 4; i++) {
		for (int j = 0; j < STRING_NUM; j++) {
			if (pDoc->chess[i][j] == 1 && pDoc->chess[i + 1][j] == 1 && pDoc->chess[i + 2][j] == 1 && pDoc->chess[i + 3][j] == 1 && pDoc->chess[i + 4][j] == 1)
			{
				pDoc->gameover = true;
				return 1;
			}
			else if (pDoc->chess[i][j] == 2 && pDoc->chess[i + 1][j] == 2 && pDoc->chess[i + 2][j] == 2 && pDoc->chess[i + 3][j] == 2 && pDoc->chess[i + 4][j] == 2)
			{
				pDoc->gameover = true;
				return 2;
			}
		}
	}

	//判断竖着的
	for (int i = 0; i < STRING_NUM; i++)
	{
		for (int j = 0; j < STRING_NUM - 4; j++)
		{
			if (pDoc->chess[i][j] == 1 && pDoc->chess[i][j + 1] == 1 && pDoc->chess[i][j + 2] == 1 && pDoc->chess[i][j + 3] == 1 && pDoc->chess[i][j + 4] == 1)
			{
				pDoc->gameover = true;
				return 1;
			}
			else if (pDoc->chess[i][j] == 2 && pDoc->chess[i][j + 1] == 2 && pDoc->chess[i][j + 2] == 2 && pDoc->chess[i][j + 3] == 2 && pDoc->chess[i][j + 4] == 2)
			{
				pDoc->gameover = true;
				return 2;
			}
		}
	}

	//判断左斜着的
	for (int i = 0; i < STRING_NUM - 4; i++)
	{
		for (int j = 0; j < STRING_NUM - 4; j++)
		{
			if (pDoc->chess[i][j] == 1 && pDoc->chess[i + 1][j + 1] == 1 && pDoc->chess[i + 2][j + 2] == 1 && pDoc->chess[i + 3][j + 3] == 1 && pDoc->chess[i + 4][j + 4] == 1)
			{
				pDoc->gameover = true;
				return 1;
			}
			else if (pDoc->chess[i][j] == 2 && pDoc->chess[i + 1][j + 1] == 2 && pDoc->chess[i + 2][j + 2] == 2 && pDoc->chess[i + 3][j + 3] == 2 && pDoc->chess[i + 4][j + 4] == 2)
			{
				pDoc->gameover = true;
				return 2;
			}
		}
	}

	//判断右斜着的
	for (int i = 4; i < STRING_NUM; i++)
	{
		for (int j = 0; j < STRING_NUM - 4; j++)
		{
			if (pDoc->chess[i][j] == 1 && pDoc->chess[i - 1][j + 1] == 1 && pDoc->chess[i - 2][j + 2] == 1 && pDoc->chess[i - 3][j + 3] == 1 && pDoc->chess[i - 4][j + 4] == 1)
			{
				pDoc->gameover = true;
				return 1;
			}
			else if (pDoc->chess[i][j] == 2 && pDoc->chess[i - 1][j + 1] == 2 && pDoc->chess[i - 2][j + 2] == 2 && pDoc->chess[i - 3][j + 3] == 2 && pDoc->chess[i - 4][j + 4] == 2)
			{
				pDoc->gameover = true;
				return 2;
			}
		}
	}

	//当上述都不符合，且棋盘上没有空位时，说明平局,否则说明还没决出胜负
	for (int i = 0; i < STRING_NUM; i++)
	{
		for (int j = 0; j < STRING_NUM; j++)
		{
			if (pDoc->chess[i][j] != 0) {
				pDoc->gameover = false;
				return 0;
			}
		}
	}
	pDoc->gameover = true;
	return 3;
}

//判断是否可以执行Undo操作
void CMyGobangView::canUndo()
{
	if (pDoc->stk1.empty() || pDoc->stk1.size() == 1)
	{
		m_bUndo = FALSE;
	}
	else
	{
		m_bUndo = TRUE;
	}
}

//判断是否可以执行Redo操作
void CMyGobangView::canRedo()
{
	if (pDoc->stk2.empty())
	{
		m_bRedo = FALSE;
	}
	else
	{
		m_bRedo = TRUE;
	}
}



// CMyGobangView 消息处理程序


void CMyGobangView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CClientDC clentDc(this);

	CBrush blackBrush(RGB(0, 0, 0));	//黑色画刷
	CBrush whiteBrush(RGB(255, 255, 255));	//白色画刷
	struct qizi tmp_qizi;

	if (!pDoc->gameover)
	{
		x_count = 0;
		y_count = 0;
		x_remain = point.x % DISTANCE;
		y_remain = point.y % DISTANCE;
		if (x_remain<5)					//离左边交叉点较近
			x_count = point.x / DISTANCE;
		else if (x_remain>DISTANCE - 5 && x_remain < DISTANCE)	//离右边交叉点较近
			x_count = point.x / DISTANCE + 1;

		if (y_remain<5)	//离上方交叉点较近
			y_count = point.y / DISTANCE;
		else if (y_remain>DISTANCE - 5 && y_remain < DISTANCE) //离下方交叉点较近
			y_count = point.y / DISTANCE + 1;

		if (pDoc->chess[x_count - 1][y_count - 1] == 0 && (x_count != 0 && y_count != 0))
		{
			CRect chess_rect(x_count*DISTANCE - 15, y_count*DISTANCE - 15, x_count*DISTANCE + 15, y_count*DISTANCE + 15);	//一个棋子所在的矩形
			if (pDoc->heizi)
			{
				CBrush *pBrush = clentDc.SelectObject(&blackBrush);
				clentDc.Ellipse(chess_rect);
				pDoc->chess[x_count - 1][y_count - 1] = 1;
				CPoint tmp_point(x_count - 1, y_count - 1);
				tmp_qizi.point = tmp_point;
				tmp_qizi.value = 1;
				(pDoc->stk1).push(tmp_qizi);	//储存棋子信息到栈1
				pDoc->heizi = false;
			}
			else
			{
				CBrush *pBrush = clentDc.SelectObject(&whiteBrush);
				clentDc.Ellipse(chess_rect);
				pDoc->chess[x_count - 1][y_count - 1] = 2;
				CPoint tmp_point(x_count - 1, y_count - 1);
				tmp_qizi.point = tmp_point;
				tmp_qizi.value = 2;
				pDoc->stk1.push(tmp_qizi);	//储存棋子信息到栈1
				pDoc->heizi = true;
			}
			//下完一步之后判断是否可执行Undo、Redo操作
			canUndo();
			canRedo();
			//下完一步之后判断是否能决出胜负
			CString str;
			int judgement = judge();
			if (judgement == 1)
			{
				str.Format(_T("黑子获胜！"));
				MessageBox(str);
			}
			else if (judgement == 2)
			{
				str.Format(_T("白子获胜！"));
				MessageBox(str);
			}
			else if (judgement == 3)
			{
				str.Format(_T("平局！"));
				MessageBox(str);
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}




//修改棋盘颜色
void CMyGobangView::OnColor()
{
	// TODO:  在此添加命令处理程序代码
	CColorDialog colorDlg(color);	//构造颜色对话框，传入初始颜色值
	if (colorDlg.DoModal() == IDOK)	//显示颜色对话框，并判断是否点击了“确定”
	{
		color = colorDlg.GetColor();	//获取所选的颜色
	}
	Invalidate();	//重绘
}

//悔棋。每次两步
void CMyGobangView::OnEditUndo()
{
	// TODO:  在此添加命令处理程序代码
	//先检查栈2，如果栈是空，表示不能复棋,输出信息
	CString str;
	struct qizi tmp_qizi;
	//先检查栈1，如果栈是空或者为1，表示不能悔棋,输出信息
	if (pDoc->stk1.empty() || pDoc->stk1.size() == 1)
	{
		str.Format(_T("当前不能悔棋！"));
		MessageBox(str);
		return;
	}
	//每次从栈1弹出两个棋子,存到栈2
	for (int i = 0; i < 2; i++)
	{
		tmp_qizi = pDoc->stk1.top();
		pDoc->stk2.push(tmp_qizi);
		pDoc->stk1.pop();
		pDoc->chess[tmp_qizi.point.x][tmp_qizi.point.y] = 0;	//将棋子清除
	}
	//重绘
	Invalidate();
}

//复棋。每次两步
void CMyGobangView::OnEditRedo()
{
	// TODO:  在此添加命令处理程序代码
	//先检查栈2，如果栈是空，表示不能复棋,输出信息
	CString str;
	struct qizi tmp_qizi;  
	if (pDoc->stk2.empty())
	{
		str.Format(_T("当前不能复棋！"));
		MessageBox(str);
		return;
	}
	//每次从栈2弹出两个棋子，存到栈1
	for (int i = 0; i < 2; i++)
	{
		tmp_qizi = pDoc->stk2.top();		
		(*pDoc).stk1.push(tmp_qizi);
		pDoc->stk2.pop();
		pDoc->chess[tmp_qizi.point.x][tmp_qizi.point.y] = tmp_qizi.value;
	}
	//重绘
	Invalidate();
}


void CMyGobangView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	//根据m_bUndo的值设置是否激活菜单项
	pCmdUI->Enable(m_bUndo);
}


void CMyGobangView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	//根据m_bRedo的值设置是否激活菜单项
	pCmdUI->Enable(m_bRedo);
}

void CMyGobangView::OnUpdateNextChess(CCmdUI *pCmdUI) {
	pCmdUI->Enable();
	//状态栏显示下一个棋子颜色
	CString nextchess;
	if (pDoc->heizi) {
		nextchess.Format(_T("NEXT:BLACK"));
	}
	else
	{
		nextchess.Format(_T("NEXT:WHITE"));
	}
	pCmdUI->SetText(nextchess);
}
