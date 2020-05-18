
// MFCApplication1View.cpp : CMFCApplication1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#include "DlgImgInfo.h"
#include"ChangeLignt.h"
#include"DrawHist.h"
#include"DlgHistogram.h"
#include"Dib.h"
#include"HistRange.h"
#include"PointTrans.h"
//#include"DlgInverse_V.h"
#include"Inverse.h"
//#include"DlgVTrans.h"
//#include"DlgInverse_L.h"
//#include"DlgLTrans.h"
#include"DlgLinerPara.h"
#include"BitPlane.h"
//#include"DlgLogTranse.h"
//#include"DlgGammaTrans.h"
#include"DlgThreshold.h"

#include"BMPSmooth.h"
#include"DlgSmooth.h"
#include"DlgMidFilter.h"
#include"DlgFilterSize.h"
//#include"DlgAddNoise.h"

#include"Morphologic.h"
#include"DlgGetStructElem.h"

#include"DlgIntensity.h"
#endif

#include "MFCApplication1Doc.h"
#include "MFCApplication1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1View

IMPLEMENT_DYNCREATE(CMFCApplication1View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_DispImgInfo, &CMFCApplication1View::OnDispimginfo)
	ON_COMMAND(ID_ChangeLight, &CMFCApplication1View::OnChangelight)
	ON_COMMAND(ID_Change256ColorToGray, &CMFCApplication1View::OnChange256colortogray)
	ON_COMMAND(ID_GrayToBinary, &CMFCApplication1View::OnGraytobinary)
	ON_COMMAND(ID_DrawHist, &CMFCApplication1View::OnDrawhist)
	ON_COMMAND(ID_DrawHist2, &CMFCApplication1View::OnDrawhist2)
	ON_COMMAND(ID_248grey, &CMFCApplication1View::On248grey)
	ON_COMMAND(ID_EDIT_UNDO, &CMFCApplication1View::OnEditUndo)
	ON_COMMAND(ID_PointInvert, &CMFCApplication1View::OnPointinvert)
	//ON_COMMAND(ID_InverseV, &CMFCApplication1View::OnInversev)
	ON_COMMAND(ID_24ColorTo8Color, &CMFCApplication1View::On24colorto8color)
	//ON_COMMAND(ID_VTrans, &CMFCApplication1View::OnVtrans)
	//ON_COMMAND(ID_INVERSEL, &CMFCApplication1View::OnInversel)
	//ON_COMMAND(ID_LTrans, &CMFCApplication1View::OnLtrans)
	ON_COMMAND(ID_LINEARTRANSE, &CMFCApplication1View::OnLineartranse)
	ON_COMMAND(ID_BITPLANE, &CMFCApplication1View::OnBitplane)
	//ON_COMMAND(ID_LOGTRANSE, &CMFCApplication1View::OnLogtranse)
	//ON_COMMAND(ID_GAMMATRANS, &CMFCApplication1View::OnGammatrans)
	ON_COMMAND(ID_ThresholdTrans, &CMFCApplication1View::OnThresholdtrans)
	ON_COMMAND(ID_BMPSMOOTH, &CMFCApplication1View::OnBmpsmooth)
	ON_COMMAND(ID_MIDFILTER, &CMFCApplication1View::OnMidfilter)
	ON_COMMAND(ID_OTHERFILTER, &CMFCApplication1View::OnOtherfilter)
	//ON_COMMAND(ID_ADDNOISE, &CMFCApplication1View::OnAddnoise)
	ON_COMMAND(ID_LAPLACESHARP, &CMFCApplication1View::OnLaplacesharp)
	//ON_COMMAND(ID_Sobel, &CMFCApplication1View::OnSobel)
	ON_COMMAND(ID_Erosion, &CMFCApplication1View::OnErosion)
	ON_COMMAND(ID_EXPAND, &CMFCApplication1View::OnExpand)
	ON_COMMAND(ID_OPEN, &CMFCApplication1View::OnOpen)
	ON_COMMAND(ID_CLOSE, &CMFCApplication1View::OnClose)
	ON_COMMAND(ID_INNERBOUNDARY, &CMFCApplication1View::OnInnerboundary)
	ON_COMMAND(ID_OUTERBOUNDART, &CMFCApplication1View::OnOuterboundart)
	ON_COMMAND(ID_BINARYSHOW, &CMFCApplication1View::OnBinaryshow)
	ON_COMMAND(ID_BINARYSHOW2, &CMFCApplication1View::OnBinaryshow2)
	ON_COMMAND(ID_DRAWHIST3, &CMFCApplication1View::OnDrawhist3)
