#pragma once


// CDlgFilterSize �Ի���

class CDlgFilterSize : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFilterSize)

public:
	CDlgFilterSize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgFilterSize();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERSIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �˲�������
	int m_filterType;
	int m_width;
	int m_height;

	afx_msg void OnBnClickedRadio1();
};
