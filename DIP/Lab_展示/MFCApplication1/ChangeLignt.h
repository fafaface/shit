#pragma once


// CChangeLignt 对话框

class CChangeLignt : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeLignt)

public:
	CChangeLignt(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChangeLignt();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ChangeLignt };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 要调节的亮度值
	int Light;
	virtual BOOL OnInitDialog();
};