END_MESSAGE_MAP()

// CMFCApplication1View 构造/析构

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: 在此处添加构造代码

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View 绘制

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	HGLOBAL hDIB = pDoc->GetHObject();

	// 判断DIB是否为空
	if (hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// 获取DIB宽度
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpDibSection);

		// 获取DIB高度
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// 输出DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}
}


// CMFCApplication1View 打印

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CMFCApplication1View 诊断

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View 消息处理程序


void CMFCApplication1View::OnDispimginfo()
{
	// TODO: 在此添加命令处理程序代码

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度和高度
	long	lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	CDlgImgInfo dlgPara;// 创建对话框		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;


	if (dlgPara.DoModal() != IDOK)// 显示对话框， 
	{
		//::MessageBox(NULL, L"error", L"welcome", MB_OK);

		return;
	}





	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定


}






void CMFCApplication1View::OnChangelight()
{
	// TODO: 在此添加命令处理程序代码

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																			////////////////////////////////////////////////////////////////////////////////////////////
	CChangeLignt dlgPara;// 创建对话框		
	
	

	if (dlgPara.DoModal() != IDOK)// 显示对话框
	{

		return;
	}




	for (int i = 0; i < lSrcLineBytes*lSrcHeight; i++)
	{


		int temp = (unsigned char)*lpSrcStartBits;

		if (temp + dlgPara.Light < 0)
			temp = 0;
		else if (temp + dlgPara.Light > 255)
			temp = 255;
		else temp += dlgPara.Light;

		*lpSrcStartBits = temp;

		lpSrcStartBits++;
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定


}


void CMFCApplication1View::OnChange256colortogray()
{
	// TODO: 在此添加命令处理程序代码


	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////




	BYTE bMap[256];//灰度映射表

	LPSTR lpSrcColorBits;//指向调色板的指针

	lpSrcColorBits = lpSrcDib + sizeof(BITMAPINFOHEADER);

	LPSTR lpSrc;// 指向DIB第i行，第j个象素的指针

	for (int i = 0; i<256; i++)//生成新的调色板,并将256种彩色根据公式转换为灰度
	{
		// 计算该颜色对应的灰度值g=0.299*r+0.587*g+0.114*b
		int j = 0;
		bMap[i] = (BYTE)(0.114 * lpSrcColorBits[j] + 0.587 * lpSrcColorBits[j + 1] + 0.299 * lpSrcColorBits[j + 2]+0.5);

		//改变原来的颜色表

		lpSrcColorBits[j] = lpSrcColorBits[j + 1] = lpSrcColorBits[j + 2] = i;
		lpSrcColorBits = lpSrcColorBits + 4;

	}
	// 更换每个象素的颜色索引（即按照灰度映射表换成灰度值）
	// 逐行扫描
	for (int i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrc = lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;

			*lpSrc = bMap[*lpSrc];// 变换
		}
	}

	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnGraytobinary()
{
	// TODO: 在此添加命令处理程序代码

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// 显示图像基本信息
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////






	BYTE bMap[256];//灰度映射表
	printf("\n对256色彩色图像变为256级灰度图像\n");


	LPSTR lpSrcColorBits;//指向调色板的指针
	LPSTR lpSrc;// 指向DIB第i行，第j个象素的指针
	lpSrcColorBits = lpSrcDib + sizeof(BITMAPINFOHEADER);


	for (int i = 0; i < 128; i++)
	{
		int j = 0;
		lpSrcColorBits[j] = lpSrcColorBits[j + 1] = lpSrcColorBits[j + 2] = 0;
		lpSrcColorBits = lpSrcColorBits + 4;
	}



	for (int i = 128; i < 256; i++)
	{
		int j = 0;
		lpSrcColorBits[j] = lpSrcColorBits[j + 1] = lpSrcColorBits[j + 2] = 255;
		lpSrcColorBits = lpSrcColorBits + 4;
	}



	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());



}


