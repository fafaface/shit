// ChangeLignt.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChangeLignt.h"
#include "afxdialogex.h"


// CChangeLignt 对话框

IMPLEMENT_DYNAMIC(CChangeLignt, CDialogEx)

CChangeLignt::CChangeLignt(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ChangeLignt, pParent)
	, Light(0)
{

}

CChangeLignt::~CChangeLignt()
{
}

void CChangeLignt::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Light);
}


BEGIN_MESSAGE_MAP(CChangeLignt, CDialogEx)
END_MESSAGE_MAP()


// CChangeLignt 消息处理程序


BOOL CChangeLignt::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(true);//输入

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
