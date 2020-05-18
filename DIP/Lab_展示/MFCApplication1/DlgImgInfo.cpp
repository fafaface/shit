// DlgImgInfo.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgImgInfo.h"
#include "afxdialogex.h"


// CDlgImgInfo �Ի���

IMPLEMENT_DYNAMIC(CDlgImgInfo, CDialogEx)

CDlgImgInfo::CDlgImgInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DlgImgInfo, pParent)
	, m_Height(0)
	, m_Width(0)
	, m_bitCount(0)
{

}

CDlgImgInfo::~CDlgImgInfo()
{
}

void CDlgImgInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_EDIT_Height, m_Height);
	DDX_Text(pDX, IDC_EDIT_Width, m_Width);
	DDX_Text(pDX, IDC_EDIT_BitCount, m_bitCount);
}


BEGIN_MESSAGE_MAP(CDlgImgInfo, CDialogEx)
END_MESSAGE_MAP()


// CDlgImgInfo ��Ϣ�������


BOOL CDlgImgInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	UpdateData(false);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
