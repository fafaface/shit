#pragma once
#include "atltypes.h"


// CDlgInverse_V �Ի���

class CDlgInverse_V : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgInverse_V)

public:
	CDlgInverse_V(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInverse_V();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dlg_Inverse_V };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �Ǹ��仯�ĵ�
	int m_threshold;
	// //��ʶ�Ƿ��϶�
	bool m_bIsDrawing;
	// //��Ӧ��������
	CRect m_MouseRect;
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};
