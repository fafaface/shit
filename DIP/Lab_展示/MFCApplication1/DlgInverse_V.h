#pragma once
#include "atltypes.h"


// CDlgInverse_V 对话框

class CDlgInverse_V : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInverse_V)

public:
	CDlgInverse_V(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgInverse_V();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_Inverse_V };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 那个变化的点
	int m_threshold;
	// //标识是否拖动
	bool m_bIsDrawing;
	// //响应鼠标的区域
	CRect m_MouseRect;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
