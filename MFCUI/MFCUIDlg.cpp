
// MFCUIDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCUI.h"
#include "MFCUIDlg.h"
#include "Mysql.h"
#include "HalconCpp.h"
#include "afxdialogex.h"
#include <iostream>
using namespace std;
using namespace HalconCpp;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//ȫ�ֱ���
int MoRow;
int MoCol;
HObject  ho_Image;
CRect rtWindow;
HTuple m_htWindow,hv_Length;
HTuple DirectShow, hv_AcqHandle;
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
public:
//	virtual BOOL PreTranslateMessage(MSG* pMsg);
	HACCEL hAccel;
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


// CMFCUIDlg �Ի���



CMFCUIDlg::CMFCUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCUI_DIALOG, pParent)
	, Row(_T(""))
	, Column(_T(""))
	, BoxNumber(_T(""))
	, SampleType(_T(""))
	, BoxDescription(_T(""))
	, BoxLocation(_T(""))
	, m_ChangeContext(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON3);
}

void CMFCUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1_Row, Row);
	DDX_Text(pDX, IDC_EDIT2_Column, Column);
	DDX_Text(pDX, IDC_EDIT3_BoxNumber, BoxNumber);
	DDX_Text(pDX, IDC_EDIT4_SampleType, SampleType);
	DDX_Text(pDX, IDC_EDIT5_BoxDescription, BoxDescription);
	DDX_Text(pDX, IDC_EDIT6_BoxLocation, BoxLocation);
	DDX_Control(pDX, IDC_LIST, m_ListCtrl);
	DDX_Text(pDX, IDC_EDIT_ChangeContext, m_ChangeContext);
	DDX_Text(pDX, IDC_EDIT1_Total, Bar_Total);
	DDX_Text(pDX, IDC_EDIT1_Dealed, Bar_Dealed);
}

BEGIN_MESSAGE_MAP(CMFCUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON5_Txt, &CMFCUIDlg::OnBnClickedButton5Txt)
	//ON_BN_CLICKED(IDC_BUTTON2_Start, &CMFCUIDlg::OnBnClickedButton2Start)
	ON_BN_CLICKED(IDC_BUTTON3_Image, &CMFCUIDlg::OnBnClickedButton3Image)
	ON_BN_CLICKED(IDC_BUTTON4_Sql, &CMFCUIDlg::OnBnClickedButton4Sql)
	ON_BN_CLICKED(IDC_BUTTON_ChangeContext, &CMFCUIDlg::OnBnClickedButtonChangecontext)
	ON_NOTIFY(NM_CLICK, IDC_LIST, &CMFCUIDlg::OnNMClickList)
	ON_BN_CLICKED(IDC_BUTTON2_Start2, &CMFCUIDlg::OnBnClickedButton2Start2)
	ON_BN_CLICKED(IDC_BUTTON_Exit, &CMFCUIDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON1_Fresh, &CMFCUIDlg::OnBnClickedButton1Fresh)
	ON_BN_CLICKED(IDC_BUTTON2_Deal, &CMFCUIDlg::OnBnClickedButton2Deal)
END_MESSAGE_MAP()


// CMFCUIDlg ��Ϣ�������

BOOL CMFCUIDlg::OnInitDialog()
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

	
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	init_list_control();
	init_StatusBarr();
	
	//�����
	OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "gray", -1, "false",
		"[1] yuv (3264x2448)", "[1] HD USB Camera", 0, -1, &hv_AcqHandle);
	SetFramegrabberParam(hv_AcqHandle, "brightness", -64);
	SetFramegrabberParam(hv_AcqHandle, "gamma", 72);
	SetFramegrabberParam(hv_AcqHandle, "exposure", -4);
	GrabImageStart(hv_AcqHandle, -1);
	GrabImage(&ho_Image, hv_AcqHandle);
	Sleep(300);
	HWND hImgWnd = GetDlgItem(IDC_STATIC_Image)->m_hWnd;
	GetDlgItem(IDC_STATIC_Image)->GetClientRect(&rtWindow);
	OpenWindow(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), (Hlong)hImgWnd, "visible", "", &m_htWindow);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMFCUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCUIDlg::OnPaint()
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
HCURSOR CMFCUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}










