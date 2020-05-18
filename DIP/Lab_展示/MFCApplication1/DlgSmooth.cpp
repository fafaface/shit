// DlgSmooth.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgSmooth.h"
#include "afxdialogex.h"


// CDlgSmooth 对话框

IMPLEMENT_DYNAMIC(CDlgSmooth, CDialogEx)

CDlgSmooth::CDlgSmooth(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BMPSMOOTH, pParent)
	 ,m_fpArray(NULL)
	, m_intType(2)
	, m_iTempH(3)
	, m_iTempW(3)
	, m_iTempMX(0)
	, m_iTempMY(0)
	, m_fTempC(0)
{
	m_fpArray = new float[25];
	for (int i = 0; i < 25; i++)
		m_fpArray[i] = 0;


}

CDlgSmooth::~CDlgSmooth()
{
}

void CDlgSmooth::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_intType);

	DDX_Text(pDX, IDC_EDIT_TEMPH, m_iTempH);
	DDV_MinMaxInt(pDX, m_iTempH, 2, 5);

	DDX_Text(pDX, IDC_EDIT_TEMPW, m_iTempW);
	DDV_MinMaxInt(pDX, m_iTempW, 2, 5);

	DDX_Text(pDX, IDC_EDIT_MX, m_iTempMX);
	DDX_Text(pDX, IDC_EDIT_MY, m_iTempMY);
	DDX_Text(pDX, IDC_EDIT_TEMPC, m_fTempC);

	DDX_Text(pDX, IDC_EDIT_V0, m_fpArray[0]);
	DDX_Text(pDX, IDC_EDIT_V1, m_fpArray[1]);
	DDX_Text(pDX, IDC_EDIT_V2, m_fpArray[2]);
	DDX_Text(pDX, IDC_EDIT_V3, m_fpArray[3]);
	DDX_Text(pDX, IDC_EDIT_V4, m_fpArray[4]);
	DDX_Text(pDX, IDC_EDIT_V5, m_fpArray[5]);
	DDX_Text(pDX, IDC_EDIT_V6, m_fpArray[6]);
	DDX_Text(pDX, IDC_EDIT_V7, m_fpArray[7]);
	DDX_Text(pDX, IDC_EDIT_V8, m_fpArray[8]);
	DDX_Text(pDX, IDC_EDIT_V9, m_fpArray[9]);
	DDX_Text(pDX, IDC_EDIT_V10, m_fpArray[10]);
	DDX_Text(pDX, IDC_EDIT_V11, m_fpArray[11]);
	DDX_Text(pDX, IDC_EDIT_V12, m_fpArray[12]);
	DDX_Text(pDX, IDC_EDIT_V13, m_fpArray[13]);
	DDX_Text(pDX, IDC_EDIT_V14, m_fpArray[14]);
	DDX_Text(pDX, IDC_EDIT_V15, m_fpArray[15]);
	DDX_Text(pDX, IDC_EDIT_V16, m_fpArray[16]);
	DDX_Text(pDX, IDC_EDIT_V17, m_fpArray[17]);
	DDX_Text(pDX, IDC_EDIT_V18, m_fpArray[18]);
	DDX_Text(pDX, IDC_EDIT_V19, m_fpArray[19]);
	DDX_Text(pDX, IDC_EDIT_V20, m_fpArray[20]);
	DDX_Text(pDX, IDC_EDIT_V21, m_fpArray[21]);
	DDX_Text(pDX, IDC_EDIT_V22, m_fpArray[22]);
	DDX_Text(pDX, IDC_EDIT_V23, m_fpArray[23]);
	DDX_Text(pDX, IDC_EDIT_V24, m_fpArray[24]);

}


BEGIN_MESSAGE_MAP(CDlgSmooth, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO1, &CDlgSmooth::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDlgSmooth::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CDlgSmooth::OnBnClickedRadio3)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPH, &CDlgSmooth::OnEnKillfocusEditTemph)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPW, &CDlgSmooth::OnEnKillfocusEditTempw)
	ON_BN_CLICKED(IDOK, &CDlgSmooth::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_V24, &CDlgSmooth::OnEnChangeEditV24)
END_MESSAGE_MAP()


// CDlgSmooth 消息处理程序


