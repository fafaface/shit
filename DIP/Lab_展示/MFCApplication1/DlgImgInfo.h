#pragma once


// CDlgImgInfo �Ի���

class CDlgImgInfo : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImgInfo)

public:
	CDlgImgInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgImgInfo();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DlgImgInfo };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	long m_Height;
	long m_Width;
	long m_bitCount;
	virtual BOOL OnInitDialog();
};