//����ͼ��
void CMFCUIDlg::OnBnClickedButton3Image()
{
	
	CWnd* bmpShow = GetDlgItem(IDC_STATIC_Image);
	CDC *pdc = bmpShow->GetDC();
	CImage  imag;
	CRect rect;

	GetClientRect(&rect);        
	bmpShow->GetWindowRect(&rect);
	imag.Create(rect.Width(), rect.Height(), 32);
	::BitBlt(imag.GetDC(), 0, 0, rect.Width(), rect.Height(), pdc->m_hDC, 0, 0, SRCCOPY);

	TCHAR szFilter[] = _T("jpg file(.jpg)|.jpg|bmp file(.bmp)|.bmp|�����ļ�(*.*)|*.*||");  
	CFileDialog fileDlg(FALSE, _T("jpg"), _T(".jpg"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	fileDlg.m_ofn.lpstrTitle = _T("����ͼƬ");  
	CString picturePath;
	if (IDOK == fileDlg.DoModal())  
	{
		picturePath = fileDlg.GetPathName();  
	}

	HRESULT hResult = imag.Save(picturePath); 
	ReleaseDC(pdc);
	imag.ReleaseDC();


}

//���ݿ����
void CMFCUIDlg::OnBnClickedButton4Sql()
{
	//int nRow = m_ListCtrl.GetItemCount();
	if (m_ListCtrl.GetItemCount() == 0)
	{
		MessageBox(_T("û������Ҫ�洢!!"));
		return;
	}
	const char user[] = "root";
	const char pswd[] = "123456";
	const char host[] = "localhost";
	const char db[] = "product_data";
	unsigned int port = 3306;
	MYSQL mycont;
	MYSQL_RES *result;
	MYSQL_ROW sql_row;
	//int res;
	char select_user[1024];
	CString sqls;
	mysql_init(&mycont);
	CString clear;
	
	if (!mysql_real_connect(&mycont, host, user, pswd, db, port, NULL, 0))
	{
		MessageBox(_T("���ݿ�����ʧ��!"));
	}
	else 
	{
		mysql_query(&mycont, "SET NAMES GBK");
		clear = "DELETE  FROM  tb_data";
		mysql_real_query(&mycont, clear, strlen(clear));
		for (int i = 0; i < hv_Length; i++)
		{
		//char*   (LPTSTR)(LPCTSTR)
			CString ID = m_ListCtrl.GetItemText(i, 0);
			CString location = m_ListCtrl.GetItemText(i, 1);
			CString BarCont = m_ListCtrl.GetItemText(i, 2);
			CString SampleCont = m_ListCtrl.GetItemText(i, 3);
		    sprintf_s(select_user, "INSERT INTO tb_data(���,λ��,��������,�걾����) VALUES('%s','%s','%s','%s')", 
			ID, location, BarCont, SampleCont);
			//MessageBox(select_user);
			mysql_real_query(&mycont, select_user, strlen(select_user));
			UpdateData(false);
		}
		
		//int sum=mysql_query(&mycont, "SELECT COUNT(*) FROM tb_data");
	
		if (100 == hv_Length)
			{
				MessageBox(_T("����ɹ�!"));
			}
			else {
				MessageBox(_T("��������ʧ��!"));
			}
		}
	//UpdateData(false);
	mysql_close(&mycont);
	}
	
//����ΪExcel��Txt
void CMFCUIDlg::OnBnClickedButton5Txt()
{
	CString strFilePath;
	CString strFilter = _T("txt�ļ�(*.txt)|*.txt|xls�ļ�(*.xls)|*.xls|�����ļ�(*.*)|*.*||");
	CFileDialog dlg(FALSE, _T("txt|xls"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, strFilter, this);
	dlg.m_ofn.lpstrTitle = _T("��������");
	if (dlg.DoModal() != IDC_BUTTON5_Txt)
	{
		strFilePath = dlg.GetPathName();

		FILE *fp;
		const char* fpath = CStringA(strFilePath);
		fopen_s(&fp, fpath, "w");
		char str[1024];
		if (fp == NULL)
		{
			printf("save error\n");
			return;
		}
		int nHeadNum = m_ListCtrl.GetHeaderCtrl()->GetItemCount();
		LVCOLUMN lvcol;
		char str_out[256];
		int nColNUm;
		nColNUm = 0;
		lvcol.mask = LVCF_TEXT;
		lvcol.pszText = str_out;
		lvcol.cchTextMax = 256;
		while (m_ListCtrl.GetColumn(nColNUm, &lvcol))
		{
			nColNUm++;
			fprintf_s(fp, "%s\t", lvcol.pszText);
		}
		fprintf_s(fp, "\n", lvcol.pszText);
		int nRow = m_ListCtrl.GetItemCount();
		for (int i = 0; i < nRow; i++)
		{
			for (int j = 0; j < nColNUm; j++)
			{
				CString str_data = m_ListCtrl.GetItemText(i, j);
				fprintf_s(fp, "%s\t", str_data);
			}
			fprintf_s(fp, "\n");
		}
		fclose(fp);
	}
}

//��ʼ��list control
void CMFCUIDlg::init_list_control()
{
	//��ͷ
	m_ListCtrl.SetItemState(30, LVIS_FOCUSED | LVIS_SELECTED, LVIS_FOCUSED | LVIS_SELECTED);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListCtrl.InsertColumn(0, _T("���"));
	m_ListCtrl.InsertColumn(1, _T("λ��"));
	m_ListCtrl.InsertColumn(2, _T("��������"));
	m_ListCtrl.InsertColumn(3, _T("�걾����"));
	CRect rect;
	m_ListCtrl.GetClientRect(rect);
	m_ListCtrl.SetColumnWidth(0, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(1, 0.2*rect.Width());
	m_ListCtrl.SetColumnWidth(2, 0.3*rect.Width());
	m_ListCtrl.SetColumnWidth(3, 0.3*rect.Width());

	//�����������
	/*for (int i = 1; i < 101; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		int nRow = m_ListCtrl.InsertItem(i, str);
		m_ListCtrl.SetItemText(nRow, 1, _T("A1"));
		m_ListCtrl.SetItemText(nRow, 2, _T("2299200A"));
		m_ListCtrl.SetItemText(nRow, 3, _T(""));
	}*/
	/*CString fs[10] = { "809809","hoih8","kgoihpo098","ukhoiu909",
		"798yoikhoi","bkuh080","0980hku",
		"8080","y98tfyujh","709ygikug" };
	for (size_t i = 0; i < 10; i++)
	{
		CString temp = fs[i];
		CString str;
		str.Format(_T("%d"), i);
		int nRow = m_ListCtrl.InsertItem(i, str);
		m_ListCtrl.SetItemText(i, 2, temp);
	}*/
}

//��ʼ��state_bar
void CMFCUIDlg::init_StatusBarr()
{
	m_bar.Create(this);
	m_bar.SetIndicators(indicators, sizeof(indicators) / sizeof(UINT));
	CRect rect;
	GetWindowRect(rect);
	m_bar.SetPaneInfo(0, ID_INDICATOR_COUNT, SBPS_STRETCH, 0.2*rect.Width() );
	//m_bar.SetPaneInfo(1, ID_INDICATOR_TIME, SBPS_NORMAL, 0.8*rect.Width());
	

	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST, 0);
	SetTimer(1, 1000, NULL);
	CTime t1;
	//CString str;
	t1 = CTime::GetCurrentTime();
	//str = hv_Length.S();
	m_bar.SetPaneText(0, t1.Format("   %Y��%m��%d��   "));
	////m_bar.SetPaneText(1, " ʶ������ 100��   ʶ�� ?��");
}

//Timer
void CMFCUIDlg::OnTimer(UINT_PTR nIDEvent)
{
	CTime t1;
	t1 = CTime::GetCurrentTime();
	m_bar.SetPaneText(0, t1.Format("   %Y��%m��%d��   ����%w "));
	CDialog::OnTimer(nIDEvent);
}


//��ݼ��麯������
BOOL CMFCUIDlg::PreTranslateMessage(MSG* pMsg)
{
	switch (pMsg->wParam)
	{
	case VK_F1: {OnBnClickedButton2Start2(); break; }
	case VK_F2: {OnBnClickedButton2Deal(); break; }
	case VK_F3: {OnBnClickedButton3Image(); break; }
	case VK_F4: {OnBnClickedButton4Sql(); break; }
	case VK_F5: {OnBnClickedButton5Txt(); break; }
	

	}

	return CDialog::PreTranslateMessage(pMsg);
}

//���listctrl�ؼ���NM_CLICK��Ϣ��Ӧ����,�õ�������CListCtrl�����к�
void CMFCUIDlg::OnNMClickList(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{


		MoRow = pNMListView->iItem;
		MoCol = pNMListView->iSubItem;

	}

	*pResult = 0;
}

//�޸���������
void CMFCUIDlg::OnBnClickedButtonChangecontext()
{
	UpdateData();
	CString Mostr = m_ChangeContext;
	UpdateData(TRUE);
	m_ListCtrl.SetItemText(MoRow, MoCol + 1, _T(Mostr));
}

//itemѡ�и���
void CMFCUIDlg::OnCustomdrawList(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>(pNMHDR);

	*pResult = CDRF_DODEFAULT;
	if (CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if (CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage)
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ((CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage)
	{

		COLORREF clrNewTextColor, clrNewBkColor;

		int nItem = static_cast<int>(pLVCD->nmcd.dwItemSpec);

		POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
		int index = m_ListCtrl.GetNextSelectedItem(pos);

		if (index == nItem)//���Ҫˢ�µ���Ϊ��ǰѡ������������Ϊ��ɫ������ɫ��Ϊ��ɫ
		{
			clrNewTextColor = RGB(255, 255, 255);        //Set the text to white
			clrNewBkColor = RGB(49, 106, 197);        //Set the background color to blue
		}
		else
		{
			clrNewTextColor = RGB(0, 0, 0);        //set the text black
			clrNewBkColor = RGB(255, 255, 255);    //leave the background color white
		}

		pLVCD->clrText = clrNewTextColor;
		pLVCD->clrTextBk = clrNewBkColor;

		*pResult = CDRF_DODEFAULT;
	}

}


//��ͼ
void CMFCUIDlg::OnBnClickedButton2Start2()
{
	//HTuple DirectShow, hv_AcqHandle;
	
	HTuple width, height;
	//�����
	/*OpenFramegrabber("DirectShow", 1, 1, 0, 0, 0, 0, "default", 8, "gray", -1, "false",
		"[1] yuv (3264x2448)", "[1] HD USB Camera", 0, -1, &hv_AcqHandle);
	SetFramegrabberParam(hv_AcqHandle, "brightness", -64);
	SetFramegrabberParam(hv_AcqHandle, "gamma", 72);
	SetFramegrabberParam(hv_AcqHandle, "exposure", -4);
	GrabImageStart(hv_AcqHandle, -1);
	GrabImage(&ho_Image, hv_AcqHandle);
	Sleep(300);*/
	GrabImage(&ho_Image, hv_AcqHandle);
	WriteImage(ho_Image, "jpg", 0, "E:/1.1.jpg");
	GetImageSize(ho_Image, &height, &width);
	SetWindowAttr("background_color", "black");
	SetPart(m_htWindow, 0, 0, width, height);
	if (HDevWindowStack::IsOpen())
		HalconCpp::CloseWindow(m_htWindow);
	DispObj(ho_Image, m_htWindow);
	//��ձ��е�����
	m_ListCtrl.DeleteAllItems();
}


void CMFCUIDlg::OnBnClickedButtonExit()
{
	CloseFramegrabber(hv_AcqHandle);
	ExitProcess(0);
}


void CMFCUIDlg::OnBnClickedButton1Fresh()
{
	CStatic* pStatic = (CStatic*)GetDlgItem(IDC_STATIC_Image);
	pStatic->GetClientRect(&rtWindow);
	pStatic->GetDC()->FillSolidRect(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), RGB(240, 240, 240));
	pStatic->GetClientRect(&rtWindow); pStatic->GetDC()->FillSolidRect(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), RGB(192, 192, 192));
}


void CMFCUIDlg::OnBnClickedButton2Deal()
{
	// Local iconic variables
	HObject  ho_Circle, ho_ImageReduced;
	HObject  ho_SymbolXLDs1;

	// Local control variables
	HTuple  hv_CircleD, hv_Blank, hv_row, hv_column, hv_index, hv_DataCodeHandle;
	HTuple  hv_IndexY, hv_IndexX, hv_ResultHandles, hv_DecodedDataStrings1;

	//ReadImage(&ho_Image, "E:/1.jpg");
	//bin_threshold (Image, Region)
	hv_CircleD = 200;
	hv_Blank = 40;
	hv_row = 150;
	hv_column = 326;
	hv_index = HTuple();
	CreateDataCode2dModel("Data Matrix ECC 200", "default_parameters", "enhanced_recognition",
		&hv_DataCodeHandle);
	for (hv_IndexY = 0; hv_IndexY <= 9; hv_IndexY += 1)
	{
		for (hv_IndexX = 0; hv_IndexX <= 9; hv_IndexX += 1)
		{
			GenCircle(&ho_Circle, hv_row + ((hv_CircleD + hv_Blank)*hv_IndexY), hv_column + ((hv_CircleD + hv_Blank)*hv_IndexX),
				hv_CircleD / 2);
			SetTposition(m_htWindow, (hv_row - 120) + ((hv_CircleD + hv_Blank)*hv_IndexY),
				(hv_column + 40) + ((hv_CircleD + hv_Blank)*hv_IndexX));
			WriteString(m_htWindow, (hv_IndexX + (hv_IndexY * 10)) + 1);
			ReduceDomain(ho_Image, ho_Circle, &ho_ImageReduced);
			FindDataCode2d(ho_ImageReduced, &ho_SymbolXLDs1, hv_DataCodeHandle, HTuple(),
				HTuple(), &hv_ResultHandles, &hv_DecodedDataStrings1);
			DispObj(ho_SymbolXLDs1, m_htWindow);
			TupleConcat(hv_index, hv_DecodedDataStrings1, &hv_index);
			TupleLength(hv_index, &hv_Length);
			
		}
	}
	//��ʾʶ����Ŀ
	Bar_Total = hv_IndexY*hv_IndexX;
	UpdateData(false);
	Bar_Dealed = hv_Length;
	UpdateData(false);

	//�����������
	for (int i = 1; i < hv_Length + 1; i++)
	{
		CString str;
		str.Format(_T("%d"), i);
		CString temp = (CString)hv_index[i - 1].S();
		int nRow = m_ListCtrl.InsertItem(i, str);
		m_ListCtrl.SetItemText(nRow, 1, str);
		m_ListCtrl.SetItemText(nRow, 2, temp);
		m_ListCtrl.SetItemText(nRow, 3, _T(""));
	}
	/*if (100 == hv_Length)
	{
		for (int i = 1; i < 101; i++)
		{
			CString str;
			str.Format(_T("%d"), i);
			CString temp = (CString)hv_index[i - 1].S();
			int nRow = m_ListCtrl.InsertItem(i, str);
			m_ListCtrl.SetItemText(nRow, 1, str);
			m_ListCtrl.SetItemText(nRow, 2, temp);
			m_ListCtrl.SetItemText(nRow, 3, _T(""));
		}
	}
	else
	{
		MessageBox("ʶ��ʧ��");
		CloseFramegrabber(hv_AcqHandle);
		ExitProcess(0);
	}*/
	
	
	
}
