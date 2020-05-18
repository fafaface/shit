
// MFCApplication1View.cpp : CMFCApplication1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
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

// CMFCApplication1View ����/����

CMFCApplication1View::CMFCApplication1View()
{
	// TODO: �ڴ˴���ӹ������

}

CMFCApplication1View::~CMFCApplication1View()
{
}

BOOL CMFCApplication1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCApplication1View ����

void CMFCApplication1View::OnDraw(CDC* pDC)
{
	CMFCApplication1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	HGLOBAL hDIB = pDoc->GetHObject();

	// �ж�DIB�Ƿ�Ϊ��
	if (hDIB != NULL)
	{
		LPSTR lpDibSection = (LPSTR) ::GlobalLock((HGLOBAL)hDIB);

		// ��ȡDIB���
		int cxDIB = (int)pDoc->m_dib.GetWidth(lpDibSection);

		// ��ȡDIB�߶�
		int cyDIB = (int)pDoc->m_dib.GetHeight(lpDibSection);
		::GlobalUnlock((HGLOBAL)hDIB);
		CRect rcDIB;
		rcDIB.top = rcDIB.left = 0;
		rcDIB.right = cxDIB;
		rcDIB.bottom = cyDIB;
		CRect rcDest = rcDIB;
		// ���DIB
		pDoc->m_dib.DrawDib(pDC->m_hDC, &rcDest, pDoc->GetHObject(),
			&rcDIB, pDoc->GetDocPal());
	}
}


// CMFCApplication1View ��ӡ

BOOL CMFCApplication1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCApplication1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCApplication1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMFCApplication1View ���

#ifdef _DEBUG
void CMFCApplication1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication1Doc* CMFCApplication1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication1Doc)));
	return (CMFCApplication1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication1View ��Ϣ�������


void CMFCApplication1View::OnDispimginfo()
{
	// TODO: �ڴ���������������

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// ��ʾͼ�������Ϣ
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ�Ⱥ͸߶�
	long	lSrcHeight;
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////
	CDlgImgInfo dlgPara;// �����Ի���		
	dlgPara.m_Width = lSrcWidth;
	dlgPara.m_Height = lSrcHeight;
	dlgPara.m_bitCount = lpSrcBitCount;


	if (dlgPara.DoModal() != IDOK)// ��ʾ�Ի��� 
	{
		//::MessageBox(NULL, L"error", L"welcome", MB_OK);

		return;
	}





	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������


}






void CMFCApplication1View::OnChangelight()
{
	// TODO: �ڴ���������������

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// ��ʾͼ�������Ϣ
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																			////////////////////////////////////////////////////////////////////////////////////////////
	CChangeLignt dlgPara;// �����Ի���		
	
	

	if (dlgPara.DoModal() != IDOK)// ��ʾ�Ի���
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);

	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������


}


