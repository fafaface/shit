#pragma once


// CDrawHist 对话框

class CDrawHist : public CDialogEx
{
	DECLARE_DYNAMIC(CDrawHist)

public:
	CDrawHist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDrawHist();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DrawHist };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	// 灰度范围最小值	
	float num[256];
	// 灰度范围最小值
	int minHist;
	// 灰度范围最大值
	int maxHist;
	afx_msg void OnBnClickedRefresh();
};
