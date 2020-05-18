#pragma once
#include "atltypes.h"


// CDlgVTrans �Ի���

class CDlgVTrans : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgVTrans)

public:
	CDlgVTrans(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgVTrans();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VTrans };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_threshold;
	bool m_bIsDrawing;
	CRect m_MouseRect;
	afx_msg void OnInversev();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
