#pragma once


// CDlgLogTranse �Ի���

class CDlgLogTranse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogTranse)

public:
	CDlgLogTranse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLogTranse();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGTRANSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	float m_c;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRefresh();
};
