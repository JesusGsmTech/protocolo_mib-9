#pragma once


// CDlgSetupStateDataEx 대화 상자입니다.

class CDlgSetupStateDataEx : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetupStateDataEx)

public:
	CDlgSetupStateDataEx(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetupStateDataEx();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SETUP_STATE_DATA_EX };
	CComboBox	m_comboStaPocket;
	CComboBox	m_comboRejPocket;
	CComboBox	m_comboDenom;
	CComboBox	m_comboCurrency;
	CComboBox	m_comboCountMode;
	BOOL	m_bAddon;
	BOOL	m_bAuto;
	BOOL	m_bBatch;
	BOOL	m_bBeep;
	BOOL	m_bIROn;
	BOOL	m_bModeLock;
	BOOL	m_bMROn;
	BOOL	m_bUVOn;
	int		m_lBatchCnt;
	int		m_lIRLevel;
	int		m_lMRLevel;
	int		m_lUVLevel;

	BYTE m_baSelect[7];

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	void SetDenomCombo( int iCurrency );

	// Generated message map functions
	//{{AFX_MSG(CDlgSetupStateData2)
	afx_msg void OnSelchangeComboCurrencyCodeSetupEx();
	virtual void OnOK();
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
