// DlgHistogram.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgHistogram.h"
#include "afxdialogex.h"


// CDlgHistogram �Ի���

IMPLEMENT_DYNAMIC(CDlgHistogram, CDialogEx)

CDlgHistogram::CDlgHistogram(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COOR, pParent)
	, m_iLowGray(0)
	, m_iUpGray(0)
{

}

CDlgHistogram::~CDlgHistogram()
{
}

void CDlgHistogram::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgHistogram, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgHistogram ��Ϣ�������


void CDlgHistogram::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

					   //��ʾֱ��ͼ
					   // �豸������

					   
	CString str;// �ַ���

	// ѭ������
	LONG i;

	// ������
	LONG lMaxCount = 0;

	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_COOR);//���

	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);


	// �������ʶ���
	CPen* pPenRed = new CPen;

	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

	// �������ʶ���
	CPen* pPenBlue = new CPen;

	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID, 1, RGB(0, 0, 255));

	// �������ʶ���
	CPen* pPenGreen = new CPen;

	// ��ɫ����
	pPenGreen->CreatePen(PS_DOT, 1, RGB(0, 255, 0));

	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// ����������
	pDC->MoveTo(10, 10);

	// ��ֱ��
	pDC->LineTo(10, 280);

	// ˮƽ��
	pDC->LineTo(320, 280);

	// дX��̶�ֵ
	str.Format("0");
	pDC->TextOut(10, 283, str);
	str.Format("50");
	pDC->TextOut(60, 283, str);
	str.Format("100");
	pDC->TextOut(110, 283, str);
	str.Format("150");
	pDC->TextOut(160, 283, str);
	str.Format("200");
	pDC->TextOut(210, 283, str);
	str.Format("255");
	pDC->TextOut(265, 283, str);
	// ����X��̶�
	for (i = 0; i < 256; i += 5)
	{
		if ((i & 1) == 0)
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 284);
		}
		else
		{
			// 10�ı���
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 282);
		}
	}
	// ����������ֵ
	for (i = m_iLowGray; i <= m_iUpGray; i++)
	{
		// �ж��Ƿ���ڵ�ǰ���ֵ
		if (m_lCount[i] > lMaxCount)
		{
			// �������ֵ
			lMaxCount = m_lCount[i];
		}
	}

	// ���������ֵ
	pDC->MoveTo(10, 25);
	pDC->LineTo(14, 25);
	str.Format("%d", lMaxCount);
	pDC->TextOut(11, 26, str);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenGreen);

	// ���ƴ���������
	pDC->MoveTo(m_iLowGray + 10, 25);
	pDC->LineTo(m_iLowGray + 10, 280);

	pDC->MoveTo(m_iUpGray + 10, 25);
	pDC->LineTo(m_iUpGray + 10, 280);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);

	// �ж��Ƿ��м���
	if (lMaxCount > 0)
	{
		// ����ֱ��ͼ
		for (i = m_iLowGray; i <= m_iUpGray; i++)
		{
			pDC->MoveTo(i + 10, 280);
			pDC->LineTo(i + 10, 281 - (int)(m_lCount[i] * 256 / lMaxCount));
		}
	}

	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);

	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
}
