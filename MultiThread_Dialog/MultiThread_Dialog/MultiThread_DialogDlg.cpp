
// MultiThread_DialogDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MultiThread_Dialog.h"
#include "MultiThread_DialogDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CM_UPDATE (WM_USER + 100)//�Զ�����Ϣ

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


// CMultiThread_DialogDlg �Ի���



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
	ON_MESSAGE(CM_UPDATE, &CMultiThread_DialogDlg::UpdateUI)//�����Ϣ����
END_MESSAGE_MAP()


// CMultiThread_DialogDlg ��Ϣ�������

BOOL CMultiThread_DialogDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMultiThread_DialogDlg::OnPaint()
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
HCURSOR CMultiThread_DialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//ȫ�ֱ���
volatile BOOL m_bRun;//��ʶ�߳��Ƿ���������

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

ThreadData ThreadParm;//�����Ǿֲ�����
void CMultiThread_DialogDlg::OnBnClickedStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	ThreadParm.hWnd = AfxGetMainWnd()->m_hWnd;
	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadProc, &ThreadParm, 0, &ThreadID);
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_STOP)->EnableWindow(TRUE);
}


void CMultiThread_DialogDlg::OnBnClickedStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bRun = FALSE;
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE);
	CloseHandle(hThread);
}


LRESULT CMultiThread_DialogDlg::UpdateUI(WPARAM wParam, LPARAM lParam)//�����Ϣ��Ӧ����
{
	CTime time;
	CString strTime;
	time = CTime::GetCurrentTime();
	strTime = time.Format("%H:%M:%S");
	SetDlgItemText(IDC_TIME, strTime);
	//UpdateData(FALSE);
	return 0;
}
