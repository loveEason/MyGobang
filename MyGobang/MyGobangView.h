
// MyGobangView.h : CMyGobangView ��Ľӿ�
//

#pragma once
#include <stack>

#include <iostream>

using namespace std;


class CMyGobangView : public CView
{
protected: // �������л�����
	CMyGobangView();
	DECLARE_DYNCREATE(CMyGobangView)

// ����
public:
	CMyGobangDoc* GetDocument() const;

	CMyGobangDoc* pDoc;
	int x_remain;				//�������������Ľ����ĺ������
	int x_count;				//��������Ĵ������佻����ˮƽ���
	int y_remain;				//�������������Ľ������������
	int y_count;				//��������Ĵ������佻���Ĵ�ֱ���
	COLORREF color = RGB(0, 255, 0);	//������ɫ��Ĭ��Ϊ��ɫ
	bool m_bUndo = FALSE;						//��ǰ�Ƿ���Ե��Undo�˵���
	bool m_bRedo = FALSE;						//��ǰ�Ƿ���Ե��Redo�˵���
// ����
public:
	int judge();				//�ж���Ӯ
	void canUndo();				//�ж��Ƿ����ִ��Undo����
	void canRedo();				//�ж��Ƿ����ִ��Redo����

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMyGobangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MyGobangView.cpp �еĵ��԰汾
inline CMyGobangDoc* CMyGobangView::GetDocument() const
   { return reinterpret_cast<CMyGobangDoc*>(m_pDocument); }
#endif

