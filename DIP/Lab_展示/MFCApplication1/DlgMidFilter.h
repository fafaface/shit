



#pragma once


// CDlgMidFilter �Ի���

class CDlgMidFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMidFilter)

public:
	CDlgMidFilter(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMidFilter();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MidianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �˲�������
	int m_iFilterType;
	// �˲����߶�
	int m_iFilterH;
	// �˲������
	int m_iFilterW;
	// �˲�������Ԫ��X����
	int m_iFilterMX;
	// �˲�������Ԫ��Y����
	int m_iFilterMY;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
