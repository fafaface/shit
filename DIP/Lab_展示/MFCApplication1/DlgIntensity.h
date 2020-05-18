#pragma once


// CDlgIntensity �Ի���

class CDlgIntensity : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgIntensity)

public:

	// ��ǰ����϶�״̬��0��ʾδ�϶���1��ʾ�����϶����ޣ�2��ʾ�����϶����ޡ�
	int		m_iIsDraging;

	// ��Ӧ����¼��ľ�������
	CRect	m_MouseRect;

	// DIB�ĸ߶�
	LONG	m_lHeight;

	// DIB�Ŀ��
	LONG	m_lWidth;

	// ָ��ǰDIB���ص�ָ��
	char *	m_lpDIBBits;

	// �����Ҷ�ֵ�ļ���
	LONG	m_lCount[256];

	// ��ʾ�Ҷ����������
	int		m_iLowGray;

	// ��ʾ�Ҷ����������
	int		m_iUpGray;

	CDlgIntensity(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgIntensity();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_Intensity };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��



	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnKillfocusEditLowgray();
	afx_msg void OnEnKillfocusEditUpgray();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
};
