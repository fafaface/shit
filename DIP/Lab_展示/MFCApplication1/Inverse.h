#pragma once


// Inverse �Ի���

class Inverse : public CDialogEx
{
	DECLARE_DYNAMIC(Inverse)

public:
	Inverse(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Inverse();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INVERSE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