void CMFCApplication1View::OnChange256colortogray()
{
	// TODO: �ڴ���������������


	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// ��ʾͼ�������Ϣ
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////




	BYTE bMap[256];//�Ҷ�ӳ���

	LPSTR lpSrcColorBits;//ָ���ɫ���ָ��

	lpSrcColorBits = lpSrcDib + sizeof(BITMAPINFOHEADER);

	LPSTR lpSrc;// ָ��DIB��i�У���j�����ص�ָ��

	for (int i = 0; i<256; i++)//�����µĵ�ɫ��,����256�ֲ�ɫ���ݹ�ʽת��Ϊ�Ҷ�
	{
		// �������ɫ��Ӧ�ĻҶ�ֵg=0.299*r+0.587*g+0.114*b
		int j = 0;
		bMap[i] = (BYTE)(0.114 * lpSrcColorBits[j] + 0.587 * lpSrcColorBits[j + 1] + 0.299 * lpSrcColorBits[j + 2]+0.5);

		//�ı�ԭ������ɫ��

		lpSrcColorBits[j] = lpSrcColorBits[j + 1] = lpSrcColorBits[j + 2] = i;
		lpSrcColorBits = lpSrcColorBits + 4;

	}
	// ����ÿ�����ص���ɫ�����������ջҶ�ӳ����ɻҶ�ֵ��
	// ����ɨ��
	for (int i = 0; i < lSrcHeight; i++)
	{
		//����ɨ��
		for (int j = 0; j < lSrcWidth; j++)
		{
			lpSrc = lpSrcStartBits + lSrcLineBytes * (lSrcHeight - 1 - i) + j;

			*lpSrc = bMap[*lpSrc];// �任
		}
	}

	pDoc->SetModifiedFlag(TRUE);
	pDoc->UpdateAllViews(NULL);
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnGraytobinary()
{
	// TODO: �ڴ���������������

	//::MessageBox(NULL, L"hello", L"welcome", MB_OK);


	// ��ʾͼ�������Ϣ
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////






	BYTE bMap[256];//�Ҷ�ӳ���
	printf("\n��256ɫ��ɫͼ���Ϊ256���Ҷ�ͼ��\n");


	LPSTR lpSrcColorBits;//ָ���ɫ���ָ��
	LPSTR lpSrc;// ָ��DIB��i�У���j�����ص�ָ��
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
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////

	HistRange range;

	if (range.DoModal() != IDOK)// ��ʾ�Ի���
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

	if (dlg.DoModal() != IDOK)// ��ʾ�Ի���
	{
		return;
	}
}


void CMFCApplication1View::OnDrawhist2()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();

	// ָ��DIB��ָ��
	LPSTR lpDIB;

	// ָ��DIB����ָ��
	LPSTR    lpDIBBits;

	LONG i, j;
	LONG m_lCount[256];
	unsigned char* lpSrc;
	LONG m_lWidth, m_lHeight;

	// ����DIB
	lpDIB = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());
	if (lpDIB == NULL)
	{
		//MessageBox("�ȴ�ͼ��", "��ʾ", MB_OK);
		return;
	}
	// �ҵ�DIBͼ��������ʼλ��
	lpDIBBits = pDoc->m_dib.GetBits(lpDIB);

	// �ж��Ƿ���8-bitλͼ������Ϊ�˷��㣬ֻ����8-bitλͼ�������Ŀ������ƣ�
	if (pDoc->m_dib.GetColorNum(lpDIB) != 256)
	{
		// ��ʾ�û�
		//MessageBox("Ŀǰֻ֧�ֲ鿴256ɫλͼ�Ҷ�ֱ��ͼ��", "ϵͳ��ʾ", MB_ICONINFORMATION | MB_OK);

		// �������
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

		// ����
		return;
	}
	// ���Ĺ����״
	BeginWaitCursor();
	//����ֱ��ͼ
	// ���ü���Ϊ0
	for (i = 0; i < 256; i++)
	{
		// ����
		m_lCount[i] = 0;
	}
	// ͼ��ÿ�е��ֽ���
	LONG lLineBytes;
	// ����ͼ��ÿ�е��ֽ���

	// ��������Ҷ�ֵ�ļ���
	m_lWidth = pDoc->m_dib.GetWidth(lpDIB);
	m_lHeight = pDoc->m_dib.GetHeight(lpDIB);
	lLineBytes = pDoc->m_dib.GetReqByteWidth(m_lWidth * pDoc->m_dib.GetBitCount(lpDIB));
	for (i = 0; i <m_lHeight; i++)
	{
		for (j = 0; j <m_lWidth; j++)
		{
			lpSrc = (unsigned char *)lpDIBBits + lLineBytes * i + j;
			// ������1
			m_lCount[*(lpSrc)]++;
		}
	}
	// �����Ի���
	CDlgHistogram dlgHist;
	// ��ʼ������ֵ
	dlgHist.m_iLowGray = 0;
	dlgHist.m_iUpGray = 255;
	for (i = 0; i < 256; i++)
	{
		dlgHist.m_lCount[i] = m_lCount[i];
	}
	// ��ʾ�Ի���
	if (dlgHist.DoModal() != IDOK)
	{
		// ����
		return;
	}

	// �������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	// �ָ����
	EndWaitCursor();
}


