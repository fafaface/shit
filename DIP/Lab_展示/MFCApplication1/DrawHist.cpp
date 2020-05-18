// DrawHist.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DrawHist.h"
#include "afxdialogex.h"


// CDrawHist 对话框

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


// CDrawHist 消息处理程序


void CDrawHist::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CDialog::OnPaint();
	CPoint start;
	CPoint end;

	CPen cPen;//创建画笔
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
	// TODO: 在此添加控件通知处理程序代码

}
