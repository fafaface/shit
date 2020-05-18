// DlgLTrans.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgLTrans.h"
#include "afxdialogex.h"

#include"resource.h"


// CDlgLTrans �Ի���

IMPLEMENT_DYNAMIC(CDlgLTrans, CDialogEx)

CDlgLTrans::CDlgLTrans(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LTRANS, pParent)
	, m_bIsDrawing(false)
	, m_threshold(128)
{

}

CDlgLTrans::~CDlgLTrans()
{
}

void CDlgLTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_threshold);
}


BEGIN_MESSAGE_MAP(CDlgLTrans, CDialogEx)
	ON_WM_PAINT()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CDlgLTrans ��Ϣ�������


BOOL CDlgLTrans::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	//��ȡ����ͼ�εı�ǩ
	CWnd* pWnd = GetDlgItem(IDC_LTRANS);
	//�����������¼�����Ч����
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	//���ý�������¼�����Ч����
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	//��ʼ���϶�״̬
	m_bIsDrawing = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLTrans::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
					   //��ȡ����������ı���
	CWnd * pWnd = GetDlgItem(IDC_LTRANS);
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
	pCenterTop.x = 10 + m_threshold;//128;
	pCenterTop.y = 25;

	pCenterBottom.x = 10 + m_threshold;//128;
	pCenterBottom.y = 280;
	pDC->MoveTo(pCenterTop);
	pDC->LineTo(pCenterBottom);

	//���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);
	//�������任�ߣ�û�м���б��,û�н���
	pLeft.x = 10;
	pLeft.y = 25;
	//pDC->MoveTo(10,280);
	pDC->MoveTo(pLeft);
	pCenterTop.x = 10 + m_threshold;//128;
	pCenterTop.y = 280;
	//pDC->LineTo(138,25);
	pDC->LineTo(pCenterTop);
	pRight.x = 265;
	pRight.y = 280;
	//pDC->LineTo(265,280);
	pDC->LineTo(pRight);
}


void CDlgLTrans::OnKillFocus(CWnd* pNewWnd)
{
	CDialogEx::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������

	//�����û�����
	UpdateData(TRUE);
	//�ػ�
	InvalidateRect(m_MouseRect, TRUE);
}


void CDlgLTrans::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//  ���û�������������ʼ�϶�
	//�ж��Ƿ�����Ч����
	if (m_MouseRect.PtInRect(point))
	{
		if (point.x == (m_MouseRect.left + m_threshold))
		{
			//�����϶�״̬
			m_bIsDrawing = TRUE;
			//���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgLTrans::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//  ���û��ͷ�������ֹͣ�϶�
	if (m_bIsDrawing)
	{
		//���������϶�״̬
		m_bIsDrawing = FALSE;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgLTrans::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//  �жϵ�ǰ����Ƿ��ڻ�������
	if (m_MouseRect.PtInRect(point))
	{
		//�ж��Ƿ����϶�
		if (m_bIsDrawing)
		{
			//������ֵ
			m_threshold = (BYTE)(point.x - m_MouseRect.left);
			//���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
			//����
			UpdateData(FALSE);
			//�ػ�
			InvalidateRect(m_MouseRect, TRUE);
		}
		else if (point.x == (m_MouseRect.left + m_threshold))
		{
			//���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_SIZEWE));
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
