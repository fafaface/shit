#pragma once


// HistRange 对话框

class HistRange : public CDialogEx
{
	DECLARE_DYNAMIC(HistRange)

public:
	HistRange(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HistRange();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HistRange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 灰度范围最小值
	int minHistRange;
	// 灰度范围最大值
	int histRangeMax;
	virtual BOOL OnInitDialog();
};
