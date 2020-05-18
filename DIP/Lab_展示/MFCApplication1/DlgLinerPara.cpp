// DlgLinerPara.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "DlgLinerPara.h"
#include "afxdialogex.h"


// CDlgLinerPara �Ի���

IMPLEMENT_DYNAMIC(CDlgLinerPara, CDialogEx)

CDlgLinerPara::CDlgLinerPara(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DLG_LinerPara, pParent)
	, m_fA(0)
	, m_fB(0)
{

}

CDlgLinerPara::~CDlgLinerPara()
{
}

void CDlgLinerPara::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_A, m_fA);
	DDX_Text(pDX, IDC_EDIT_B, m_fB);
}


BEGIN_MESSAGE_MAP(CDlgLinerPara, CDialogEx)
	ON_EN_KILLFOCUS(IDC_EDIT_A, &CDlgLinerPara::OnEnKillfocusEditA)
	ON_EN_KILLFOCUS(IDC_EDIT_B, &CDlgLinerPara::OnEnKillfocusEditB)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgLinerPara ��Ϣ�������


BOOL CDlgLinerPara::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ��ȡ���Ʋ������ߵı�ǩ
	CWnd* pWnd = GetDlgItem(IDC_LINEARTRANSE);
	// �����������¼�����Ч����
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);

	CRect rect;
	GetClientRect(rect);
	ClientToScreen(&rect);

	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;

	// ���ý�������¼�����Ч����
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;

	// ��ʼ���϶�״̬
	m_bIsDraging = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgLinerPara::OnEnKillfocusEditA()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����û�����
	UpdateData(TRUE);

	// �ػ�
	InvalidateRect(m_MouseRect, TRUE);

}


void CDlgLinerPara::OnEnKillfocusEditB()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����û�����
	UpdateData(TRUE);

	// �ػ�
	InvalidateRect(m_MouseRect, TRUE);

}


