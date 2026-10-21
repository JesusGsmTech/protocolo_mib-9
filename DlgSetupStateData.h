#if !defined(AFX_DLGSETUPSTATEDATA_H__97C765C8_685F_4F44_BA00_95483DAEAC30__INCLUDED_)
#define AFX_DLGSETUPSTATEDATA_H__97C765C8_685F_4F44_BA00_95483DAEAC30__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSetupStateData.h : header file
//

class CDlgSetupStateData : public CDialog
{
// Construction
public:
	CDlgSetupStateData(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSetupStateData)
	enum { IDD = IDD_DLG_SETUP_STATE_DATA };
	CComboBox	m_comboStackPocket;
	CComboBox	m_comboRejectPocket;
	CComboBox	m_comboCurrencyCode;
	CComboBox	m_comboCountMode;
	CComboBox	m_comboDenom;
	BOOL	m_bBeepEnable;
	BOOL	m_bAuto;
	BOOL	m_bAddOn;
	BOOL	m_bUVOn;
	BOOL	m_bMROn;
	BOOL	m_bModeLockOn;
	BOOL	m_bBatchOn;
	long	m_lBatchCountNum;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSetupStateData)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void SetDenomCombo( int iCurrency );

	// Generated message map functions
	//{{AFX_MSG(CDlgSetupStateData)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeComboCurrencyCode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	BYTE m_baSelect[7];
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETUPSTATEDATA_H__97C765C8_685F_4F44_BA00_95483DAEAC30__INCLUDED_)
