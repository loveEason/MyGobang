
// MyGobangDoc.h : CMyGobangDoc ��Ľӿ�
//


#pragma once
#include <stack>
#include <iostream>
using namespace std;


class CMyGobangDoc : public CDocument
{
protected: // �������л�����
	CMyGobangDoc();
	DECLARE_DYNCREATE(CMyGobangDoc)

// ����
public:

	bool heizi;		//�º��ӻ���ӵ�������־
	bool gameover;	//��Ϸ�Ƿ�����ı�־
	int chess[STRING_NUM][STRING_NUM] ;	//���ڴ�����ӵ����飬0��ʾû�����ӣ�1��ʾ���ӣ�2��ʾ����

	stack<qizi> stk1;					//������ջ��ʵ�ֻ��帴��.ջ1����Ч��

	stack<qizi> stk2;					//ջ2��Ҫ�ڵ���


// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CMyGobangDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnFileNew();
};
