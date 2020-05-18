// DlgMidFilter.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgMidFilter.h"
#include "afxdialogex.h"


// CDlgMidFilter 对话框

IMPLEMENT_DYNAMIC(CDlgMidFilter, CDialogEx)

CDlgMidFilter::CDlgMidFilter(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_MidianFilter, pParent)
	, m_iFilterType(3)
	, m_iFilterH(3)
	, m_iFilterW(1)
	, m_iFilterMX(0)
	, m_iFilterMY(1)
{

}

CDlgMidFilter::~CDlgMidFilter()
{
}

void CDlgMidFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Radio(pDX, IDC_RADIO1, m_iFilterType);
	DDX_Text(pDX, IDC_EDIT_FH, m_iFilterH);
	DDV_MinMaxInt(pDX, m_iFilterH, 1, 8);
	DDX_Text(pDX, IDC_EDIT_FW, m_iFilterW);
	DDV_MinMaxInt(pDX, m_iFilterW, 1, 8);

	DDX_Text(pDX, IDC_EDIT_FMX, m_iFilterMX);
	DDX_Text(pDX, IDC_EDIT_FMY, m_iFilterMY);

}


BEGIN_MESSAGE_MAP(CDlgMidFilter, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgMidFilter::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgMidFilter::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgMidFilter::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CDlgMidFilter::OnBnClickedRadio4)
END_MESSAGE_MAP()


// CDlgMidFilter 消息处理程序


void CDlgMidFilter::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码

	// 3×1模板
	m_iFilterType = 0;
	m_iFilterH = 1;
	m_iFilterW = 3;
	m_iFilterMX = 0;
	m_iFilterMY = 1;

	// 设置文本框不可用
	(CEdit *)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);

}


void CDlgMidFilter::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 1×3模板
	m_iFilterType = 1;
	m_iFilterH = 3;
	m_iFilterW = 1;
	m_iFilterMX = 1;
	m_iFilterMY = 0;

	// 设置文本框不可用
	(CEdit *)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);
}


void CDlgMidFilter::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码
	// 3×3模板
	m_iFilterType = 2;
	m_iFilterH = 3;
	m_iFilterW = 3;
	m_iFilterMX = 1;
	m_iFilterMY = 1;

	// 设置文本框不可用
	(CEdit *)GetDlgItem(IDC_EDIT_FH)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FW)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(FALSE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(FALSE);

	// 更新
	UpdateData(FALSE);
}


void CDlgMidFilter::OnBnClickedRadio4()
{
	// TODO: 在此添加控件通知处理程序代码
	// 自定义模板
	(CEdit *)GetDlgItem(IDC_EDIT_FH)->EnableWindow(TRUE);
	(CEdit *)GetDlgItem(IDC_EDIT_FW)->EnableWindow(TRUE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMX)->EnableWindow(TRUE);
	(CEdit *)GetDlgItem(IDC_EDIT_FMY)->EnableWindow(TRUE);
}
