#pragma once


// CChangeLignt �Ի���

class CChangeLignt : public CDialogEx
{
	DECLARE_DYNAMIC(CChangeLignt)

public:
	CChangeLignt(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChangeLignt();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ChangeLignt };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// Ҫ���ڵ�����ֵ
	int Light;
	virtual BOOL OnInitDialog();
};
