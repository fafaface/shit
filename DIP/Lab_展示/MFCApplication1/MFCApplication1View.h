
// MFCApplication1View.h : CMFCApplication1View ��Ľӿ�
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // �������л�����
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

// ����
public:
	CMFCApplication1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDispimginfo();
	afx_msg void OnChangelight();
	afx_msg void OnChange256colortogray();
	afx_msg void OnGraytobinary();
	afx_msg void OnDrawhist();
	afx_msg void OnDrawhist2();
	afx_msg void On248grey();
	afx_msg void OnEditUndo();
	afx_msg void OnPointinvert();
	//afx_msg void OnInversev();
	afx_msg void On24colorto8color();
	//afx_msg void OnVtrans();
//	afx_msg void OnInversel();
	//afx_msg void OnLtrans();
	afx_msg void OnLineartranse();
	afx_msg void OnBitplane();
	//afx_msg void OnLogtranse();
//	afx_msg void OnGammatrans();
	afx_msg void OnThresholdtrans();
	afx_msg void OnBmpsmooth();
	afx_msg void OnMidfilter();
	afx_msg void OnOtherfilter();
	//afx_msg void OnAddnoise();
	afx_msg void OnLaplacesharp();
	//afx_msg void OnSobel();
	afx_msg void OnErosion();
	afx_msg void OnExpand();
	afx_msg void OnOpen();
	afx_msg void OnClose();
	afx_msg void OnInnerboundary();
	afx_msg void OnOuterboundart();
	afx_msg void OnBinaryshow();
	afx_msg void OnBinaryshow2();
	afx_msg void OnDrawhist3();
};

#ifndef _DEBUG  // MFCApplication1View.cpp �еĵ��԰汾
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