void CDlgLinerPara::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// ���û�������������ʼ�϶�
	if (m_MouseRect.PtInRect(point))
	{
		// ���浱ǰ���λ��
		m_p1 = point;

		// ת������ϵ
		m_p1.x = m_p1.x - m_MouseRect.left + 10;
		m_p1.y = m_p1.y - m_MouseRect.top + 25;

		// �����϶�״̬
		m_bIsDraging = TRUE;

		// ����m_bDrawedΪFALSE
		m_bDrawed = FALSE;

		// ���Ĺ��
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));

		// ��ʼ��������¼�����֤������ƶ���������ʱҲ���Խ��յ�����ͷ��¼���
		SetCapture();
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CDlgLinerPara::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// �жϵ�ǰ����Ƿ��ڻ�������
	if (m_MouseRect.PtInRect(point))
	{
		// ���Ĺ��
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));

		// �ж��Ƿ������϶�
		if (m_bIsDraging)
		{
			// ��ȡ��ͼ�ı�ǩ
			CWnd* pWnd = GetDlgItem(IDC_LINEARTRANSE);

			// ��ȡ�豸������
			CDC* pDC = pWnd->GetDC();

			// ���û��Ʒ�ʽΪ���ģʽ
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);

			// �����µĻ���
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));

			// ѡ���»���
			CGdiObject* pOldPen = pDC->SelectObject(pPen);

			// �ж��Ƿ��Ѿ�������Ƥ����
			if (m_bDrawed)
			{
				// ��ȥ��ǰ����Ƥ����
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}

			// ���浱ǰ������
			m_p2 = point;

			// ת������ϵ
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;

			// ����һ������Ƥ����
			pDC->MoveTo(m_p1);
			pDC->LineTo(m_p2);

			// ����m_bDrawedΪTRUE
			m_bDrawed = TRUE;

			// ѡ����ǰ�Ļ���
			pDC->SelectObject(pOldPen);

			// �ָ�����ǰ�Ļ���ģʽ
			pDC->SetROP2(nOldDrawMode);

			delete pPen;
			ReleaseDC(pDC);
		}
	}
	else
	{
		// �ж��Ƿ������϶�
		if (m_bIsDraging)
		{
			// ���Ĺ��
			::SetCursor(::LoadCursor(NULL, IDC_NO));
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CDlgLinerPara::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	// ���û��ͷ�������ֹͣ�϶�
	if (m_bIsDraging)
	{
		// �жϵ�ǰ����Ƿ��ڻ�������
		if (m_MouseRect.PtInRect(point))
		{
			// ���浱ǰ���λ��
			m_p2 = point;

			// ת������ϵ
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;

			if ((m_p1 != m_p2) && (m_p1.x != m_p2.x))
			{
				// ת������ϵ
				m_p1.x = m_p1.x - 10;
				m_p1.y = 280 - m_p1.y;
				m_p2.x = m_p2.x - 10;
				m_p2.y = 280 - m_p2.y;

				// ����б�ʺͽؾ�
				m_fA = (float)(m_p2.y - m_p1.y) / (m_p2.x - m_p1.x);
				m_fB = m_p1.y - m_fA * m_p1.x;

				// ����䶯
				UpdateData(FALSE);
			}

			// �ػ�
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			// �û��ڻ���������ſ�������

			// ��ȡ��ͼ�ı�ǩ
			CWnd* pWnd = GetDlgItem(IDC_COORD);

			// ��ȡ�豸������
			CDC* pDC = pWnd->GetDC();

			// ���û��Ʒ�ʽΪ���ģʽ
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);

			// �����µĻ���
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT, 1, RGB(0, 0, 0));

			// ѡ���»���
			CGdiObject* pOldPen = pDC->SelectObject(pPen);

			// �ж��Ƿ��Ѿ�������Ƥ����
			if (m_bDrawed)
			{
				// ��ȥ��ǰ����Ƥ����
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}

			// ѡ����ǰ�Ļ���
			pDC->SelectObject(pOldPen);

			// �ָ�����ǰ�Ļ���ģʽ
			pDC->SetROP2(nOldDrawMode);

			delete pPen;
			ReleaseDC(pDC);

		}

		// ���������¼��ĸ���
		::ReleaseCapture();

		// �����϶�״̬
		m_bIsDraging = FALSE;
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CDlgLinerPara::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

					   // �ַ���
	CString str;

	// ֱ�ߺ������������������
	int x1, y1, x2, y2;


	// ��ȡ����������ı���
	CWnd* pWnd = GetDlgItem(IDC_LINEARTRANSE);

	// ָ��
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();

	pDC->Rectangle(0, 0, 330, 300);

	// �������ʶ���
	CPen* pPenRed = new CPen;

	// ��ɫ����
	pPenRed->CreatePen(PS_SOLID, 2, RGB(255, 0, 0));

	// �������ʶ���
	CPen* pPenBlue = new CPen;

	// ��ɫ����
	pPenBlue->CreatePen(PS_SOLID, 2, RGB(0, 0, 255));

	// ѡ�е�ǰ��ɫ���ʣ���������ǰ�Ļ���
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);

	// ����������
	pDC->MoveTo(10, 10);

	// ��ֱ��
	pDC->LineTo(10, 280);

	// ˮƽ��
	pDC->LineTo(320, 280);

	// д����
	str.Format("0");
	pDC->TextOut(10, 281, str);

	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);

	// ����X���ͷ
	pDC->LineTo(315, 275);
	pDC->MoveTo(320, 280);
	pDC->LineTo(315, 285);

	// ����Y���ͷ
	pDC->MoveTo(10, 10);
	pDC->LineTo(5, 15);
	pDC->MoveTo(10, 10);
	pDC->LineTo(15, 15);

	// ���ĳ���ɫ����
	pDC->SelectObject(pPenBlue);

	// ����ֱ�ߺ������������������
	if (m_fA >= 0)
	{
		if (((m_fA * 255 + m_fB) >= 0) && (m_fB < 255))
		{
			// ����(x1, y1)����
			if (m_fB < 0)
			{
				x1 = (int)(-m_fB / m_fA + 0.5);
				y1 = 0;
			}
			else
			{
				x1 = 0;
				y1 = (int)(m_fB + 0.5);
			}

			// ����(x2, y2)����
			if ((m_fA * 255 + m_fB) > 255)
			{
				x2 = (int)((255 - m_fB) / m_fA + 0.5);
				y2 = 255;
			}
			else
			{
				x2 = 255;
				y2 = (int)(255 * m_fA + m_fB + 0.5);
			}
		}
		else if (((m_fA * 255 + m_fB) < 0))
		{
			// ת������������ֵ��С��0��ֱ������Ϊ0
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			// ת������������ֵ������255��ֱ������Ϊ255
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}
	else  // б��С��0
	{
		if ((m_fB > 0) && (255 * m_fA + m_fB < 255))
		{
			// ����(x1, y1)����
			if (m_fB > 255)
			{
				x1 = (int)((255 - m_fB) / m_fA + 0.5);
				y1 = 255;
			}
			else
			{
				x1 = 0;
				y1 = (int)(m_fB + 0.5);
			}

			// ����(x2, y2)����
			if ((m_fA * 255 + m_fB) < 0)
			{
				x2 = (int)(-m_fB / m_fA + 0.5);
				y2 = 0;
			}
			else
			{
				x2 = 255;
				y2 = (int)(255 * m_fA + m_fB + 0.5);
			}
		}
		else if (m_fB <= 0)
		{
			// ת������������ֵ��С��0��ֱ������Ϊ0
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			// ת������������ֵ������255��ֱ������Ϊ255
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}

	// ��������ֵ
	str.Format("(%d, %d)", x1, y1);
	pDC->TextOut(x1 + 10, 280 - y1 + 1, str);
	str.Format("(%d, %d)", x2, y2);
	pDC->TextOut(x2 + 10, 280 - y2 + 1, str);

	// �����û�ָ�������Ա任ֱ�ߣ�ע��ת������ϵ��
	pDC->MoveTo(x1 + 10, 280 - y1);
	pDC->LineTo(x2 + 10, 280 - y2);

	// �ָ���ǰ�Ļ���
	pDC->SelectObject(pOldPen);

	// ���Ʊ�Ե
	pDC->MoveTo(10, 25);
	pDC->LineTo(265, 25);
	pDC->LineTo(265, 280);

	// ɾ���µĻ���
	delete pPenRed;
	delete pPenBlue;
}
