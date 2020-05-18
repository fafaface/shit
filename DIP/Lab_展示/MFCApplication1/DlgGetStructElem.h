#pragma once


// CDlgGetStructElem 对话框

class CDlgGetStructElem : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgGetStructElem)

public:
	CDlgGetStructElem(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgGetStructElem();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRUCTUREELEM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_nMode;

	CButton	m_Control9;
	CButton	m_Control8;
	CButton	m_Control7;
	CButton	m_Control6;
	CButton	m_Control5;
	CButton	m_Control4;
	CButton	m_Control3;
	CButton	m_Control2;
	CButton	m_Control1;

	//-1表示选中，0表示不被选中
	int		m_nStructure1;
	int		m_nStructure2;
	int		m_nStructure3;
	int		m_nStructure4;
	int		m_nStructure5;
	int		m_nStructure6;
	int		m_nStructure7;
	int		m_nStructure8;
	int		m_nStructure9;
	afx_msg void OnBnClickedHori();
	afx_msg void OnBnClickedVert();
	afx_msg void OnBnClickedcustom();
	afx_msg void OnBnClickedStructure1();
	int check[10];
	afx_msg void OnBnClickedStructure2();
	afx_msg void OnBnClickedStructure3();
	afx_msg void OnBnClickedStructure4();
	afx_msg void OnBnClickedStructure5();
	afx_msg void OnBnClickedStructure6();
	afx_msg void OnBnClickedStructure7();
	afx_msg void OnBnClickedStructure8();
	afx_msg void OnBnClickedStructure9();
};
