#pragma once


// CDlgFilterSize 对话框

class CDlgFilterSize : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgFilterSize)

public:
	CDlgFilterSize(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgFilterSize();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTERSIZE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 滤波器类型
	int m_filterType;
	int m_width;
	int m_height;

	afx_msg void OnBnClickedRadio1();
};
