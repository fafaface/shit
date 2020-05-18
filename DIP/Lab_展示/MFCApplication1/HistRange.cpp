// HistRange.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "HistRange.h"
#include "afxdialogex.h"


// HistRange 对话框

IMPLEMENT_DYNAMIC(HistRange, CDialogEx)

HistRange::HistRange(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_HistRange, pParent)
	, minHistRange(0)
	, histRangeMax(0)
{

}

HistRange::~HistRange()
{
}

void HistRange::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, minHistRange);
	DDX_Text(pDX, IDC_EDIT2, histRangeMax);
}


BEGIN_MESSAGE_MAP(HistRange, CDialogEx)
END_MESSAGE_MAP()


// HistRange 消息处理程序


BOOL HistRange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
