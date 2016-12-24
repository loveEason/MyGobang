
// MyGobangView.cpp : CMyGobangView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMyGobangView ����/����

CMyGobangView::CMyGobangView()
{
	// TODO:  �ڴ˴���ӹ������
}

CMyGobangView::~CMyGobangView()
{
}

BOOL CMyGobangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyGobangView ����

void CMyGobangView::OnDraw(CDC* pDC)
{
	pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	//������������ɫ

	CRect rect;
	GetClientRect(&rect);
	pDC->FillSolidRect(rect, color);

	//������
	CString str;
	CPen pen;

	//��ˮƽ��
	for (int i = 0; i < STRING_NUM; i++) {
		pDC->MoveTo(DISTANCE, DISTANCE + i * DISTANCE);
		pDC->LineTo(STRING_NUM * DISTANCE, DISTANCE + i * DISTANCE);
	}

	//����ֱ��
	for (int i = 0; i < STRING_NUM; i++) {
		pDC->MoveTo(DISTANCE + i * DISTANCE, DISTANCE);
		pDC->LineTo(DISTANCE + i * DISTANCE, STRING_NUM * DISTANCE);
	}

	//���ڷŴ���С����ʱ�����ػ�
	CBrush blackBrush = CBrush(RGB(0, 0, 0));	//��ɫ��ˢ
	CBrush whiteBrush = CBrush(RGB(255, 255, 255));	//��ɫ��ˢ

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


// CMyGobangView ��ӡ


void CMyGobangView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMyGobangView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMyGobangView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMyGobangView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// CMyGobangView ���

#ifdef _DEBUG
void CMyGobangView::AssertValid() const
{
	CView::AssertValid();
}

void CMyGobangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyGobangDoc* CMyGobangView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyGobangDoc)));
	return (CMyGobangDoc*)m_pDocument;
}
#endif //_DEBUG


/*
* �ж���Ӯ
* 0����û����ʤ��
* 1�����ӻ�ʤ
* 2�����ӻ�ʤ
* 3��ƽ��
*/
int CMyGobangView::judge() {
	//�жϺ��ŵ�
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

	//�ж����ŵ�
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

	//�ж���б�ŵ�
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

	//�ж���б�ŵ�
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

	//�������������ϣ���������û�п�λʱ��˵��ƽ��,����˵����û����ʤ��
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

//�ж��Ƿ����ִ��Undo����
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

//�ж��Ƿ����ִ��Redo����
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



// CMyGobangView ��Ϣ�������


void CMyGobangView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CClientDC clentDc(this);

	CBrush blackBrush(RGB(0, 0, 0));	//��ɫ��ˢ
	CBrush whiteBrush(RGB(255, 255, 255));	//��ɫ��ˢ
	struct qizi tmp_qizi;

	if (!pDoc->gameover)
	{
		x_count = 0;
		y_count = 0;
		x_remain = point.x % DISTANCE;
		y_remain = point.y % DISTANCE;
		if (x_remain<5)					//����߽����Ͻ�
			x_count = point.x / DISTANCE;
		else if (x_remain>DISTANCE - 5 && x_remain < DISTANCE)	//���ұ߽����Ͻ�
			x_count = point.x / DISTANCE + 1;

		if (y_remain<5)	//���Ϸ������Ͻ�
			y_count = point.y / DISTANCE;
		else if (y_remain>DISTANCE - 5 && y_remain < DISTANCE) //���·������Ͻ�
			y_count = point.y / DISTANCE + 1;

		if (pDoc->chess[x_count - 1][y_count - 1] == 0 && (x_count != 0 && y_count != 0))
		{
			CRect chess_rect(x_count*DISTANCE - 15, y_count*DISTANCE - 15, x_count*DISTANCE + 15, y_count*DISTANCE + 15);	//һ���������ڵľ���
			if (pDoc->heizi)
			{
				CBrush *pBrush = clentDc.SelectObject(&blackBrush);
				clentDc.Ellipse(chess_rect);
				pDoc->chess[x_count - 1][y_count - 1] = 1;
				CPoint tmp_point(x_count - 1, y_count - 1);
				tmp_qizi.point = tmp_point;
				tmp_qizi.value = 1;
				(pDoc->stk1).push(tmp_qizi);	//����������Ϣ��ջ1
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
				pDoc->stk1.push(tmp_qizi);	//����������Ϣ��ջ1
				pDoc->heizi = true;
			}
			//����һ��֮���ж��Ƿ��ִ��Undo��Redo����
			canUndo();
			canRedo();
			//����һ��֮���ж��Ƿ��ܾ���ʤ��
			CString str;
			int judgement = judge();
			if (judgement == 1)
			{
				str.Format(_T("���ӻ�ʤ��"));
				MessageBox(str);
			}
			else if (judgement == 2)
			{
				str.Format(_T("���ӻ�ʤ��"));
				MessageBox(str);
			}
			else if (judgement == 3)
			{
				str.Format(_T("ƽ�֣�"));
				MessageBox(str);
			}
		}
	}
	CView::OnLButtonDown(nFlags, point);
}




