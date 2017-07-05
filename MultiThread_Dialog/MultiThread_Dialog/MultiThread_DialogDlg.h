
// MultiThread_DialogDlg.h : 头文件
//

#pragma once


// CMultiThread_DialogDlg 对话框
class CMultiThread_DialogDlg : public CDialogEx
{
// 构造
public:
	CMultiThread_DialogDlg(CWnd* pParent = NULL);	// 标准构造函数
	
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MULTITHREAD_DIALOG_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	HANDLE hThread;
	DWORD ThreadID;
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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