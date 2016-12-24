
// MyGobang.h : MyGobang 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号

#define DISTANCE 40		//线与线之间的距离
#define STRING_NUM 15	//线的数量

struct qizi{			//存棋子的坐标和值，1表示黑子，2表示白子

	CPoint point;

	int value;

} ;


// CMyGobangApp:
// 有关此类的实现，请参阅 MyGobang.cpp
//

class CMyGobangApp : public CWinAppEx
{
public:
	CMyGobangApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyGobangApp theApp;
