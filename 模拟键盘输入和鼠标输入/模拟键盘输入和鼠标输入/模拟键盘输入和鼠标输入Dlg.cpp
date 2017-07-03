
// ģ�����������������Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ģ�����������������.h"
#include "ģ�����������������Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// Cģ�����������������Dlg �Ի���



Cģ�����������������Dlg::Cģ�����������������Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, Title(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cģ�����������������Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Title);
}

BEGIN_MESSAGE_MAP(Cģ�����������������Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cģ�����������������Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Cģ�����������������Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Cģ�����������������Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Cģ�����������������Dlg ��Ϣ�������

BOOL Cģ�����������������Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void Cģ�����������������Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cģ�����������������Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cģ�����������������Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cģ�����������������Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT1, Title);//���������е�Ӧ�ó������ƣ�����notepad��
	CWnd *pWnd = FindWindow(Title, NULL);//��ȡӦ�ó���Ĵ��ھ��,TitleΪ����
	//CWnd *pWnd = FindWindow(NULL, Title);//TitleΪ��������������������
	char *cTitle = new char[30];
	int charcount;
	charcount = WideCharToMultiByte(CP_ACP, 0, Title, -1, NULL, 0, NULL, NULL);
	WideCharToMultiByte(CP_ACP, 0, Title, -1, cTitle, charcount, NULL, NULL);
	WinExec(cTitle, SW_SHOW);//��Ӧ�ó���
	if (pWnd->GetSafeHwnd())
	{
		pWnd->ShowWindow(SW_NORMAL);//���ô���Ϊ������С
		pWnd->SetForegroundWindow();//����������ǰ̨�������		
	}
	delete[] cTitle;
}


void Cģ�����������������Dlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItemText(IDC_EDIT1, Title);
	CWnd *pWnd = FindWindow(Title, NULL);
	if (pWnd->GetSafeHwnd())
	{
		//pWnd->ShowWindow(SW_MINIMIZE);//���ô�����С��
		pWnd->SetForegroundWindow();
		keybd_event(VK_MENU, 0, 0, 0);//����Alt��
		keybd_event(69, 0, 0, 0);//���¡�E������E���ļ���Ϊ69
		keybd_event('E', 0, KEYEVENTF_KEYUP, 0);//�ɿ�E��
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
		//����Prscrn ������
		keybd_event(44, 0, 0, 0);
		keybd_event(44, 0, KEYEVENTF_KEYUP, 0);
	}
}


void Cģ�����������������Dlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
	GetDlgItemText(IDC_EDIT1, Title);
	CWnd *pWnd = FindWindow(Title, NULL);
	if (pWnd->GetSafeHwnd())
	{
		pWnd->SetForegroundWindow();
		keybd_event(VK_MENU, 0, 0, 0);
		keybd_event(VK_F4, 0, 0, 0);//����F4��
		keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
		keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
	}
}
