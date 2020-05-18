#pragma once


// CDlgLogTranse 对话框

class CDlgLogTranse : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLogTranse)

public:
	CDlgLogTranse(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLogTranse();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGTRANSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	float m_c;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedRefresh();
};
