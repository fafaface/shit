#pragma once


// HistRange �Ի���

class HistRange : public CDialogEx
{
	DECLARE_DYNAMIC(HistRange)

public:
	HistRange(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~HistRange();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HistRange };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// �Ҷȷ�Χ��Сֵ
	int minHistRange;
	// �Ҷȷ�Χ���ֵ
	int histRangeMax;
	virtual BOOL OnInitDialog();
};
