#pragma once


// CBitPlane 对话框

class CBitPlane : public CDialogEx
{
	DECLARE_DYNAMIC(CBitPlane)

public:
	CBitPlane(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CBitPlane();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITPLANE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int bitplane;
	virtual BOOL OnInitDialog();
};
