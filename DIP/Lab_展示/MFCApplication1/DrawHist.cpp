// DrawHist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DrawHist.h"
#include "afxdialogex.h"


// CDrawHist �Ի���

IMPLEMENT_DYNAMIC(CDrawHist, CDialogEx)

CDrawHist::CDrawHist(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DrawHist, pParent)
	, minHist(0)
	, maxHist(0)
{

}

CDrawHist::~CDrawHist()
{
}

void CDrawHist::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, minHist);
	DDX_Text(pDX, IDC_EDIT2, maxHist);
}


BEGIN_MESSAGE_MAP(CDrawHist, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_Refresh, &CDrawHist::OnBnClickedRefresh)
END_MESSAGE_MAP()


// CDrawHist ��Ϣ�������


void CDrawHist::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	CDialog::OnPaint();
	CPoint start;
	CPoint end;

	CPen cPen;//��������
	cPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	dc.SelectObject(&cPen);

	//start.x = 15;
	//start.y = 20;
	//end.x = 545;
	//end.y = 340;

	//dc.MoveTo(start);
	//dc.LineTo(end);

	int delt = 500 / (maxHist - minHist);

	for (int i = 0; i < maxHist-minHist; i++)
	{
		start.x = 15 + i * delt;
		start.y = 20 + (1 - num[i]) * 320;
		end.x = start.x;
		end.y = 340;

		dc.MoveTo(start);
		dc.LineTo(end);
	}




}


void CDrawHist::OnBnClickedRefresh()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

}
