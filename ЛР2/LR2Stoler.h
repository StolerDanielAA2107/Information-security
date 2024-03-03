
// LR2Stoler.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы

// CLR2StolerApp:
// Сведения о реализации этого класса: LR2Stoler.cpp
//

class CLR2StolerApp : public CWinApp
{
public:
	CLR2StolerApp();

// Переопределение
public:
	virtual BOOL InitInstance();

	afx_msg void OnBnClickedButtonOpen() {};

	DECLARE_MESSAGE_MAP()
};

extern CLR2StolerApp theApp;
