#if !defined(AFX_DLGSETUPSTATEDATA2_H__0249CB38_E28F_4427_A8B8_A262AE80C8A3__INCLUDED_)
#define AFX_DLGSETUPSTATEDATA2_H__0249CB38_E28F_4427_A8B8_A262AE80C8A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetupStateData2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData2 dialog

class CDlgSetupStateData2 : public CDialog
{
// Construction
public:
	CDlgSetupStateData2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetupStateData2)
	enum { IDD = IDD_DLG_SETUP_STATE_DATA2 };
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
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetupStateData2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetDenomCombo( int iCurrency );

	// Generated message map functions
	//{{AFX_MSG(CDlgSetupStateData2)
	afx_msg void OnSelchangeComboCurrencyCodeSetup2();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BYTE m_baSelect[7];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETUPSTATEDATA2_H__0249CB38_E28F_4427_A8B8_A262AE80C8A3__INCLUDED_)