//�޸�������ɫ
void CMyGobangView::OnColor()
{
	// TODO:  �ڴ���������������
	CColorDialog colorDlg(color);	//������ɫ�Ի��򣬴����ʼ��ɫֵ
	if (colorDlg.DoModal() == IDOK)	//��ʾ��ɫ�Ի��򣬲��ж��Ƿ����ˡ�ȷ����
	{
		color = colorDlg.GetColor();	//��ȡ��ѡ����ɫ
	}
	Invalidate();	//�ػ�
}

//���塣ÿ������
void CMyGobangView::OnEditUndo()
{
	// TODO:  �ڴ���������������
	//�ȼ��ջ2�����ջ�ǿգ���ʾ���ܸ���,�����Ϣ
	CString str;
	struct qizi tmp_qizi;
	//�ȼ��ջ1�����ջ�ǿջ���Ϊ1����ʾ���ܻ���,�����Ϣ
	if (pDoc->stk1.empty() || pDoc->stk1.size() == 1)
	{
		str.Format(_T("��ǰ���ܻ��壡"));
		MessageBox(str);
		return;
	}
	//ÿ�δ�ջ1������������,�浽ջ2
	for (int i = 0; i < 2; i++)
	{
		tmp_qizi = pDoc->stk1.top();
		pDoc->stk2.push(tmp_qizi);
		pDoc->stk1.pop();
		pDoc->chess[tmp_qizi.point.x][tmp_qizi.point.y] = 0;	//���������
	}
	//�ػ�
	Invalidate();
}

//���塣ÿ������
void CMyGobangView::OnEditRedo()
{
	// TODO:  �ڴ���������������
	//�ȼ��ջ2�����ջ�ǿգ���ʾ���ܸ���,�����Ϣ
	CString str;
	struct qizi tmp_qizi;  
	if (pDoc->stk2.empty())
	{
		str.Format(_T("��ǰ���ܸ��壡"));
		MessageBox(str);
		return;
	}
	//ÿ�δ�ջ2�����������ӣ��浽ջ1
	for (int i = 0; i < 2; i++)
	{
		tmp_qizi = pDoc->stk2.top();		
		(*pDoc).stk1.push(tmp_qizi);
		pDoc->stk2.pop();
		pDoc->chess[tmp_qizi.point.x][tmp_qizi.point.y] = tmp_qizi.value;
	}
	//�ػ�
	Invalidate();
}


void CMyGobangView::OnUpdateEditUndo(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	//����m_bUndo��ֵ�����Ƿ񼤻�˵���
	pCmdUI->Enable(m_bUndo);
}


void CMyGobangView::OnUpdateEditRedo(CCmdUI *pCmdUI)
{
	// TODO:  �ڴ������������û����洦��������
	//����m_bRedo��ֵ�����Ƿ񼤻�˵���
	pCmdUI->Enable(m_bRedo);
}

void CMyGobangView::OnUpdateNextChess(CCmdUI *pCmdUI) {
	pCmdUI->Enable();
	//״̬����ʾ��һ��������ɫ
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
