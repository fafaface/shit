// BitPlane.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "BitPlane.h"
#include "afxdialogex.h"


// CBitPlane �Ի���

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


// CBitPlane ��Ϣ�������


BOOL CBitPlane::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
