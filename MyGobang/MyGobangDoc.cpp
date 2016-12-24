
// MyGobangDoc.cpp : CMyGobangDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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


// CMyGobangDoc 构造/析构

CMyGobangDoc::CMyGobangDoc()
{
	// TODO:  在此添加一次性构造代码
				
}

CMyGobangDoc::~CMyGobangDoc()
{
}

BOOL CMyGobangDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	heizi = true;
	gameover = false;
	for (int i = 0; i < STRING_NUM; i++) {
		for (int j = 0; j < STRING_NUM; j++) {
			chess[i][j] = { 0 };
		}
	}
	//将两个栈清空
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




// CMyGobangDoc 序列化

void CMyGobangDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
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
		// TODO:  在此添加加载代码	
		OnNewDocument();	//先新建一个，然后载入之前保存的数据
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

// 缩略图的支持
void CMyGobangDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
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

// 搜索处理程序的支持
void CMyGobangDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
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

// CMyGobangDoc 诊断

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


// CMyGobangDoc 命令



//重新开始游戏
void CMyGobangDoc::OnFileNew()
{
	// TODO:  在此添加命令处理程序代码
	OnNewDocument();
	UpdateAllViews(NULL);
}
