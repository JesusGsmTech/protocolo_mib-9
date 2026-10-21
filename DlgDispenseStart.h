#if !defined(AFX_DLGDISPENSESTART_H__9B10AE54_D379_4ABC_A717_A9AA6E974BB9__INCLUDED_)
#define AFX_DLGDISPENSESTART_H__9B10AE54_D379_4ABC_A717_A9AA6E974BB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDispenseStart.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDispenseStart dialog

class CDlgDispenseStart : public CDialog
{
// Construction
public:
	CDlgDispenseStart(CWnd* pParent = NULL);   // standard constructor

	LONG m_lAmount;

// Dialog Data
	//{{AFX_DATA(CDlgDispenseStart)
	enum { IDD = IDD_DLG_DISPENSE_START };
	CString	m_Amount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDispenseStart)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDispenseStart)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDISPENSESTART_H__9B10AE54_D379_4ABC_A717_A9AA6E974BB9__INCLUDED_)
