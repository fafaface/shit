#pragma once


// CDlgSmooth �Ի���

class CDlgSmooth : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgSmooth)

public:
	CDlgSmooth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgSmooth();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BMPSMOOTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:

	// ģ��Ԫ������ָ��
	float * m_fpArray;
	// ģ������
	int m_intType;

	// ģ��߶�
	int m_iTempH;
	// ģ����
	int m_iTempW;
	// ģ������Ԫ��X����
	int m_iTempMX;
	// ģ������Ԫ��Y����
	int m_iTempMY;
	// ģ��ϵ��
	float m_fTempC;

	void UpdateEdit();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnEnKillfocusEditTemph();
	afx_msg void OnEnKillfocusEditTempw();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditV24();
};
