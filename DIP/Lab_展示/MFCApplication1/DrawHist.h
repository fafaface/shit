#pragma once


// CDrawHist �Ի���

class CDrawHist : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawHist)

public:
	CDrawHist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDrawHist();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DrawHist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	// �Ҷȷ�Χ��Сֵ	
	float num[256];
	// �Ҷȷ�Χ��Сֵ
	int minHist;
	// �Ҷȷ�Χ���ֵ
	int maxHist;
	afx_msg void OnBnClickedRefresh();
};
