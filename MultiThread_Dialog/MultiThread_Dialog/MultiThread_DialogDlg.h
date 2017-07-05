
// MultiThread_DialogDlg.h : ͷ�ļ�
//

#pragma once


// CMultiThread_DialogDlg �Ի���
class CMultiThread_DialogDlg : public CDialogEx
{
// ����
public:
	CMultiThread_DialogDlg(CWnd* pParent = NULL);	// ��׼���캯��
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTITHREAD_DIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	HANDLE hThread;
	DWORD ThreadID;
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();	
	afx_msg void OnBnClickedStop();
	afx_msg LRESULT UpdateUI(WPARAM wParam, LPARAM lParam);
};

//DWORD WINAPI ThreadProc(LPVOID lpParameter);
void ThreadProc(LPVOID lpParameter);
typedef struct __ThreadData
{
	HWND hWnd;

	__ThreadData()
	{
		hWnd = NULL;
	}
}ThreadData;