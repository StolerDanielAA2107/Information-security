﻿
// LR2StolerDlg.h: файл заголовка
//

#pragma once

// Диалоговое окно CLR2StolerDlg
class CLR2StolerDlg : public CDialogEx
{
// Создание
public:
	CLR2StolerDlg(CWnd* pParent = nullptr);	// стандартный конструктор
// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LR2STOLER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};