void CMFCApplication1View::On248grey()//24λ��ɫת8λ�Ҷ�
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();


	long lSrcLineBytes;     //ͼ��ÿ�е��ֽ���
	long    lSrcWidth;      //ͼ��Ŀ�Ⱥ͸߶�
	long    lSrcHeight;
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR   lpSrcDib;       //ָ��Դͼ���ָ��  
	LPSTR   lpSrcStartBits; //ָ��Դ���ص�ָ��
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib) return;
	if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// �ж��Ƿ���24-bppλͼ
	{
	//	AfxMessageBox(L"�Բ��𣬲���24λͼ��");// ����              
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������     
		return;                                  //����
	}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);           // �ҵ�DIBͼ��������ʼλ��    
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);                  // ��ȡͼ��Ŀ��      
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);                    // ��ȡͼ��ĸ߶�  
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);       // ����ͼ��ÿ�е��ֽ���
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//new����*pBmpBufNew--����ͬ��ָ��ָ�����Ĳ�ͬ���ֲ��޸�--��������ֵ��lpSrcDib


	unsigned char*  lpSrc;//��������RGB����


	// ѭ������
	LONG    i;
	LONG    j;
	// ͼ��ÿ�е��ֽ���
	LONG    lLineBytes=lSrcLineBytes;

	BITMAPINFOHEADER *pHead;//�½���һ��ָ��λͼ��Ϣͷ���ͱ�����ָ��
	RGBQUAD* pColorTable;//�½���һ��ָ����ɫ�����ͱ�����ָ��
	int lineByteNew;//24λBMPͼ��ת���ɵ�8λBMPͼ���ÿһ����ռ�õ��ֽ���
	int biBitCount = 8;

	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;//����8λ��λͼÿ����ռ�õ��ֽ���


	unsigned char *pBmpBufNew;//�����µ�8λBMP��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
	//BMP����ʱ��λͼ�ļ�ͷ������ݻ����¼��㣬���ù�
	pBmpBufNew = new unsigned char[ sizeof(BITMAPINFOHEADER) + 256 * 4+ lineByteNew * lSrcHeight];//�����洢�µ�λͼ

	//void *memcpy(void *destin, void *source, unsigned n);
	//����
	//	destin-- - ָ�����ڴ洢�������ݵ�Ŀ�����飬����ǿ��ת��Ϊ void* ָ�롣
	//	source-- ָ��Ҫ���Ƶ�����Դ������ǿ��ת��Ϊ void* ָ�롣
	//	n-- ------Ҫ�����Ƶ��ֽ�����

	memcpy(pBmpBufNew, (unsigned char *)lpSrcDib, sizeof(BITMAPINFOHEADER));//��Ϣͷ����

	pHead = (BITMAPINFOHEADER *)pBmpBufNew;//��pHeadָ��ָ����һ�������ڴ��λͼ��Ϣ����
	//pHead = pBmpBufNew;//����
	pHead->biBitCount = 8;//�ı�λ��
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

	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));//��pColorTableָ��ָ����һ�������ڴ����ɫ����
	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ
	if (biBitCount == 8) {
		//������ɫ������Ҫ�Ŀռ䣬����ɫ��ֵ
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
	//����ɨ��
	for (i = 0; i < lSrcHeight; i++)
	{
		//����ɨ��
		for (j = 0; j < lSrcWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;//��ԭRGB���ݲ��ֶ�ȡ���ݣ�lpSrc������
			Blue = *lpSrc;
			Green = *(++lpSrc);
			Red = *(++lpSrc);
			Gray = (BYTE)(0.299 * Red + 0.587 * Green + 0.114 * Blue + 0.5);
			// �任
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lSrcHeight - 1 - i) + j;//������Ҷȣ��浽�����ڴ��Ӧ���֡�
			*lpSrc = Gray;
		}
	}
	//����
	memcpy(lpSrcDib, pBmpBufNew,  sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);

	delete[]pBmpBufNew;



	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());



}


