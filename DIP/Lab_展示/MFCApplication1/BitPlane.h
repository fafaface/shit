#pragma once


// CBitPlane �Ի���

class CBitPlane : public CDialogEx
{
	DECLARE_DYNAMIC(CBitPlane)

public:
	CBitPlane(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CBitPlane();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BITPLANE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int bitplane;
	virtual BOOL OnInitDialog();
};
