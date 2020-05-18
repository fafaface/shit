#pragma once


// CDlgHistogram 对话框

class CDlgHistogram : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHistogram)

public:
	CDlgHistogram(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHistogram();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COOR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 灰度值的最小值
	int m_iLowGray;
	// 灰度值的最大值
	int m_iUpGray;
	long m_lCount[256];
	afx_msg void OnPaint();
};