void CMFCApplication1View::OnDrawhist()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////

	HistRange range;

	if (range.DoModal() != IDOK)// 显示对话框
	{
		return;
	}


	CDrawHist dlg;

	for (int i = 0; i < 256; i++)
		dlg.num[i] = 0;

	int totalNum = 0;

	for (int r = 0; r < lSrcHeight; r++)
	{
		for (int c = 0; c < lSrcWidth; c++)
		{
			int temp = (unsigned char)*lpSrcStartBits;
			if (temp >= range.minHistRange&&temp <= range.histRangeMax)
			{
				dlg.num[temp]++;
				totalNum++;
			}

			lpSrcStartBits++;
		}
		for (int x = 0; x < lSrcLineBytes - lSrcWidth; x++)
			lpSrcStartBits++;
	}

	for (int i = 0; i < 256; i++)
		dlg.num[i] = dlg.num[i]/totalNum ;

	dlg.minHist = range.minHistRange;

	dlg.maxHist = range.histRangeMax;

	if (dlg.DoModal() != IDOK)// 显示对话框
	{
		return;
	}
}


void CMFCApplication1View::OnDrawhist2()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();

	// 指向DIB的指针
	LPSTR lpDIB;

	// 指向DIB象素指针
	LPSTR    lpDIBBits;

	LONG i, j;
	LONG m_lCount[256];
	unsigned char* lpSrc;
	LONG m_lWidth, m_lHeight;

	// 锁定DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	if (lpDIB == NULL)
	{
		//MessageBox("先打开图像！", "提示", MB_OK);
		return;
	}
	// 找到DIB图像象素起始位置
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// 判断是否是8-bit位图（这里为了方便，只处理8-bit位图，其它的可以类推）
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// 提示用户
		//MessageBox("目前只支持查看256色位图灰度直方图！", "系统提示", MB_ICONINFORMATION | MB_OK);

		// 解除锁定
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// 返回
		return;
	}
	// 更改光标形状
	BeginWaitCursor();
	//计算直方图
	// 重置计数为0
	for (i = 0; i < 256; i++)
	{
		// 清零
		m_lCount[i] = 0;
	}
	// 图像每行的字节数
	LONG lLineBytes;
	// 计算图像每行的字节数

	// 计算各个灰度值的计数
	m_lWidth = pDoc->m_dib.GetWidth(lpDIB);
	m_lHeight = pDoc->m_dib.GetHeight(lpDIB);
	lLineBytes = pDoc->m_dib.GetReqByteWidth(m_lWidth * pDoc->m_dib.GetBitCount(lpDIB));
	for (i = 0; i <m_lHeight; i++)
	{
		for (j = 0; j <m_lWidth; j++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			// 计数加1
			m_lCount[*(lpSrc)]++;
		}
	}
	// 创建对话框
	CDlgHistogram dlgHist;
	// 初始化变量值
	dlgHist.m_iLowGray = 0;
	dlgHist.m_iUpGray = 255;
	for (i = 0; i < 256; i++)
	{
		dlgHist.m_lCount[i] = m_lCount[i];
	}
	// 显示对话框
	if (dlgHist.DoModal() != IDOK)
	{
		// 返回
		return;
	}

	// 解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// 恢复光标
	EndWaitCursor();
}


