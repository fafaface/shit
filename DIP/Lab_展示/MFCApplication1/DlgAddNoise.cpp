// DlgAddNoise.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgAddNoise.h"
#include "afxdialogex.h"


// CDlgAddNoise 对话框

IMPLEMENT_DYNAMIC(CDlgAddNoise, CDialogEx)

//CDlgAddNoise::CDlgAddNoise(CWnd* pParent /*=NULL*/)
//	: CDialogEx(IDD_ADDNOISE, pParent)
//	, m_noistType(0)
//	, m_noistPersent(0)
//{
//
//}

CDlgAddNoise::~CDlgAddNoise()
{
}

void CDlgAddNoise::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_noistType);
	DDX_Text(pDX, IDC_EDIT1, m_noistPersent);
}


BEGIN_MESSAGE_MAP(CDlgAddNoise, CDialogEx)
END_MESSAGE_MAP()


// CDlgAddNoise 消息处理程序
