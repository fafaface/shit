
// MFCApplication1View.h : CMFCApplication1View 类的接口
//

#pragma once


class CMFCApplication1View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication1View();
	DECLARE_DYNCREATE(CMFCApplication1View)

// 特性
public:
	CMFCApplication1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCApplication1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // MFCApplication1View.cpp 中的调试版本
inline CMFCApplication1Doc* CMFCApplication1View::GetDocument() const
   { return reinterpret_cast<CMFCApplication1Doc*>(m_pDocument); }
#endif

