#pragma once


// CDlgAddNoise �Ի���

class CDlgAddNoise : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddNoise)

public:
	CDlgAddNoise(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAddNoise();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDNOISE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ��������
	int m_noistType;
	// ����ռ�����������ı���
	float m_noistPersent;
};
