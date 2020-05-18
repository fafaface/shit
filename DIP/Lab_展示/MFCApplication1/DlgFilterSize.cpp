// DlgFilterSize.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgFilterSize.h"
#include "afxdialogex.h"


// CDlgFilterSize �Ի���

IMPLEMENT_DYNAMIC(CDlgFilterSize, CDialogEx)

CDlgFilterSize::CDlgFilterSize(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_FILTERSIZE, pParent)
	, m_filterType(0)
	, m_width(0)
	, m_height(0)
{

}

CDlgFilterSize::~CDlgFilterSize()
{
}

void CDlgFilterSize::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_filterType);
	DDX_Text(pDX, IDC_EDIT1, m_width);
	DDX_Text(pDX, IDC_EDIT2, m_height);
}


BEGIN_MESSAGE_MAP(CDlgFilterSize, CDialogEx)

	ON_BN_CLICKED(IDC_RADIO1, &CDlgFilterSize::OnBnClickedRadio1)
END_MESSAGE_MAP()


// CDlgFilterSize ��Ϣ�������





void CDlgFilterSize::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