void CMFCApplication1View::On248grey()//24位彩色转8位灰度
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();


	long lSrcLineBytes;     //图象每行的字节数
	long    lSrcWidth;      //图象的宽度和高度
	long    lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR   lpSrcDib;       //指向源图象的指针  
	LPSTR   lpSrcStartBits; //指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	{
	//	AfxMessageBox(L"对不起，不是24位图！");// 警告              
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定     
		return;                                  //返回
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);           // 找到DIB图象像素起始位置    
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);                  // 获取图象的宽度      
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);                    // 获取图象的高度  
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);       // 计算图象每行的字节数
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//new申请*pBmpBufNew--》不同的指针指向它的不同部分并修改--》整个赋值给lpSrcDib


	unsigned char*  lpSrc;//用来遍历RGB数据


	// 循环变量
	LONG    i;
	LONG    j;
	// 图像每行的字节数
	LONG    lLineBytes=lSrcLineBytes;

	BITMAPINFOHEADER *pHead;//新建的一个指向位图信息头类型变量的指针
	RGBQUAD* pColorTable;//新建的一个指向颜色表类型变量的指针
	int lineByteNew;//24位BMP图像转换成的8位BMP图像后每一行所占用的字节数
	int biBitCount = 8;

	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;//计算8位的位图每行所占用的字节数


	unsigned char *pBmpBufNew;//申请新的8位BMP数据所需要的空间，读位图数据进内存
	//BMP保存时，位图文件头里的数据会重新计算，不用管
	pBmpBufNew = new unsigned char[ sizeof(BITMAPINFOHEADER) + 256 * 4+ lineByteNew * lSrcHeight];//用来存储新的位图

	//void *memcpy(void *destin, void *source, unsigned n);
	//参数
	//	destin-- - 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
	//	source-- 指向要复制的数据源，类型强制转换为 void* 指针。
	//	n-- ------要被复制的字节数。

	memcpy(pBmpBufNew, (unsigned char *)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝

	pHead = (BITMAPINFOHEADER *)pBmpBufNew;//把pHead指针指向那一长串的内存的位图信息部分
	//pHead = pBmpBufNew;//报错
	pHead->biBitCount = 8;//改变位数
	pHead->biHeight = lSrcHeight;
	pHead->biWidth = lSrcWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew*lSrcHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;

	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));//把pColorTable指针指向那一长串的内存的颜色表部分
	//灰度图像有颜色表，且颜色表表项为
	if (biBitCount == 8) {
		//申请颜色表所需要的空间，给颜色表赋值
		for (int i = 0; i<256; i++)
		{
			pColorTable[i].rgbBlue = i;
			pColorTable[i].rgbGreen = i;
			pColorTable[i].rgbRed = i;
			pColorTable[i].rgbReserved = 0;
		}
	}

	int Red, Green, Blue, Gray, offset;
	offset = sizeof(BITMAPINFOHEADER) + 256 * 4;
	//逐行扫描
	for (i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;//从原RGB数据部分读取数据，lpSrc是桥梁
			Blue = *lpSrc;
			Green = *(++lpSrc);
			Red = *(++lpSrc);
			Gray = (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// 变换
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lSrcHeight - 1 - i) + j;//计算出灰度，存到长段内存对应部分。
			*lpSrc = Gray;
		}
	}
	//拷贝
	memcpy(lpSrcDib, pBmpBufNew,  sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);

	delete[]pBmpBufNew;



	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());



}


void CMFCApplication1View::OnEditUndo()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();


	long lSrcLineBytes;     //图象每行的字节数
	long    lSrcWidth;      //图象的宽度和高度
	long    lSrcHeight;
	int     lpSrcBitCount;       //图像的位深
	LPSTR   lpSrcDib;       //指向源图象的指针  
	LPSTR   lpSrcStartBits; //指向源像素的指针
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib) return;
	//if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// 判断是否是24-bpp位图
	//{
	//		AfxMessageBox("对不起，不是24位图！");// 警告              
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定     
	//	return;                                  //返回
	//}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);           // 找到DIB图象像素起始位置    
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);                  // 获取图象的宽度      
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);                    // 获取图象的高度  
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);       // 计算图象每行的字节数
	 /////////////////////////////////////////////////////////////////////////////////////////////////

	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 8)
	{
		int lineByteNew = (lSrcWidth * 8 / 8 + 3) / 4 * 4;//计算8位的位图每行所占用的字节数

		memcpy(lpSrcDib, pDoc->m_dib.lpdib2, sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);
	}

	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 24)
	{
		int lineByteNew = (lSrcWidth * 24 / 8 + 3) / 4 * 4;//计算8位的位图每行所占用的字节数

		memcpy(lpSrcDib, pDoc->m_dib.lpdib2, sizeof(BITMAPINFOHEADER) +  lineByteNew * lSrcHeight);
	}


	

//	AfxMessageBox("撤销完成");

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnPointinvert()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	
	Inverse dlgPara;// 创建对话框	

	if (dlgPara.DoModal() != IDOK)// 显示对话框 
	{
		return;
	}
	
	
	float fa= - 1;
	float fb = 255;
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


