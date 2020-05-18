// DlgGetStructElem.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgGetStructElem.h"
#include "afxdialogex.h"


// CDlgGetStructElem �Ի���

IMPLEMENT_DYNAMIC(CDlgGetStructElem, CDialogEx)

CDlgGetStructElem::CDlgGetStructElem(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STRUCTUREELEM, pParent)
	, m_nMode(2)
{
	//����-1��ʾ���������ѡ�У�0��ʾ�����һ��RadioButton��ѡ�У�
	//1��ʾѡ�еڶ�����2��ʾѡ�е�������������
	
	m_nStructure1 = -1;
	m_nStructure2 = -1;
	m_nStructure3 = -1;
	m_nStructure4 = -1;
	m_nStructure5 = -1;
	m_nStructure6 = -1;
	m_nStructure7 = -1;
	m_nStructure8 = -1;
	m_nStructure9 = -1;

	for (int i = 0; i < 10; i++)
		check[i] = 0;
}

CDlgGetStructElem::~CDlgGetStructElem()
{
}

void CDlgGetStructElem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_Hori, m_nMode);

	DDX_Control(pDX, IDC_Structure9, m_Control9);
	DDX_Control(pDX, IDC_Structure8, m_Control8);
	DDX_Control(pDX, IDC_Structure7, m_Control7);
	DDX_Control(pDX, IDC_Structure6, m_Control6);
	DDX_Control(pDX, IDC_Structure5, m_Control5);
	DDX_Control(pDX, IDC_Structure4, m_Control4);
	DDX_Control(pDX, IDC_Structure3, m_Control3);
	DDX_Control(pDX, IDC_Structure2, m_Control2);
	DDX_Control(pDX, IDC_Structure1, m_Control1);

	DDX_Radio(pDX, IDC_Structure1, m_nStructure1);
	DDX_Radio(pDX, IDC_Structure2, m_nStructure2);
	DDX_Radio(pDX, IDC_Structure3, m_nStructure3);
	DDX_Radio(pDX, IDC_Structure4, m_nStructure4);
	DDX_Radio(pDX, IDC_Structure5, m_nStructure5);
	DDX_Radio(pDX, IDC_Structure6, m_nStructure6);
	DDX_Radio(pDX, IDC_Structure7, m_nStructure7);
	DDX_Radio(pDX, IDC_Structure8, m_nStructure8);
	DDX_Radio(pDX, IDC_Structure9, m_nStructure9);
}


BEGIN_MESSAGE_MAP(CDlgGetStructElem, CDialogEx)
	ON_BN_CLICKED(IDC_Hori, &CDlgGetStructElem::OnBnClickedHori)
	ON_BN_CLICKED(IDC_Vert, &CDlgGetStructElem::OnBnClickedVert)
	ON_BN_CLICKED(IDC_custom, &CDlgGetStructElem::OnBnClickedcustom)
	ON_BN_CLICKED(IDC_Structure1, &CDlgGetStructElem::OnBnClickedStructure1)
	ON_BN_CLICKED(IDC_Structure2, &CDlgGetStructElem::OnBnClickedStructure2)
	ON_BN_CLICKED(IDC_Structure3, &CDlgGetStructElem::OnBnClickedStructure3)
	ON_BN_CLICKED(IDC_Structure4, &CDlgGetStructElem::OnBnClickedStructure4)
	ON_BN_CLICKED(IDC_Structure5, &CDlgGetStructElem::OnBnClickedStructure5)
	ON_BN_CLICKED(IDC_Structure6, &CDlgGetStructElem::OnBnClickedStructure6)
	ON_BN_CLICKED(IDC_Structure7, &CDlgGetStructElem::OnBnClickedStructure7)
	ON_BN_CLICKED(IDC_Structure8, &CDlgGetStructElem::OnBnClickedStructure8)
	ON_BN_CLICKED(IDC_Structure9, &CDlgGetStructElem::OnBnClickedStructure9)
END_MESSAGE_MAP()


// CDlgGetStructElem ��Ϣ�������


void CDlgGetStructElem::OnBnClickedHori()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//Ҳ�ǿ���ͨ����������úʹ˹����ı�����0����-1

	for (int i = 1; i < 10; i++)
		check[i] = 0;
	check[4] = 1;
	check[5] = 1;
	check[6] = 1;


	((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure2))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure3))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure4))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure5))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure6))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure7))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure8))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure9))->SetCheck(FALSE);

	m_Control1.EnableWindow(FALSE);
	m_Control2.EnableWindow(FALSE);
	m_Control3.EnableWindow(FALSE);
	m_Control4.EnableWindow(FALSE);
	m_Control5.EnableWindow(FALSE);
	m_Control6.EnableWindow(FALSE);
	m_Control7.EnableWindow(FALSE);
	m_Control8.EnableWindow(FALSE);
	m_Control9.EnableWindow(FALSE);
}