void CDlgSmooth::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码
	// 3×3平均模板
	m_intType = 0;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (FLOAT)(1.0 / 9.0);

	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 1.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 1.0;
	m_fpArray[6] = 1.0;
	m_fpArray[7] = 1.0;
	m_fpArray[8] = 0.0;
	m_fpArray[9] = 0.0;
	m_fpArray[10] = 1.0;
	m_fpArray[11] = 1.0;
	m_fpArray[12] = 1.0;
	m_fpArray[13] = 0.0;
	m_fpArray[14] = 0.0;
	m_fpArray[15] = 0.0;
	m_fpArray[16] = 0.0;
	m_fpArray[17] = 0.0;
	m_fpArray[18] = 0.0;
	m_fpArray[19] = 0.0;
	m_fpArray[20] = 0.0;
	m_fpArray[21] = 0.0;
	m_fpArray[22] = 0.0;
	m_fpArray[23] = 0.0;
	m_fpArray[24] = 0.0;

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}






void CDlgSmooth::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 3×3高斯模板
	m_intType = 1;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (FLOAT)(1.0 / 16.0);

	// 设置模板元素
	m_fpArray[0] = 1.0;
	m_fpArray[1] = 2.0;
	m_fpArray[2] = 1.0;
	m_fpArray[3] = 0.0;
	m_fpArray[4] = 0.0;
	m_fpArray[5] = 2.0;
	m_fpArray[6] = 4.0;
	m_fpArray[7] = 2.0;
	m_fpArray[8] = 0.0;
	m_fpArray[9] = 0.0;
	m_fpArray[10] = 1.0;
	m_fpArray[11] = 2.0;
	m_fpArray[12] = 1.0;
	m_fpArray[13] = 0.0;
	m_fpArray[14] = 0.0;
	m_fpArray[15] = 0.0;
	m_fpArray[16] = 0.0;
	m_fpArray[17] = 0.0;
	m_fpArray[18] = 0.0;
	m_fpArray[19] = 0.0;
	m_fpArray[20] = 0.0;
	m_fpArray[21] = 0.0;
	m_fpArray[22] = 0.0;
	m_fpArray[23] = 0.0;
	m_fpArray[24] = 0.0;

	// 更新文本框状态
	UpdateEdit();

	// 更新
	UpdateData(FALSE);
}


void CDlgSmooth::OnBnClickedRadio3()
{
	// TODO: 在此添加控件通知处理程序代码

	// 自定义模板
	m_intType = 2;

	// 更新文本框状态
	UpdateEdit();
}


void CDlgSmooth::UpdateEdit()
{
	BOOL	bEnable;

	// 循环变量
	int		i;
	int		j;

	// 判断是不是自定义模板
	if (m_intType == 2)
	{
		bEnable = TRUE;
	}
	else
	{
		bEnable = FALSE;
	}

	// 设置文本框可用状态
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPH)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPW)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPC)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_MX)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_MY)->EnableWindow(bEnable);

	// IDC_EDIT_V0等ID其实是一个整数，它的数值定义在Resource.h中定义。

	// 设置模板元素文本框Enable状态
	for (i = IDC_EDIT_V0; i <= IDC_EDIT_V24; i++)
	{
		// 设置文本框不可编辑
		(CEdit *)GetDlgItem(i)->EnableWindow(bEnable);
	}

	// 显示应该可见的模板元素文本框
	for (i = 0; i < m_iTempH; i++)//行
	{
		for (j = 0; j < m_iTempW; j++)//列
		{
			// 设置文本框可见
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_SHOW);
		}
	}

	//隐藏应该不可见的模板元素文本框（前m_iTempH行的后几列）
	for (i = 0; i < m_iTempH; i++)
	{
		for (j = m_iTempW; j < 5; j++)
		{
			// 设置不可见
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);
		}
	}

	//// 隐藏应该不可见的模板元素文本框（后几行）
	for (i = m_iTempH; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			// 设置不可见
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);
		}
	}

}

void CDlgSmooth::OnEnKillfocusEditTemph()
{
	// TODO: 在此添加控件通知处理程序代码
	// 更新
	UpdateData(TRUE);

	// 更新文本框状态
	UpdateEdit();
}


void CDlgSmooth::OnEnKillfocusEditTempw()
{
	// TODO: 在此添加控件通知处理程序代码
	// 更新
	UpdateData(TRUE);

	// 更新文本框状态
	UpdateEdit();
}


BOOL CDlgSmooth::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgSmooth::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CDlgSmooth::OnEnChangeEditV24()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