void CMFCApplication1View::OnEditUndo()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();


	long lSrcLineBytes;     //ͼ��ÿ�е��ֽ���
	long    lSrcWidth;      //ͼ��Ŀ�Ⱥ͸߶�
	long    lSrcHeight;
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR   lpSrcDib;       //ָ��Դͼ���ָ��  
	LPSTR   lpSrcStartBits; //ָ��Դ���ص�ָ��
	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib) return;
	//if (pDoc->m_dib.GetBitCount(lpSrcDib) != 24)// �ж��Ƿ���24-bppλͼ
	//{
	//		AfxMessageBox("�Բ��𣬲���24λͼ��");// ����              
	//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������     
	//	return;                                  //����
	//}
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);           // �ҵ�DIBͼ��������ʼλ��    
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);                  // ��ȡͼ��Ŀ��      
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);                    // ��ȡͼ��ĸ߶�  
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);                    //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);       // ����ͼ��ÿ�е��ֽ���
	 /////////////////////////////////////////////////////////////////////////////////////////////////

	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 8)
	{
		int lineByteNew = (lSrcWidth * 8 / 8 + 3) / 4 * 4;//����8λ��λͼÿ����ռ�õ��ֽ���

		memcpy(lpSrcDib, pDoc->m_dib.lpdib2, sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);
	}

	if (pDoc->m_dib.GetBitCount(lpSrcDib) == 24)
	{
		int lineByteNew = (lSrcWidth * 24 / 8 + 3) / 4 * 4;//����8λ��λͼÿ����ռ�õ��ֽ���

		memcpy(lpSrcDib, pDoc->m_dib.lpdib2, sizeof(BITMAPINFOHEADER) +  lineByteNew * lSrcHeight);
	}


	

//	AfxMessageBox("�������");

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnPointinvert()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	*/


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////
	
	Inverse dlgPara;// �����Ի���	

	if (dlgPara.DoModal() != IDOK)// ��ʾ�Ի��� 
	{
		return;
	}
	
	
	float fa= - 1;
	float fb = 255;
	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, fa, fb);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


//void CMFCApplication1View::OnInversev()
//{
//	// TODO: �ڴ���������������
//	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
//	long	lSrcWidth;      //ͼ��Ŀ��
//	long	lSrcHeight;    //ͼ��ĸ߶�
//	int     lpSrcBitCount;       //ͼ���λ��
//	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
//	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
//	if (!lpSrcDib)
//	{
//		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
//		return;
//	}


	/*
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���8-bmpλͼ
	{
	AfxMessageBox(L"�Բ��𣬲���256ɫλͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	
	CDlgInverse_V dlgPara;// �����Ի���	
	dlgPara.m_threshold = 128;
	if (dlgPara.DoModal() != IDOK)// ��ʾ�Ի��� 
	{
		return;
	}

	int point = dlgPara.m_threshold;

	InverseV(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}
	*/

