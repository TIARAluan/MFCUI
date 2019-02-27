
// MFCUIDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"



// CMFCUIDlg �Ի���
class CMFCUIDlg : public CDialogEx
{
// ����
public:
	CMFCUIDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CStatusBar m_bar;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCUI_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


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
//����һ��״̬���ṹ��
static UINT BASED_CODE indicators[] =
{
	ID_INDICATOR_COUNT,
	//ID_INDICATOR_TIME,
};
