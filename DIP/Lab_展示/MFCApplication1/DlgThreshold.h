#pragma once
#include "atltypes.h"


// CDlgThreshold �Ի���

class CDlgThreshold : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgThreshold)

public:
	CDlgThreshold(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgThreshold();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THRESHOLD };
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
