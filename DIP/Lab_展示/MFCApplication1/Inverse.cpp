// Inverse.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Inverse.h"
#include "afxdialogex.h"


// Inverse �Ի���

IMPLEMENT_DYNAMIC(Inverse, CDialogEx)

Inverse::Inverse(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INVERSE, pParent)
{

}

Inverse::~Inverse()
{
}

void Inverse::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Inverse, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// Inverse ��Ϣ�������


void Inverse::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CWnd * pWnd = GetDlgItem(IDC_INVERSE);
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
	//���ĳ���ɫ����,����ֱ��

	pDC->SelectObject(pPenGreen);
	pCenterTop.x = 10 + 0;//128;
	pCenterTop.y = 25;

	pCenterBottom.x = 10 + 0;//128;
	pCenterBottom.y = 280;
	pDC->MoveTo(pCenterTop);
	pDC->LineTo(pCenterBottom);

	//���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);
	//�������任�ߣ�û�м���б��,û�н���
	pLeft.x = 10;
	pLeft.y = 280;
	//pDC->MoveTo(10,280);
	pDC->MoveTo(pLeft);
	pCenterTop.x = 10 + 0;//128;
	pCenterTop.y = 25;
	//pDC->LineTo(138,25);
	pDC->LineTo(pCenterTop);
	pRight.x = 265;
	pRight.y = 280;
	//pDC->LineTo(265,280);
	pDC->LineTo(pRight);


}