void CMFCApplication1View::On24colorto8color()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}


	
	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 0)// �ж��Ƿ���24-bmpλͼ
	{
	AfxMessageBox("�Բ��𣬲���24λ��λͼ��");// ����
	::GlobalUnlock((HGLOBAL) pDoc->GetHObject());// �������
	return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
	


	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////

	//new����*pBmpBufNew--����ͬ��ָ��ָ�����Ĳ�ͬ���ֲ��޸�--��������ֵ��lpSrcDib


	unsigned char*  lpSrc;//��������RGB����


						  // ѭ������
	LONG    i;
	LONG    j;
	// ͼ��ÿ�е��ֽ���
	LONG    lLineBytes = lSrcLineBytes;

	BITMAPINFOHEADER *pHead;//�½���һ��ָ��λͼ��Ϣͷ���ͱ�����ָ��
	RGBQUAD* pColorTable;//�½���һ��ָ����ɫ�����ͱ�����ָ��
	int lineByteNew;//24λBMPͼ��ת���ɵ�8λBMPͼ���ÿһ����ռ�õ��ֽ���
	int biBitCount = 8;

	lineByteNew = (lSrcWidth * biBitCount / 8 + 3) / 4 * 4;//����8λ��λͼÿ����ռ�õ��ֽ���


	unsigned char *pBmpBufNew;//�����µ�8λBMP��������Ҫ�Ŀռ䣬��λͼ���ݽ��ڴ�
							  //BMP����ʱ��λͼ�ļ�ͷ������ݻ����¼��㣬���ù�
	pBmpBufNew = new unsigned char[sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight];//�����洢�µ�λͼ

																								  //void *memcpy(void *destin, void *source, unsigned n);
																								  //����
																								  //	destin-- - ָ�����ڴ洢�������ݵ�Ŀ�����飬����ǿ��ת��Ϊ void* ָ�롣
																								  //	source-- ָ��Ҫ���Ƶ�����Դ������ǿ��ת��Ϊ void* ָ�롣
																								  //	n-- ------Ҫ�����Ƶ��ֽ�����

	memcpy(pBmpBufNew, (unsigned char *)lpSrcDib, sizeof(BITMAPINFOHEADER));//��Ϣͷ����

	pHead = (BITMAPINFOHEADER *)pBmpBufNew;//��pHeadָ��ָ����һ�������ڴ��λͼ��Ϣ����
										   //pHead = pBmpBufNew;//����
	pHead->biBitCount = 8;//�ı�λ��
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

	pColorTable = (RGBQUAD*)(pBmpBufNew + sizeof(BITMAPINFOHEADER));//��pColorTableָ��ָ����һ�������ڴ����ɫ����
																	//�Ҷ�ͼ������ɫ������ɫ�����Ϊ

	int R[4] = { 0,85,170,255 };
	int G[16] = { 0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255 };
	int B[4] = { 0,85,170,255 };


		//������ɫ������Ҫ�Ŀռ䣬����ɫ��ֵ
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
	//����ɨ��
	for (i = 0; i < lSrcHeight; i++)
	{
		//����ɨ��
		for (j = 0; j < lSrcWidth; j++)
		{
			// ָ��DIB��i�У���j�����ص�ָ��
			lpSrc = (unsigned char*)lpSrcStartBits + lLineBytes * (lSrcHeight - 1 - i) + j * 3;//��ԭRGB���ݲ��ֶ�ȡ���ݣ�lpSrc������
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
			// �任
			lpSrc = (unsigned char*)(pBmpBufNew + offset) + lineByteNew * (lSrcHeight - 1 - i) + j;//������Ҷȣ��浽�����ڴ��Ӧ���֡�
			*lpSrc =result;
		}
	}
	//����
	memcpy(lpSrcDib, pBmpBufNew, sizeof(BITMAPINFOHEADER) + 256 * 4 + lineByteNew * lSrcHeight);

	delete[]pBmpBufNew;



	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}

/*
void CMFCApplication1View::OnVtrans()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////
	CDlgVTrans dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	VTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnInversel()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgInverse_L dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	InverseL(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnLtrans()
{
	// TODO: �ڴ���������������

	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



	///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLTrans dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	int point = dlg.m_threshold;

	LTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}*/


