
// MFCApplication1Doc.h : CMFCApplication1Doc ��Ľӿ�
//


#pragma once

#include "Dib.h"
extern CDib m_dib;

class CMFCApplication1Doc : public CDocument
{
protected: // �������л�����
	CMFCApplication1Doc();
	DECLARE_DYNCREATE(CMFCApplication1Doc)

// ����
public:
	CDib m_dib;

// ����
public:
	HGLOBAL GetHObject() const	//��ȡDib����ľ��
	{
		return m_hDIB;
	}
	CPalette* GetDocPal() const	//��ȡ��ɫ��ָ��
	{
		return m_palDIB;
	}
	CSize GetDocDimension() const//��ȡ��ɫ���С
	{
		return m_sizeDoc;
	}
	void UpdateObject(HGLOBAL hDIB);//����dib����
// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	void SetDib();				//��ʼ��dib����
	virtual ~CMFCApplication1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HGLOBAL m_hDIB;
	CPalette*  m_palDIB;
	CSize m_sizeDoc;
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
