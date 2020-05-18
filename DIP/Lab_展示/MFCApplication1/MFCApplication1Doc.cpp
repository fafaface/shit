
// MFCApplication1Doc.cpp : CMFCApplication1Doc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCApplication1.h"
#endif

#include "MFCApplication1Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication1Doc

IMPLEMENT_DYNCREATE(CMFCApplication1Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication1Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication1Doc ����/����

CMFCApplication1Doc::CMFCApplication1Doc()
{
	// TODO: �ڴ����һ���Թ������
	m_hDIB = NULL;// ��ʼ������
	m_palDIB = NULL;
	m_sizeDoc = CSize(1, 1);
}

CMFCApplication1Doc::~CMFCApplication1Doc()
{
	if (m_hDIB != NULL)// �ж��Ƿ���DIB����
	{
		::GlobalFree((HGLOBAL)m_hDIB);
	}


	if (m_palDIB != NULL)// �жϵ�ɫ���Ƿ����
	{
		delete m_palDIB;
	}
}

BOOL CMFCApplication1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMFCApplication1Doc ���л�

void CMFCApplication1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CMFCApplication1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CMFCApplication1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CMFCApplication1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication1Doc ���

#ifdef _DEBUG
void CMFCApplication1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication1Doc ����


BOOL CMFCApplication1Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  �ڴ������ר�õĴ�������
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeRead |
		CFile::shareDenyWrite))// ���ļ�
	{
		return FALSE;// ����FALSE
	}
	DeleteContents();
	m_hDIB = m_dib.LoadFile(file);
	if (m_hDIB == NULL)// ����LoadFile()��ȡͼ��
	{
		return FALSE;
	}
	SetDib();// ��ʼ��DIB
	if (m_hDIB == NULL)	// �ж϶�ȡ�ļ��Ƿ�ɹ�
	{
		//AfxMessageBox(L"��ȡͼ��ʱ����");// ��ʾ����				
		return FALSE;// ����FALSE
	}
	SetPathName(lpszPathName);// �����ļ�����		
	SetModifiedFlag(FALSE);// ��ʼ���޸ı��ΪFALSE		
	return TRUE;// ����TRUE
}


BOOL CMFCApplication1Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: �ڴ����ר�ô����/����û���
	CFile file;
	if (!file.Open(lpszPathName, CFile::modeCreate |// ���ļ�
		CFile::modeReadWrite | CFile::shareExclusive))
	{
		return FALSE;// ����FALSE
	}
	BOOL bSuccess = FALSE;
	bSuccess = m_dib.SaveFile(m_hDIB, file);	// ����ͼ��	
	file.Close();// �ر��ļ�	
	SetModifiedFlag(FALSE);// ��������ΪFALSE
	if (!bSuccess)
	{
		//AfxMessageBox(L"����BMPͼ��ʱ����");// ��ʾ����
	}
	return bSuccess;
	//return CDocument::OnSaveDocument(lpszPathName);
}


void CMFCApplication1Doc::SetDib()
{
	LPSTR lpdib = (LPSTR) ::GlobalLock((HGLOBAL)m_hDIB);

	if (m_dib.GetWidth(lpdib) > INT_MAX || m_dib.GetHeight(lpdib) > INT_MAX)// �ж�ͼ���Ƿ����
	{
		::GlobalUnlock((HGLOBAL)m_hDIB);
		::GlobalFree((HGLOBAL)m_hDIB);	// �ͷ�DIB����			
		m_hDIB = NULL;// ����DIBΪ��		
		//AfxMessageBox(L"��ʼ��ʧ��");
		return;
	}
	m_sizeDoc = CSize((int)m_dib.GetWidth(lpdib), (int)m_dib.GetHeight(lpdib));// �����ĵ���С	
	::GlobalUnlock((HGLOBAL)m_hDIB);
	m_palDIB = new CPalette;// �����µ�ɫ��		
	if (m_palDIB == NULL)// �ж��Ƿ񴴽��ɹ�
	{
		::GlobalFree((HGLOBAL)m_hDIB);	// ʧ��		
		m_hDIB = NULL;// ����DIB����Ϊ��
		return;
	}
	// ����CreateDIBPalette��������ɫ��
	if (m_dib.ConstructPalette(m_hDIB, m_palDIB) == NULL)
	{
		delete m_palDIB;// ɾ��				
		m_palDIB = NULL;// ����Ϊ��	
		return;// ���ؿ�
	}
}



void CMFCApplication1Doc::UpdateObject(HGLOBAL hDIB)
{
	if (m_hDIB != NULL)               // �ж�DIB�Ƿ�Ϊ��
	{
		::GlobalFree((HGLOBAL)m_hDIB);// �ǿգ������
	}
	m_hDIB = hDIB;                     // �滻���µ�DIB����	
}