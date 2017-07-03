
// 模拟键盘输入和鼠标输入Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "模拟键盘输入和鼠标输入.h"
#include "模拟键盘输入和鼠标输入Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// C模拟键盘输入和鼠标输入Dlg 对话框



C模拟键盘输入和鼠标输入Dlg::C模拟键盘输入和鼠标输入Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, Title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C模拟键盘输入和鼠标输入Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Title);
}

BEGIN_MESSAGE_MAP(C模拟键盘输入和鼠标输入Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C模拟键盘输入和鼠标输入Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C模拟键盘输入和鼠标输入Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &C模拟键盘输入和鼠标输入Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// C模拟键盘输入和鼠标输入Dlg 消息处理程序

BOOL C模拟键盘输入和鼠标输入Dlg::OnInitDialog()
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

void C模拟键盘输入和鼠标输入Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C模拟键盘输入和鼠标输入Dlg::OnPaint()
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
HCURSOR C模拟键盘输入和鼠标输入Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void C模拟键盘输入和鼠标输入Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, Title);//输入已运行的应用程序名称，例“notepad”
	CWnd *pWnd = FindWindow(Title, NULL);//获取应用程序的窗口句柄,Title为类名
	//CWnd *pWnd = FindWindow(NULL, Title);//Title为标题名，例“计算器”
	char *cTitle = new char[30];
	int charcount;
	charcount = WideCharToMultiByte(CP_ACP, 0, Title, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Title, -1, cTitle, charcount, NULL, NULL);
	WinExec(cTitle, SW_SHOW);//打开应用程序
	if (pWnd->GetSafeHwnd())
	{
		pWnd->ShowWindow(SW_NORMAL);//设置窗口为正常大小
		pWnd->SetForegroundWindow();//将窗口置于前台并激活窗口		
	}
	delete[] cTitle;
}


void C模拟键盘输入和鼠标输入Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, Title);
	CWnd *pWnd = FindWindow(Title, NULL);
	if (pWnd->GetSafeHwnd())
	{
		//pWnd->ShowWindow(SW_MINIMIZE);//设置窗口最小化
		pWnd->SetForegroundWindow();
		keybd_event(VK_MENU, 0, 0, 0);//按下Alt键
		keybd_event(69, 0, 0, 0);//按下‘E’键，E键的键码为69
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0);//松开E键
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
		//按下Prscrn 截屏键
		keybd_event(44, 0, 0, 0);
		keybd_event(44, 0, KEYEVENTF_KEYUP, 0);
	}
}


void C模拟键盘输入和鼠标输入Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	GetDlgItemText(IDC_EDIT1, Title);
	CWnd *pWnd = FindWindow(Title, NULL);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->SetForegroundWindow();
		keybd_event(VK_MENU, 0, 0, 0);
		keybd_event(VK_F4, 0, 0, 0);//按下F4键
		keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}
}
