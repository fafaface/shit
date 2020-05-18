// HistRange.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "HistRange.h"
#include "afxdialogex.h"


// HistRange �Ի���

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


// HistRange ��Ϣ�������


BOOL HistRange::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(true);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