void CMFCApplication1View::OnLineartranse()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											///////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgLinerPara dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}

	//int point = dlg.m_threshold;

	//LTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, point);



	LinerTrans(lpSrcStartBits, lSrcWidth, lSrcHeight,dlg.m_fA,dlg.m_fB );

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBitplane()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	CBitPlane dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	int bitNum = dlg.bitplane;

	BitPlane(lpSrcStartBits, lSrcWidth, lSrcHeight, lSrcLineBytes, bitNum);

	

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//void CMFCApplication1View::OnLogtranse()
//{
//
//
//	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
//	long	lSrcWidth;      //ͼ��Ŀ��
//	long	lSrcHeight;    //ͼ��ĸ߶�
//	int     lpSrcBitCount;       //ͼ���λ��
//	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
//	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
//	if (!lpSrcDib)
//	{
//		//::MessageBox(NULL, L"hello", L"welcome", MB_OK);
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
//	{
//		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
//		return;									//����
//	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
//
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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
//	//�����ĵ��޸ı�־
//	pDoc->SetModifiedFlag(true);
//	//������ͼ
//	pDoc->UpdateAllViews(NULL);
//	//�������
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//
//
//
//}


//void CMFCApplication1View::OnGammatrans()
//{
//	// TODO: �ڴ���������������
//	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
//	long	lSrcWidth;      //ͼ��Ŀ��
//	long	lSrcHeight;    //ͼ��ĸ߶�
//	int     lpSrcBitCount;       //ͼ���λ��
//	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
//	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("���ȴ�ͼƬ");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
//	{
//		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
//		return;									//����
//	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
//
//
//
//	//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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
//	//�����ĵ��޸ı�־
//	pDoc->SetModifiedFlag(true);
//	//������ͼ
//	pDoc->UpdateAllViews(NULL);
//	//�������
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//
//}


void CMFCApplication1View::OnThresholdtrans()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	CDlgThreshold dlg;
	
	

	if (dlg.DoModal() != IDOK)

	{
		return;
	}
	

	ThresholdTrans(lpSrcStartBits, lSrcWidth, lSrcHeight, dlg.m_threshold);



	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnBmpsmooth()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

	


}


void CMFCApplication1View::OnMidfilter()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////
	//��ʾ�Ի���ͨ���Ի�������ز���
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

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnOtherfilter()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


//void CMFCApplication1View::OnAddnoise()
//{
//	// TODO: �ڴ���������������
//	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
//	long	lSrcWidth;      //ͼ��Ŀ��
//	long	lSrcHeight;    //ͼ��ĸ߶�
//	int     lpSrcBitCount;       //ͼ���λ��
//	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
//	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("���ȴ�ͼƬ");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
//	{
//		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
//		return;									//����
//	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�
//
//
//
//											//////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
//	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
//	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
//	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
//	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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
//	//�����ĵ��޸ı�־
//	pDoc->SetModifiedFlag(true);
//	//������ͼ
//	pDoc->UpdateAllViews(NULL);
//	//�������
//	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
//
//}


void CMFCApplication1View::OnLaplacesharp()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////

	float T[15] = { 0,-1,0,0,0,
				   -1,5,-1,0,0,
				    0,-1,0 ,0,0,};
	CustomMadeTemplate(1, 1, 3, 3, T,1, lpSrcStartBits, lSrcWidth, lSrcHeight);
	
	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());


}


//void CMFCApplication1View::OnSobel()
//{
//	// TODO: �ڴ���������������
//	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
//											  ///////////////////////////////////////////////////////////////////////////	
//	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
//	long	lSrcWidth;      //ͼ��Ŀ��
//	long	lSrcHeight;    //ͼ��ĸ߶�
//	int     lpSrcBitCount;       //ͼ���λ��
//	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
//	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��
//
//	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
//	if (!lpSrcDib)
//	{
//		AfxMessageBox("���ȴ�ͼƬ");
//		return;
//	}
//
//
//
//	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
//	{
//		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
//		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
//		return;									//����
//	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



	//////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////

	Sobel(lpSrcStartBits, lSrcWidth, lSrcHeight);

	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}*/