void CDlgGetStructElem::OnBnClickedVert()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	for (int i = 1; i < 10; i++)
		check[i] = 0;
	check[2] = 1;
	check[5] = 1;
	check[8] = 1;

	((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure2))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure3))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure4))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure5))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure6))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure7))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure8))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_Structure9))->SetCheck(FALSE);

	m_Control1.EnableWindow(FALSE);
	m_Control2.EnableWindow(FALSE);
	m_Control3.EnableWindow(FALSE);
	m_Control4.EnableWindow(FALSE);
	m_Control5.EnableWindow(FALSE);
	m_Control6.EnableWindow(FALSE);
	m_Control7.EnableWindow(FALSE);
	m_Control8.EnableWindow(FALSE);
	m_Control9.EnableWindow(FALSE);

}


void CDlgGetStructElem::OnBnClickedcustom()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	for (int i = 1; i < 10; i++)
		check[i] = 0;


	((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure2))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure3))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure4))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure5))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure6))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure7))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure8))->SetCheck(FALSE);
	((CButton *)GetDlgItem(IDC_Structure9))->SetCheck(FALSE);

	m_Control1.EnableWindow(TRUE);
	m_Control2.EnableWindow(TRUE);
	m_Control3.EnableWindow(TRUE);
	m_Control4.EnableWindow(TRUE);
	m_Control5.EnableWindow(TRUE);
	m_Control6.EnableWindow(TRUE);
	m_Control7.EnableWindow(TRUE);
	m_Control8.EnableWindow(TRUE);
	m_Control9.EnableWindow(TRUE);
}


void CDlgGetStructElem::OnBnClickedStructure1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//if (m_nStructure1 == 0)
	//	m_nStructure1 = -1;
	//if (m_nStructure1 == -1)
	//{
	//	m_nStructure1 = 0;
	//	((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(TRUE);
	//}

	//if (m_nStructure1 == 0)
	//{
	//	m_nStructure1 = 1;
	//	((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(FALSE);
	//}
	//����0��û�б������
	if (check[1] == 0){
		((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(TRUE);
		check[1] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure1))->SetCheck(FALSE);
		check[1] = 0;
	}

	//AfxMessageBox("���");
}


void CDlgGetStructElem::OnBnClickedStructure2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[2] == 0) {
		((CButton *)GetDlgItem(IDC_Structure2))->SetCheck(TRUE);
		check[2] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure2))->SetCheck(FALSE);
		check[2] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[3] == 0) {
		((CButton *)GetDlgItem(IDC_Structure3))->SetCheck(TRUE);
		check[3] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure3))->SetCheck(FALSE);
		check[3] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[4] == 0) {
		((CButton *)GetDlgItem(IDC_Structure4))->SetCheck(TRUE);
		check[4] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure4))->SetCheck(FALSE);
		check[4] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure5()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[5] == 0) {
		((CButton *)GetDlgItem(IDC_Structure5))->SetCheck(TRUE);
		check[5] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure5))->SetCheck(FALSE);
		check[5] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure6()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[6] == 0) {
		((CButton *)GetDlgItem(IDC_Structure6))->SetCheck(TRUE);
		check[6] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure6))->SetCheck(FALSE);
		check[6] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure7()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[7] == 0) {
		((CButton *)GetDlgItem(IDC_Structure7))->SetCheck(TRUE);
		check[7] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure7))->SetCheck(FALSE);
		check[7] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[8] == 0) {
		((CButton *)GetDlgItem(IDC_Structure8))->SetCheck(TRUE);
		check[8] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure8))->SetCheck(FALSE);
		check[8] = 0;
	}
}


void CDlgGetStructElem::OnBnClickedStructure9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (check[9] == 0) {
		((CButton *)GetDlgItem(IDC_Structure9))->SetCheck(TRUE);
		check[9] = 1;
	}
	else {
		((CButton *)GetDlgItem(IDC_Structure9))->SetCheck(FALSE);
		check[9] = 0;
	}
}
