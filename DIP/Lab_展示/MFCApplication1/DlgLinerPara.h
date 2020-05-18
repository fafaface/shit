#pragma once


// CDlgLinerPara �Ի���

class CDlgLinerPara : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLinerPara)

public:
	CDlgLinerPara(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLinerPara();

	// ��ʶ�Ƿ��Ѿ�������Ƥ����
	BOOL	m_bDrawed;

	// ��������������ʱ��λ��
	CPoint	m_p1;

	// ��������϶�ʱ��λ��
	CPoint	m_p2;

	// ��ǰ����϶�״̬��TRUE��ʾ�����϶���
	BOOL	m_bIsDraging;

	// ��Ӧ����¼��ľ�������
	CRect	m_MouseRect;


// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_LinerPara };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_fA;
	float m_fB;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnKillfocusEditA();
	afx_msg void OnEnKillfocusEditB();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
};
