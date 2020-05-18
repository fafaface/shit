#pragma once
#include "atltypes.h"


// CDlgInverse_L �Ի���

class CDlgInverse_L : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInverse_L)

public:
	CDlgInverse_L(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInverse_L();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INVERSEL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
