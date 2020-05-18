// Inverse.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "Inverse.h"
#include "afxdialogex.h"


// Inverse 对话框

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


// Inverse 消息处理程序


void Inverse::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CWnd * pWnd = GetDlgItem(IDC_INVERSE);
	//字符串
	CString str;
	CPoint pLeft, pRight, pCenterTop, pCenterBottom;
	//指针
	CDC *pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	//x1(left),y1(top),x2(right),y2(bottom)
	pDC->Rectangle(0, 0, 330, 300);
	//创建画笔对象
	CPen* pPenRed = new CPen;
	//红色画笔，红绿蓝
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//创建画笔对象
	CPen* pPenBlue = new CPen;
	//蓝色画笔，红绿蓝
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));
	//创建画笔对象
	CPen* pPenGreen = new CPen;
	//绿色画笔，红绿蓝
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));
	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	//绘制坐标轴
	pDC->MoveTo(10, 10);
	//垂直轴
	pDC->LineTo(10, 280);
	//水平轴
	pDC->LineTo(320, 280);
	//写坐标
	str.Format("0");
	pDC->TextOut(10, 281, str);
	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	//绘制X箭头
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);
	//绘制Y箭头
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);
	//更改成绿色画笔,画垂直线

	pDC->SelectObject(pPenGreen);
	pCenterTop.x = 10 + 0;//128;
	pCenterTop.y = 25;

	pCenterBottom.x = 10 + 0;//128;
	pCenterBottom.y = 280;
	pDC->MoveTo(pCenterTop);
	pDC->LineTo(pCenterBottom);

	//更改成蓝色画笔
	pDC->SelectObject(pPenBlue);
	//画两条变换线，没有计算斜率,没有交互
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