void CMFCApplication1View::OnErosion()
{
	// TODO: �ڴ���������������

	
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnExpand()
{
	// TODO: �ڴ���������������
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnOpen()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//�����㣬�ȸ�ʴ������
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



	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnClose()
{
	// TODO: �ڴ���������������
	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////

	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//�����㣬�������ٸ�ʴ
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

	


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnInnerboundary()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
	////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char * lpSrcStartBitsBackUp = new unsigned char [lSrcLineBytes*lSrcHeight];
	memcpy(lpSrcStartBitsBackUp, lpSrcStartBits, lSrcLineBytes*lSrcHeight);
	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//�ڱ߽磬�ȸ�ʴ�������
	
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}


void CMFCApplication1View::OnOuterboundart()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////
	unsigned char * lpSrcStartBitsBackUp = new unsigned char[lSrcLineBytes*lSrcHeight];
	memcpy(lpSrcStartBitsBackUp, lpSrcStartBits, lSrcLineBytes*lSrcHeight);
	CDlgGetStructElem dlg;
	if (dlg.DoModal() != IDOK)
	{
		return;
	}
	//��߽磬�����ͣ������

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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBinaryshow()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////

	BinaryShow(lpSrcStartBits, lSrcWidth, lSrcHeight);


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnBinaryshow2()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
																				////////////////////////////////////////////////////////////////////////////////////////////

	BinaryFloyd(lpSrcStartBits, lSrcWidth, lSrcHeight);


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());
}


void CMFCApplication1View::OnDrawhist3()
{
	// TODO: �ڴ���������������

	CMFCApplication1Doc* pDoc = GetDocument();// ��ȡ�ĵ�
											  ///////////////////////////////////////////////////////////////////////////	
	long	lSrcLineBytes;		//ͼ��ÿ�е��ֽ���
	long	lSrcWidth;      //ͼ��Ŀ��
	long	lSrcHeight;    //ͼ��ĸ߶�
	int     lpSrcBitCount;       //ͼ���λ��
	LPSTR	lpSrcDib;		//ָ��Դͼ���ָ��	
	LPSTR	lpSrcStartBits;	//ָ��Դ���ص�ָ��

	lpSrcDib = (LPSTR) ::GlobalLock((HGLOBAL)pDoc->GetHObject());// ����DIB
	if (!lpSrcDib)
	{
		AfxMessageBox("���ȴ�ͼƬ");
		return;
	}



	if (pDoc->m_dib.GetColorNum(lpSrcDib) != 256)// �ж��Ƿ���24-bmpλͼ
	{
		AfxMessageBox("�Բ��𣬲���8λ��λͼ��");// ����
		::GlobalUnlock((HGLOBAL)pDoc->GetHObject());// �������
		return;									//����
	}										//�ж��Ƿ���8-bppλͼ,�����򷵻�



											//////////////////////////////////////////////////////////////////////////////////////////////////////////

	lpSrcStartBits = pDoc->m_dib.GetBits(lpSrcDib);// �ҵ�DIBͼ��������ʼλ��	
	lSrcWidth = pDoc->m_dib.GetWidth(lpSrcDib);	// ��ȡͼ��Ŀ��	
	lSrcHeight = pDoc->m_dib.GetHeight(lpSrcDib);	// ��ȡͼ��ĸ߶�	
	lpSrcBitCount = pDoc->m_dib.GetBitCount(lpSrcDib);      //��ȡͼ��λ��
	lSrcLineBytes = pDoc->m_dib.GetReqByteWidth(lSrcWidth * lpSrcBitCount);		// ����ͼ��ÿ�е��ֽ���
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


	//�����ĵ��޸ı�־
	pDoc->SetModifiedFlag(true);
	//������ͼ
	pDoc->UpdateAllViews(NULL);
	//�������
	::GlobalUnlock((HGLOBAL)pDoc->GetHObject());

}
