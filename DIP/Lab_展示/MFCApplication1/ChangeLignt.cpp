// ChangeLignt.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "ChangeLignt.h"
#include "afxdialogex.h"


// CChangeLignt �Ի���

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


// CChangeLignt ��Ϣ�������


BOOL CChangeLignt::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(true);//����

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}
