// BitPlane.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "BitPlane.h"
#include "afxdialogex.h"


// CBitPlane 对话框

IMPLEMENT_DYNAMIC(CBitPlane, CDialogEx)

CBitPlane::CBitPlane(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BITPLANE, pParent)
	, bitplane(0)
{

}

CBitPlane::~CBitPlane()
{
}

void CBitPlane::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, bitplane);
}


BEGIN_MESSAGE_MAP(CBitPlane, CDialogEx)
END_MESSAGE_MAP()


// CBitPlane 消息处理程序


BOOL CBitPlane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
