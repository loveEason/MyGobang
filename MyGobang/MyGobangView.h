
// MyGobangView.h : CMyGobangView 类的接口
//

#pragma once
#include <stack>

#include <iostream>

using namespace std;


class CMyGobangView : public CView
{
protected: // 仅从序列化创建
	CMyGobangView();
	DECLARE_DYNCREATE(CMyGobangView)

// 特性
public:
	CMyGobangDoc* GetDocument() const;

	CMyGobangDoc* pDoc;
	int x_remain;				//鼠标点击处离最近的交叉点的横向距离
	int x_count;				//鼠标点击处的大致所落交叉点的水平序号
	int y_remain;				//鼠标点击处离最近的交叉点的纵向距离
	int y_count;				//鼠标点击处的大致所落交叉点的垂直序号
	COLORREF color = RGB(0, 255, 0);	//棋盘颜色，默认为绿色
	bool m_bUndo = FALSE;						//当前是否可以点击Undo菜单项
	bool m_bRedo = FALSE;						//当前是否可以点击Redo菜单项
// 操作
public:
	int judge();				//判断输赢
	void canUndo();				//判断是否可以执行Undo操作
	void canRedo();				//判断是否可以执行Redo操作

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMyGobangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnColor();
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateNextChess(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // MyGobangView.cpp 中的调试版本
inline CMyGobangDoc* CMyGobangView::GetDocument() const
   { return reinterpret_cast<CMyGobangDoc*>(m_pDocument); }
#endif

