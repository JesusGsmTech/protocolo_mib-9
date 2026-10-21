#if !defined(AFX_DLGMULTIBATCH_H__C8A7FC8D_897D_4583_84E1_18650758EF14__INCLUDED_)
#define AFX_DLGMULTIBATCH_H__C8A7FC8D_897D_4583_84E1_18650758EF14__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMultiBatch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiBatch dialog

class CDlgMultiBatch : public CDialog
{
// Construction
public:
	CDlgMultiBatch(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgMultiBatch)
	enum { IDD = IDD_DLG_MULTIBATCH };
	int		m_iDenom0;
	int		m_iDenom1;
	int		m_iDenom2;
	int		m_iDenom3;
	int		m_iDenom4;
	int		m_iDenom5;
	int		m_iDenom6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMultiBatch)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMultiBatch)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMULTIBATCH_H__C8A7FC8D_897D_4583_84E1_18650758EF14__INCLUDED_)
