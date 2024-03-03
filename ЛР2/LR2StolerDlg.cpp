#include <atlconv.h>


// LR2StolerDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "LR2Stoler.h"
#include "LR2StolerDlg.h"
#include "afxdialogex.h"
#include "format"
#include "afx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <afxwin.h>


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CLR2StolerDlg

CLR2StolerDlg::CLR2StolerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LR2STOLER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CLR2StolerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLR2StolerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLR2StolerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLR2StolerDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLR2StolerDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// Обработчики сообщений CLR2StolerDlg

BOOL CLR2StolerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	SetWindowText(_T("Лабораторная работа #2"));
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	CFont font;
	font.CreatePointFont(120, _T("Times New Roman"));
	GetDlgItem(IDC_RICHEDIT21)->SetFont(&font);
	
	// TODO: добавьте дополнительную инициализацию
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CLR2StolerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CLR2StolerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CLR2StolerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLR2StolerDlg::OnBnClickedButton1()
{
	CFileDialog fileDlg(TRUE); // TRUE - для открытия файла, FALSE - для сохранения
	fileDlg.m_ofn.lpstrTitle = "Выберите файл"; // Заголовок диалогового окна
	fileDlg.m_ofn.Flags |= OFN_FILEMUSTEXIST;

	if (fileDlg.DoModal() == IDOK) {
		CString selectedFile = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT1, selectedFile);
	}
	else {}
}


void CLR2StolerDlg::OnBnClickedButton2()
{
	CFileDialog fileDlg(TRUE); // TRUE - для открытия файла, FALSE - для сохранения
	fileDlg.m_ofn.lpstrTitle = "Выберите файл"; // Заголовок диалогового окна
	fileDlg.m_ofn.Flags |= OFN_FILEMUSTEXIST;
	if (fileDlg.DoModal() == IDOK) {
		CString selectedFile = fileDlg.GetPathName();
		SetDlgItemText(IDC_EDIT2, selectedFile);
	}
	else {}

}

void frequencyAnalysis(std::vector<unsigned char>& vect, int* freqModelText) {
	for (int i = 0; i < 256; i++)
		freqModelText[i] = 0;
	for (auto symbol : vect)
		freqModelText[symbol] += 1;
}

char decode(unsigned char CStandartOrCKey, unsigned char code) //decoding
{
	return code - CStandartOrCKey;
}

char getMostPopularSymbol(int* freqModelText)
{
	char popularSymbol;
	int max = -1;
	for (int i = 0; i < 256; i++)
		if (freqModelText[i] > max)
		{
			popularSymbol = i;
			max = freqModelText[i];
		}
	return popularSymbol;
}

void CLR2StolerDlg::OnBnClickedButton3()
{
	UpdateData(1);
	CString modelFileName, encodedFileName, keylength, decoded_name, minkeylength, maxkeylength;
	GetDlgItemText(IDC_EDIT4, keylength);
	int keylengthint = atoi(keylength.GetString());
	GetDlgItemText(IDC_EDIT1, encodedFileName);
	GetDlgItemText(IDC_EDIT2, modelFileName);
	GetDlgItemText(IDC_EDIT6, decoded_name);
	std::ifstream fen(encodedFileName, std::ifstream::binary);
	std::ifstream fst(modelFileName, std::ifstream::binary);
	std::vector<unsigned char> encodedText((std::istreambuf_iterator<char>(fen)), std::istreambuf_iterator<char>());
	std::vector<unsigned char> modelText((std::istreambuf_iterator<char>(fst)), std::istreambuf_iterator<char>());
	int freqModelText[256];
	frequencyAnalysis(modelText, freqModelText);

	char modelTextPopularSymbol = getMostPopularSymbol(freqModelText);

	std::vector<std::vector<unsigned char>> sequence(keylengthint);
	std::vector<unsigned char>::iterator it = encodedText.begin();
	while (it != encodedText.end())
	{
		for (auto& symbolPart : sequence)
			if (it != encodedText.end())
			{
				symbolPart.push_back(*it);
				it++;
			}
	}

	CString decodeKey;
	for (auto symbolPart : sequence)
	{
		int freqEncodeText[256];
		frequencyAnalysis(symbolPart, freqEncodeText);
		char encodedTextPopularSymbol = getMostPopularSymbol(freqEncodeText);
		char keySymbol = decode(modelTextPopularSymbol, encodedTextPopularSymbol);
		decodeKey += keySymbol;
	}

	int pos = 0;
	CString result;
	std::string res;
	for (auto code : encodedText)
	{
		char text;
		text = decode(decodeKey[pos], code);
		res.push_back(text);
		pos++;
		if (pos == keylengthint)
			pos = 0;
	}

	result.Format("%s", res.c_str());

	SetDlgItemText(IDC_STATIC, decodeKey);
	GetDlgItem(IDC_RICHEDIT21)->SetWindowText(result);

	CFile myFile;
	if (myFile.Open(decoded_name, CFile::modeCreate | CFile::modeReadWrite))
	{
		myFile.Write(result.GetBuffer(), encodedText.size());
		myFile.Flush();
	}
	myFile.Close();

	CString strMessage;
	strMessage.Format(_T("Выполнено!"));
	AfxMessageBox(strMessage);
}