



#pragma once


// CDlgMidFilter 对话框

class CDlgMidFilter : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMidFilter)

public:
	CDlgMidFilter(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMidFilter();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DLG_MidianFilter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 滤波器类型
	int m_iFilterType;
	// 滤波器高度
	int m_iFilterH;
	// 滤波器宽度
	int m_iFilterW;
	// 滤波器中心元素X坐标
	int m_iFilterMX;
	// 滤波器中心元素Y坐标
	int m_iFilterMY;
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
};
