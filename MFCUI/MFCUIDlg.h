
// MFCUIDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"



// CMFCUIDlg 对话框
class CMFCUIDlg : public CDialogEx
{
// 构造
public:
	CMFCUIDlg(CWnd* pParent = NULL);	// 标准构造函数
	CStatusBar m_bar;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


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
	CString Row;
	CString Column;
	CString BoxNumber;
	CString SampleType;
	CString BoxDescription;
	CString BoxLocation;
	CListCtrl m_ListCtrl;
	afx_msg void init_list_control();
	afx_msg void init_StatusBarr();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton5Txt();
	afx_msg void OnBnClickedButton3Image();
	afx_msg void OnBnClickedButton4Sql();
	BOOL PreTranslateMessage(MSG * pMsg);
	afx_msg void OnBnClickedButtonChangecontext();
	afx_msg void OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_ChangeContext;
	
	afx_msg void OnBnClickedButton2Start2();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnBnClickedButton1Fresh();
	afx_msg void OnBnClickedButton2Deal();
	int Bar_Total;
	int Bar_Dealed;
};
//定义一个状态栏结构体
static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_COUNT,
	//ID_INDICATOR_TIME,
};
