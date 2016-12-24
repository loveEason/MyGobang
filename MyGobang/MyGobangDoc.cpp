
// MyGobangDoc.cpp : CMyGobangDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyGobang.h"
#endif

#include "MyGobangDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMyGobangDoc

IMPLEMENT_DYNCREATE(CMyGobangDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyGobangDoc, CDocument)
	ON_COMMAND(ID_FILE_NEW, &CMyGobangDoc::OnFileNew)
END_MESSAGE_MAP()


// CMyGobangDoc ����/����

CMyGobangDoc::CMyGobangDoc()
{
	// TODO:  �ڴ����һ���Թ������
				
}

CMyGobangDoc::~CMyGobangDoc()
{
}

BOOL CMyGobangDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO:  �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	heizi = true;
	gameover = false;
	for (int i = 0; i < STRING_NUM; i++) {
		for (int j = 0; j < STRING_NUM; j++) {
			chess[i][j] = { 0 };
		}
	}
	//������ջ���
	while (!stk1.empty())
	{
		stk1.pop();
	}
	while (!stk2.empty())
	{
		stk2.pop();
	}
	return TRUE;
}




// CMyGobangDoc ���л�

void CMyGobangDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  �ڴ���Ӵ洢����
		ar << heizi;
		ar << gameover;
		for (int i = 0; i < STRING_NUM; i++) {
			for (int j = 0; j < STRING_NUM; j++) {
				ar << chess[i][j];
			}
		}
	}
	else
	{
		// TODO:  �ڴ���Ӽ��ش���	
		OnNewDocument();	//���½�һ����Ȼ������֮ǰ���������
		ar >> heizi;
		ar >> gameover;
		for (int i = 0; i < STRING_NUM; i++) {
			for (int j = 0; j < STRING_NUM; j++) {
				ar >> chess[i][j];
			}
		}

		UpdateAllViews(NULL);
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMyGobangDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMyGobangDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMyGobangDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMyGobangDoc ���

#ifdef _DEBUG
void CMyGobangDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyGobangDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyGobangDoc ����



//���¿�ʼ��Ϸ
void CMyGobangDoc::OnFileNew()
{
	// TODO:  �ڴ���������������
	OnNewDocument();
	UpdateAllViews(NULL);
}
