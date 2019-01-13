
// Library_ExecutionDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Dynamic_Extended_Library_Execution_Dialog.h"
#include "Dynamic_Extended_Library_Applications.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CLibraryExecutionDialog dialog



CLibraryExecutionDialog::CLibraryExecutionDialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_LIBRARY_EXECUTION_DIALOG, pParent)
	, LibraryFileValue(_T(""))
	, FunctionNameValue(_T(""))
	, FunctionParameterValue(_T(""))
	, FunctionResultValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLibraryExecutionDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LIBRARY_FILE, LibraryFileValue);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_NAME, FunctionNameValue);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_PARAMETER, FunctionParameterValue);
	DDX_Text(pDX, IDC_EDIT_FUNCTION_RESULT, FunctionResultValue);
	DDX_Control(pDX, IDC_LIST_FUNCTION_NAME, ListFunctionNameControl);
}

BEGIN_MESSAGE_MAP(CLibraryExecutionDialog, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_SELECT_FILE, &CLibraryExecutionDialog::OnBnClickedButtonSelectFile)
	ON_BN_CLICKED(IDC_BUTTON_EXECUTE_FUNCTION, &CLibraryExecutionDialog::OnBnClickedButtonExecuteFunction)
	ON_BN_CLICKED(IDC_BUTTON_LOAD_FUNCTIONS, &CLibraryExecutionDialog::OnBnClickedButtonLoadFunctions)
	ON_LBN_SELCHANGE(IDC_LIST_FUNCTION_NAME, &CLibraryExecutionDialog::OnLbnSelchangeListFunctionName)
END_MESSAGE_MAP()


// CLibraryExecutionDialog message handlers

BOOL CLibraryExecutionDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CLibraryExecutionDialog::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CLibraryExecutionDialog::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CLibraryExecutionDialog::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLibraryExecutionDialog::OnBnClickedButtonSelectFile()
{
	CFileDialog OpenDialog(TRUE);

	CString FunctionResult;

	if (OpenDialog.DoModal() == IDOK)
	{
		CString LibraryPath = OpenDialog.GetPathName();

		LibraryFileValue = LibraryPath;

		FunctionResult = CString("File was selected.");
	}
	else
	{
		FunctionResult = CString("File selection was canceled.");
	}

	FunctionResultValue = FunctionResult;

	UpdateData(FALSE);
}


void CLibraryExecutionDialog::OnBnClickedButtonExecuteFunction()
{
	UpdateData(TRUE);

	CString LibraryPath = LibraryFileValue;
	CString FunctionName = FunctionNameValue;
	CString FunctionParameter = FunctionParameterValue;

	CString FunctionResult;

	char FunctionNameCString[10000];

	memset(FunctionNameCString, 0, 10000 * sizeof(char));
	
	int FunctionNameGetLength = FunctionName.GetLength();

	for (int i = 0; i < FunctionNameGetLength && i < 10000; i++)
	{
		FunctionNameCString[i] = char(FunctionName.GetAt(i));
	}

	PWCHAR FunctionParameterCString = new WCHAR[10000];

	if (FunctionParameterCString != nullptr)
	{
		memset(FunctionParameterCString, 0, 10000 * sizeof(WCHAR));

		int FunctionParameterGetLength = FunctionParameter.GetLength();

		for (int i = 0; i < FunctionParameterGetLength && i < 10000; i++)
		{
			FunctionParameterCString[i] = FunctionParameter.GetAt(i);
		}

		HMODULE ModuleHandle = LoadLibrary(LibraryPath);

		if (ModuleHandle != nullptr)
		{
			typedef WCHAR * PWCHAR;

			typedef PWCHAR(FAR WINAPI *FAR_FUNCTION_RESULT_POINTER)(PWCHAR);

			FAR_FUNCTION_RESULT_POINTER RemoteFunctionPointer = (FAR_FUNCTION_RESULT_POINTER)GetProcAddress(ModuleHandle, FunctionNameCString);

			if (RemoteFunctionPointer != nullptr)
			{
				Sleep(100);
				PWCHAR FunctionResultPointer = RemoteFunctionPointer(FunctionParameterCString);

				if (FunctionResultPointer != nullptr)
				{
					if (FunctionResultPointer != nullptr)
					{
						FunctionResult = CString(FunctionResultPointer);

						delete[]FunctionResultPointer;
					}
					else
					{
						FunctionResult = CString("Function returnet zero pointer.");
					}
				}
				else
				{
					FunctionResult = CString("Function was not loaded.");
				}
			}
			else
			{
				FunctionResult = CString("Function was not found.");
			}
		}
		else
		{
			FunctionResult = CString("Module was not loaded.");
		}

		delete[]FunctionParameterCString;
	}
	else
	{
		FunctionResult = CString("Not enouph memoty.");
	}

	FunctionResultValue = FunctionResult;

	UpdateData(FALSE);
}


void CLibraryExecutionDialog::OnBnClickedButtonLoadFunctions()
{
	HMODULE CurrentModule = AfxGetApp()->m_hInstance;

	const DWORD FileNameSize = 10000;

	WCHAR FileName[FileNameSize];

	memset(FileName, 0, FileNameSize * sizeof(WCHAR));

	GetModuleFileNameW(CurrentModule, FileName, FileNameSize);

	LibraryFileValue = CString(FileName);

	ListFunctionNameControl.AddString(L"GetChessFigures");

	UpdateData(FALSE);
}


void CLibraryExecutionDialog::OnLbnSelchangeListFunctionName()
{
	int CurrentlySelected = ListFunctionNameControl.GetCurSel();

	if (CurrentlySelected >= 0)
	{
		ListFunctionNameControl.GetText(CurrentlySelected, FunctionNameValue);
	}

	UpdateData(FALSE);
}
