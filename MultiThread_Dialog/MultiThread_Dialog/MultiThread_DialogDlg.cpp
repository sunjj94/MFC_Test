
// MultiThread_DialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MultiThread_Dialog.h"
#include "MultiThread_DialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CM_UPDATE (WM_USER + 100)//自定义消息

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMultiThread_DialogDlg 对话框



CMultiThread_DialogDlg::CMultiThread_DialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MULTITHREAD_DIALOG_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMultiThread_DialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMultiThread_DialogDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMultiThread_DialogDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_STOP, &CMultiThread_DialogDlg::OnBnClickedStop)
	ON_MESSAGE(CM_UPDATE, &CMultiThread_DialogDlg::UpdateUI)//添加消息队列
END_MESSAGE_MAP()


// CMultiThread_DialogDlg 消息处理程序

BOOL CMultiThread_DialogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMultiThread_DialogDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMultiThread_DialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMultiThread_DialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//全局变量
volatile BOOL m_bRun;//标识线程是否运行条件

//DWORD WINAPI ThreadProc(LPVOID lpParameter)
void ThreadProc(LPVOID lpParameter)
{
	ThreadData *pThreadData = (ThreadData *)lpParameter;
		
	m_bRun = TRUE;
	while (m_bRun)
	{			
		::PostMessage(pThreadData->hWnd, CM_UPDATE, NULL, NULL);
		Sleep(1000);
	}
	//return 0;
}

ThreadData ThreadParm;//不能是局部变量
void CMultiThread_DialogDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码	
	ThreadParm.hWnd = AfxGetMainWnd()->m_hWnd;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, &ThreadParm, 0, &ThreadID);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
}


void CMultiThread_DialogDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bRun = FALSE;
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	CloseHandle(hThread);
}


LRESULT CMultiThread_DialogDlg::UpdateUI(WPARAM wParam, LPARAM lParam)//添加消息响应函数
{
	CTime time;
	CString strTime;
	time = CTime::GetCurrentTime();
	strTime = time.Format("%H:%M:%S");
	SetDlgItemText(IDC_TIME, strTime);
	//UpdateData(FALSE);
	return 0;
}
