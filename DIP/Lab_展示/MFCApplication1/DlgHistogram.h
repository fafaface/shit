#pragma once


// CDlgHistogram �Ի���

class CDlgHistogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHistogram();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �Ҷ�ֵ����Сֵ
	int m_iLowGray;
	// �Ҷ�ֵ�����ֵ
	int m_iUpGray;
	long m_lCount[256];
	afx_msg void OnPaint();
};