//void CMFCApplication1View::OnInversev()
//{
//	// TODO: 在此添加命令处理程序代码
//	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//图象每行的字节数
//	long	lSrcWidth;      //图象的宽度
//	long	lSrcHeight;    //图象的高度
//	int     lpSrcBitCount;       //图像的位深
//	LPSTR	lpSrcDib;		//指向源图象的指针	
//	LPSTR	lpSrcStartBits;	//指向源像素的指针
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
//	if (!lpSrcDib)
//	{
//		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
//		return;
//	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是8-bmp位图
	{
	AfxMessageBox(L"对不起，不是256色位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	
	CDlgInverse_V dlgPara;// 创建对话框	
	dlgPara.m_threshold = 128;
	if (dlgPara.DoModal() != IDOK)// 显示对话框 
	{
		return;
	}

	int point = dlgPara.m_threshold;

	InverseV(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}
	*/

void CMFCApplication1View::On24colorto8color()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 0)// 判断是否是24-bmp位图
	{
	AfxMessageBox("对不起，不是24位的位图！");// 警告
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// 解除锁定
	return;									//返回
	}										//判断是否是8-bpp位图,不是则返回
	


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////

	//new申请*pBmpBufNew--》不同的指针指向它的不同部分并修改--》整个赋值给lpSrcDib


	unsigned char*  lpSrc;//用来遍历RGB数据


						  // 循环变量
	LONG    i;
	LONG    j;
	// 图像每行的字节数
	LONG    lLineBytes = lSrcLineBytes;

	BITMAPINFOHEADER *pHead;//新建的一个指向位图信息头类型变量的指针
	RGBQUAD* pColorTable;//新建的一个指向颜色表类型变量的指针
	int lineByteNew;//24位BMP图像转换成的8位BMP图像后每一行所占用的字节数
	int biBitCount = 8;

	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;//计算8位的位图每行所占用的字节数


	unsigned char *pBmpBufNew;//申请新的8位BMP数据所需要的空间，读位图数据进内存
							  //BMP保存时，位图文件头里的数据会重新计算，不用管
	pBmpBufNew = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight];//用来存储新的位图

																								  //void *memcpy(void *destin, void *source, unsigned n);
																								  //参数
																								  //	destin-- - 指向用于存储复制内容的目标数组，类型强制转换为 void* 指针。
																								  //	source-- 指向要复制的数据源，类型强制转换为 void* 指针。
																								  //	n-- ------要被复制的字节数。

	memcpy(pBmpBufNew, (unsigned char *)lpSrcDib, sizeof(BITMAPINFOHEADER));//信息头拷贝

	pHead = (BITMAPINFOHEADER *)pBmpBufNew;//把pHead指针指向那一长串的内存的位图信息部分
										   //pHead = pBmpBufNew;//报错
	pHead->biBitCount = 8;//改变位数
	pHead->biHeight = lSrcHeight;
	pHead->biWidth = lSrcWidth;
	pHead->biClrUsed = 256;
	pHead->biClrImportant = 0;
	pHead->biCompression = 0;
	pHead->biPlanes = 1;
	pHead->biSize = 40;
	pHead->biSizeImage = lineByteNew*lSrcHeight;
	pHead->biXPelsPerMeter = 0;
	pHead->biYPelsPerMeter = 0;

	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));//把pColorTable指针指向那一长串的内存的颜色表部分
																	//灰度图像有颜色表，且颜色表表项为

	int R[4] = { 0,85,170,255 };
	int G[16] = { 0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255 };
	int B[4] = { 0,85,170,255 };


		//申请颜色表所需要的空间，给颜色表赋值
	int pos = 0;
	for (int r = 0; r < 4; r++)
		for (int g = 0; g < 16; g++)
			for (int b = 0; b < 4;b++)
		{
			pColorTable[pos].rgbRed = R[r];
			pColorTable[pos].rgbGreen = G[g];
			pColorTable[pos].rgbBlue = B[b];
			pColorTable[pos].rgbReserved = 0;
			pos++;
		}
	

	int Red, Green, Blue, result, offset;
	offset = sizeof(BITMAPINFOHEADER) + 256 * 4;
	//逐行扫描
	for (i = 0; i < lSrcHeight; i++)
	{
		//逐列扫描
		for (j = 0; j < lSrcWidth; j++)
		{
			// 指向DIB第i行，第j个象素的指针
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;//从原RGB数据部分读取数据，lpSrc是桥梁
			Blue = *lpSrc;
			Green = *(++lpSrc);
			Red = *(++lpSrc);

			Blue = Blue / 85 * 85;
			Green = Green / 17 * 17;
			Red = Red / 85 * 85;

			for (int i = 0; i < 256; i++)
			{
				if (Red == pColorTable[i].rgbRed&&Green == pColorTable[i].rgbGreen&&Blue == pColorTable[i].rgbBlue)
				{
					result = i; break;
				}
			}
			// 变换
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lSrcHeight - 1 - i) + j;//计算出灰度，存到长段内存对应部分。
			*lpSrc =result;
		}
	}
	//拷贝
	memcpy(lpSrcDib, pBmpBufNew, sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);

	delete[]pBmpBufNew;



	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}

