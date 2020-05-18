#pragma once


// Inverse 对话框

class Inverse : public CDialogEx
{
	DECLARE_DYNAMIC(Inverse)

public:
	Inverse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Inverse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INVERSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
