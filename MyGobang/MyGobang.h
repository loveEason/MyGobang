
// MyGobang.h : MyGobang Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������

#define DISTANCE 40		//������֮��ľ���
#define STRING_NUM 15	//�ߵ�����

struct qizi{			//�����ӵ������ֵ��1��ʾ���ӣ�2��ʾ����

	CPoint point;

	int value;

} ;


// CMyGobangApp:
// �йش����ʵ�֣������ MyGobang.cpp
//

class CMyGobangApp : public CWinAppEx
{
public:
	CMyGobangApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGobangApp theApp;
