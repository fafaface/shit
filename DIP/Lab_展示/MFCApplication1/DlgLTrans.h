#pragma once
#include "atltypes.h"


// CDlgLTrans 对话框

class CDlgLTrans : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLTrans)

public:
	CDlgLTrans(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLTrans();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRect m_MouseRect;
	bool m_bIsDrawing;
	int m_threshold;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
