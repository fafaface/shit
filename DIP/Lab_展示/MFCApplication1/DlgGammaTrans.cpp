// DlgGammaTrans.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgGammaTrans.h"
#include "afxdialogex.h"
#include<math.h>


// CDlgGammaTrans 对话框

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


// CDlgGammaTrans 消息处理程序


BOOL CDlgGammaTrans::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	UpdateData(TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CDlgGammaTrans::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()

	CWnd * pWnd = GetDlgItem(IDC_GAMMATRANS);
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


	//更改成蓝色画笔
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
	////保存用户设置
	UpdateData(TRUE);
	////重绘
	//InvalidateRect(m_MouseRect, TRUE);
	this->Invalidate();

}