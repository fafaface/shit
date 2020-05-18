// DlgSmooth.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgSmooth.h"
#include "afxdialogex.h"


// CDlgSmooth �Ի���

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


// CDlgSmooth ��Ϣ�������


void CDlgSmooth::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 3��3ƽ��ģ��
	m_intType = 0;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (FLOAT)(1.0 / 9.0);

	// ����ģ��Ԫ��
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

	// �����ı���״̬
	UpdateEdit();

	// ����
	UpdateData(FALSE);
}






void CDlgSmooth::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// 3��3��˹ģ��
	m_intType = 1;
	m_iTempH = 3;
	m_iTempW = 3;
	m_iTempMX = 1;
	m_iTempMY = 1;
	m_fTempC = (FLOAT)(1.0 / 16.0);

	// ����ģ��Ԫ��
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

	// �����ı���״̬
	UpdateEdit();

	// ����
	UpdateData(FALSE);
}


void CDlgSmooth::OnBnClickedRadio3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// �Զ���ģ��
	m_intType = 2;

	// �����ı���״̬
	UpdateEdit();
}


void CDlgSmooth::UpdateEdit()
{
	BOOL	bEnable;

	// ѭ������
	int		i;
	int		j;

	// �ж��ǲ����Զ���ģ��
	if (m_intType == 2)
	{
		bEnable = TRUE;
	}
	else
	{
		bEnable = FALSE;
	}

	// �����ı������״̬
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPH)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPW)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_TEMPC)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_MX)->EnableWindow(bEnable);
	(CEdit *)GetDlgItem(IDC_EDIT_MY)->EnableWindow(bEnable);

	// IDC_EDIT_V0��ID��ʵ��һ��������������ֵ������Resource.h�ж��塣

	// ����ģ��Ԫ���ı���Enable״̬
	for (i = IDC_EDIT_V0; i <= IDC_EDIT_V24; i++)
	{
		// �����ı��򲻿ɱ༭
		(CEdit *)GetDlgItem(i)->EnableWindow(bEnable);
	}

	// ��ʾӦ�ÿɼ���ģ��Ԫ���ı���
	for (i = 0; i < m_iTempH; i++)//��
	{
		for (j = 0; j < m_iTempW; j++)//��
		{
			// �����ı���ɼ�
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_SHOW);
		}
	}

	//����Ӧ�ò��ɼ���ģ��Ԫ���ı���ǰm_iTempH�еĺ��У�
	for (i = 0; i < m_iTempH; i++)
	{
		for (j = m_iTempW; j < 5; j++)
		{
			// ���ò��ɼ�
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);
		}
	}

	//// ����Ӧ�ò��ɼ���ģ��Ԫ���ı��򣨺��У�
	for (i = m_iTempH; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			// ���ò��ɼ�
			(CEdit *)GetDlgItem(IDC_EDIT_V0 + i * 5 + j)->ShowWindow(SW_HIDE);
		}
	}

}

void CDlgSmooth::OnEnKillfocusEditTemph()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����
	UpdateData(TRUE);

	// �����ı���״̬
	UpdateEdit();
}


void CDlgSmooth::OnEnKillfocusEditTempw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ����
	UpdateData(TRUE);

	// �����ı���״̬
	UpdateEdit();
}


BOOL CDlgSmooth::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgSmooth::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CDlgSmooth::OnEnChangeEditV24()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
