
// MyGobangDoc.h : CMyGobangDoc 类的接口
//


#pragma once
#include <stack>
#include <iostream>
using namespace std;


class CMyGobangDoc : public CDocument
{
protected: // 仅从序列化创建
	CMyGobangDoc();
	DECLARE_DYNCREATE(CMyGobangDoc)

// 特性
public:

	bool heizi;		//下黑子或白子的轮流标志
	bool gameover;	//游戏是否结束的标志
	int chess[STRING_NUM][STRING_NUM] ;	//用于存放棋子的数组，0表示没有棋子，1表示黑子，2表示白子

	stack<qizi> stk1;					//用两个栈来实现悔棋复棋.栈1存有效棋

	stack<qizi> stk2;					//栈2存要悔的棋


// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMyGobangDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileNew();
};