/*
void CMFCApplication1View::OnVtrans()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	CDlgVTrans dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	VTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnInversel()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgInverse_L dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	InverseL(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnLtrans()
{
	// TODO: 在此添加命令处理程序代码

	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLTrans dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	LTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}*/


void CMFCApplication1View::OnLineartranse()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLinerPara dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	//int point = dlg.m_threshold;

	//LTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);



	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight,dlg.m_fA,dlg.m_fB );

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBitplane()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	CBitPlane dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	int bitNum = dlg.bitplane;

	BitPlane(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, bitNum);

	

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//void CMFCApplication1View::OnLogtranse()
//{
//
//
//	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//图象每行的字节数
//	long	lSrcWidth;      //图象的宽度
//	long	lSrcHeight;    //图象的高度
//	int     lpSrcBitCount;       //图像的位深
//	LPSTR	lpSrcDib;		//指向源图象的指针	
//	LPSTR	lpSrcStartBits;	//指向源像素的指针
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
//	if (!lpSrcDib)
//	{
//		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
//	{
//		AfxMessageBox("对不起，不是8位的位图！");// 警告
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
//		return;									//返回
//	}										//判断是否是8-bpp位图,不是则返回
//
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
//	////////////////////////////////////////////////////////////////////////////////////////////
//	CDlgLogTranse dlg;
//	dlg.m_c = 46;
//
//	if (dlg.DoModal() != IDOK)
//	{
//		return;
//	}
//
//
//	LogTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, dlg.m_c);
//
//
//
//	//设置文档修改标志
//	pDoc->SetModifiedFlag(true);
//	//更新视图
//	pDoc->UpdateAllViews(NULL);
//	//解除锁定
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//
//
//
//}


//void CMFCApplication1View::OnGammatrans()
//{
//	// TODO: 在此添加命令处理程序代码
//	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//图象每行的字节数
//	long	lSrcWidth;      //图象的宽度
//	long	lSrcHeight;    //图象的高度
//	int     lpSrcBitCount;       //图像的位深
//	LPSTR	lpSrcDib;		//指向源图象的指针	
//	LPSTR	lpSrcStartBits;	//指向源像素的指针
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("请先打开图片");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
//	{
//		AfxMessageBox("对不起，不是8位的位图！");// 警告
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
//		return;									//返回
//	}										//判断是否是8-bpp位图,不是则返回
//
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
//	////////////////////////////////////////////////////////////////////////////////////////////
//	CDlgGammaTrans dlg;
//	dlg.m_r = 1;
//	if (dlg.DoModal() != IDOK)
//
//	{
//		return;
//	}
//	GammaTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, dlg.m_r);
//
//	
//
//
//
//	//设置文档修改标志
//	pDoc->SetModifiedFlag(true);
//	//更新视图
//	pDoc->UpdateAllViews(NULL);
//	//解除锁定
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//
//}


