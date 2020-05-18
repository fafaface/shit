#pragma once


// CDlgAddNoise 对话框

class CDlgAddNoise : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddNoise)

public:
	CDlgAddNoise(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAddNoise();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDNOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 噪声种类
	int m_noistType;
	// 噪声占总像素数量的比例
	float m_noistPersent;
};
