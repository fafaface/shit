// DlgGammaTrans.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgGammaTrans.h"
#include "afxdialogex.h"
#include<math.h>


// CDlgGammaTrans �Ի���

IMPLEMENT_DYNAMIC(CDlgGammaTrans, CDialogEx)

CDlgGammaTrans::CDlgGammaTrans(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAMMATRANS, pParent),m_r(1)
{

}

CDlgGammaTrans::~CDlgGammaTrans()
{
}

void CDlgGammaTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GAMMAR, m_r);
}


BEGIN_MESSAGE_MAP(CDlgGammaTrans, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Refresh3, &CDlgGammaTrans::OnBnClickedRefresh3)
END_MESSAGE_MAP()


// CDlgGammaTrans ��Ϣ�������


BOOL CDlgGammaTrans::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgGammaTrans::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CWnd * pWnd = GetDlgItem(IDC_GAMMATRANS);
	//�ַ���
	CString str;
	CPoint pLeft, pRight, pCenterTop, pCenterBottom;
	//ָ��
	CDC *pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	//�������ʶ���
	CPen* pPenRed = new CPen;
	//��ɫ���ʣ�������
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//�������ʶ���
	CPen* pPenBlue = new CPen;
	//��ɫ���ʣ�������
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//�������ʶ���
	CPen* pPenGreen = new CPen;
	//��ɫ���ʣ�������
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	//ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	//����������
	pDC->MoveTo(10, 10);
	//��ֱ��
	pDC->LineTo(10, 280);
	//ˮƽ��
	pDC->LineTo(320, 280);
	//д����
	str.Format("0");
	pDC->TextOut(10, 281, str);
	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	//����X��ͷ
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	//����Y��ͷ
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);


	//���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);


	CPoint start(0, 0);
	CPoint end;
	double c = 255 / pow(255, m_r);
	for (int i = 0; i < 255; i++)
	{


		int result = c*pow(i, m_r);
		int nextResult = c*pow(i + 1, m_r);
		start.x = i + 10;
		start.y = 280 - result;
		end.x = i + 10 + 1;
		end.y = 280 - nextResult;
		pDC->MoveTo(start);
		pDC->LineTo(end);

	}
}

 void CDlgGammaTrans::OnBnClickedRefresh3()
{
	////�����û�����
	UpdateData(TRUE);
	////�ػ�
	//InvalidateRect(m_MouseRect, TRUE);
	this->Invalidate();

}