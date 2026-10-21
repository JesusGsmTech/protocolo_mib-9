#if !defined(AFX_DLGDEVICESETUP2_H__87E7D054_CDB5_43C0_A392_12F4B6D1AFB0__INCLUDED_)
#define AFX_DLGDEVICESETUP2_H__87E7D054_CDB5_43C0_A392_12F4B6D1AFB0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceSetup2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup2 dialog

class CDlgDeviceSetup2 : public CDialog
{
// Construction
public:
	CDlgDeviceSetup2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeviceSetup2)
	enum { IDD = IDD_DLG_DEVICE_SETUP2 };
	BOOL	m_bByteCounting;
	BOOL	m_bLockKeyPad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceSetup2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceSetup2)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICESETUP2_H__87E7D054_CDB5_43C0_A392_12F4B6D1AFB0__INCLUDED_)