void CMFCApplication1View::OnThresholdtrans()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgThreshold dlg;
	
	

	if (dlg.DoModal() != IDOK)

	{
		return;
	}
	

	ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, dlg.m_threshold);



	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnBmpsmooth()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////

	CDlgSmooth dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	if(0==dlg.m_intType)
		MeanTemplate(1,1,lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (1 == dlg.m_intType)
		GaussTemplate(1, 1, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (2 == dlg.m_intType)
		CustomMadeTemplate(dlg.m_iTempMX, dlg.m_iTempMY, dlg.m_iTempW, dlg.m_iTempH, dlg.m_fpArray, dlg.m_fTempC, lpSrcStartBits, lSrcWidth, lSrcHeight);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	


}


void CMFCApplication1View::OnMidfilter()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	//显示对话框，通过对话框获得相关参数
	CDlgMidFilter dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;

	}
	if (0 == dlg.m_iFilterType)
		MidFilter3X1(1, 0, 1, 3, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (1 == dlg.m_iFilterType)
		MidFilter1X3(0, 1, 3, 1, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (2 == dlg.m_iFilterType)
		MidFilter3X3(1, 1, 3, 3, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (3 == dlg.m_iFilterType)
		MidFilterCustomMade(dlg.m_iFilterMX,dlg.m_iFilterMY , dlg.m_iFilterW, dlg.m_iFilterH, lpSrcStartBits, lSrcWidth, lSrcHeight);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnOtherfilter()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	CDlgFilterSize dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	
	if (0 == dlg.m_filterType)
		MaxMinFilter(dlg.m_width, dlg.m_height, 0, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (1 == dlg.m_filterType)
		MaxMinFilter(dlg.m_width, dlg.m_height, 1, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (2 == dlg.m_filterType)
		MidPointFilter(dlg.m_width, dlg.m_height, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (3 == dlg.m_filterType)
		AdaptiveMidFilter(dlg.m_width, dlg.m_height,  lpSrcStartBits, lSrcWidth, lSrcHeight);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//void CMFCApplication1View::OnAddnoise()
//{
//	// TODO: 在此添加命令处理程序代码
//	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//图象每行的字节数
//	long	lSrcWidth;      //图象的宽度
//	long	lSrcHeight;    //图象的高度
//	int     lpSrcBitCount;       //图像的位深
//	LPSTR	lpSrcDib;		//指向源图象的指针	
//	LPSTR	lpSrcStartBits;	//指向源像素的指针
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("请先打开图片");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
//	{
//		AfxMessageBox("对不起，不是8位的位图！");// 警告
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
//		return;									//返回
//	}										//判断是否是8-bpp位图,不是则返回
//
//
//
//											//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
//																				////////////////////////////////////////////////////////////////////////////////////////////
//	CDlgAddNoise dlg;
//	if (dlg.DoModal() != IDOK)
//	{
//		return;
//	}
//	if (dlg.m_noistType == 0)
//		AddNoise(0, dlg.m_noistPersent/100, lpSrcStartBits, lSrcWidth, lSrcHeight);
//	if (dlg.m_noistType == 1)
//		AddNoise(1, dlg.m_noistPersent/100, lpSrcStartBits, lSrcWidth, lSrcHeight);
//
//	//设置文档修改标志
//	pDoc->SetModifiedFlag(true);
//	//更新视图
//	pDoc->UpdateAllViews(NULL);
//	//解除锁定
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//}


void CMFCApplication1View::OnLaplacesharp()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////

	float T[15] = { 0,-1,0,0,0,
				   -1,5,-1,0,0,
				    0,-1,0 ,0,0,};
	CustomMadeTemplate(1, 1, 3, 3, T,1, lpSrcStartBits, lSrcWidth, lSrcHeight);
	
	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());


}


//void CMFCApplication1View::OnSobel()
//{
//	// TODO: 在此添加命令处理程序代码
//	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//图象每行的字节数
//	long	lSrcWidth;      //图象的宽度
//	long	lSrcHeight;    //图象的高度
//	int     lpSrcBitCount;       //图像的位深
//	LPSTR	lpSrcDib;		//指向源图象的指针	
//	LPSTR	lpSrcStartBits;	//指向源像素的指针
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("请先打开图片");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
//	{
//		AfxMessageBox("对不起，不是8位的位图！");// 警告
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
//		return;									//返回
//	}										//判断是否是8-bpp位图,不是则返回



	//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////

	Sobel(lpSrcStartBits, lSrcWidth, lSrcHeight);

	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}*/


void CMFCApplication1View::OnErosion()
{
	// TODO: 在此添加命令处理程序代码

	
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//int x = dlg.m_nStructure1;
	//x = dlg.m_nStructure2;
	//x = dlg.m_nStructure3;
	//x = dlg.m_nStructure4;
	//x = dlg.m_nStructure5;
	//x = dlg.m_nStructure6;
	if (0 == dlg.m_nMode)
		Erosion(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (1 == dlg.m_nMode)
		Erosion(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if(2==dlg.m_nMode)
		Erosion(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnExpand()
{
	// TODO: 在此添加命令处理程序代码
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	if (0 == dlg.m_nMode)
		Expand(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (1 == dlg.m_nMode)
		Expand(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	if (2 == dlg.m_nMode)
		Expand(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnOpen()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//开运算，先腐蚀再膨胀
	if (0 == dlg.m_nMode)
	{
		Erosion(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Expand(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}

	if (1 == dlg.m_nMode)
	{
		Erosion(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Expand(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}

	if (2 == dlg.m_nMode)
	{
		Erosion(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Expand(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}



	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//闭运算，先膨胀再腐蚀
	if (0 == dlg.m_nMode)
	{
		Expand(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Erosion(0, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}

	if (1 == dlg.m_nMode)
	{
		Expand(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Erosion(1, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}

	
	if (2 == dlg.m_nMode)
	{
		Expand(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
		Erosion(2, dlg.check, lpSrcStartBits, lSrcWidth, lSrcHeight);
	}

	


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnInnerboundary()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
	////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char * lpSrcStartBitsBackUp = new unsigned char [lSrcLineBytes*lSrcHeight];
	memcpy(lpSrcStartBitsBackUp, lpSrcStartBits, lSrcLineBytes*lSrcHeight);
	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//内边界，先腐蚀，再异或
	
	if (0 == dlg.m_nMode)
	{
	Erosion(0, dlg.check, (char*)lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
	XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}

	if (1 == dlg.m_nMode)
	{
	Erosion(1, dlg.check, (char*)lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
	XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}


	if (2 == dlg.m_nMode)
	{
		Erosion(2, dlg.check,(char*) lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
		XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnOuterboundart()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char * lpSrcStartBitsBackUp = new unsigned char[lSrcLineBytes*lSrcHeight];
	memcpy(lpSrcStartBitsBackUp, lpSrcStartBits, lSrcLineBytes*lSrcHeight);
	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//外边界，先膨胀，再异或

	if (0 == dlg.m_nMode)
	{
		Expand(0, dlg.check, (char*)lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
		XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}

	if (1 == dlg.m_nMode)
	{
		Expand(1, dlg.check, (char*)lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
		XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}


	if (2 == dlg.m_nMode)
	{
		Expand(2, dlg.check, (char*)lpSrcStartBitsBackUp, lSrcWidth, lSrcHeight);
		XOR(lpSrcStartBits, lpSrcStartBitsBackUp, lSrcLineBytes*lSrcHeight);
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBinaryshow()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	BinaryShow(lpSrcStartBits, lSrcWidth, lSrcHeight);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBinaryshow2()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	BinaryFloyd(lpSrcStartBits, lSrcWidth, lSrcHeight);


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnDrawhist3()
{
	// TODO: 在此添加命令处理程序代码

	CMFCApplication1Doc* pDoc = GetDocument();// 获取文档
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//图象每行的字节数
	long	lSrcWidth;      //图象的宽度
	long	lSrcHeight;    //图象的高度
	int     lpSrcBitCount;       //图像的位深
	LPSTR	lpSrcDib;		//指向源图象的指针	
	LPSTR	lpSrcStartBits;	//指向源像素的指针

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// 锁定DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("请先打开图片");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// 判断是否是24-bmp位图
	{
		AfxMessageBox("对不起，不是8位的位图！");// 警告
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// 解除锁定
		return;									//返回
	}										//判断是否是8-bpp位图,不是则返回



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// 找到DIB图象像素起始位置	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// 获取图象的宽度	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// 获取图象的高度	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //获取图像位深
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// 计算图象每行的字节数
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgIntensity dlg;

	dlg.m_lWidth = lSrcWidth;
	dlg.m_lHeight = lSrcHeight;
	dlg.m_lpDIBBits = lpSrcStartBits;
	dlg.m_iLowGray = 0;
	dlg.m_iUpGray = 255;


	if (dlg.DoModal() != IDOK)
	{
		return;
	}


	//设置文档修改标志
	pDoc->SetModifiedFlag(true);
	//更新视图
	pDoc->UpdateAllViews(NULL);
	//解除锁定
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}
