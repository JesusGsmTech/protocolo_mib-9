#if !defined(AFX_DLGDEVICESETLIVEPARAM_H__87849291_6975_440D_84B3_61AE0E078C81__INCLUDED_)
#define AFX_DLGDEVICESETLIVEPARAM_H__87849291_6975_440D_84B3_61AE0E078C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceSetLiveParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetLiveParam dialog

class CDlgDeviceSetLiveParam : public CDialog
{
// Construction
public:
	CDlgDeviceSetLiveParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgDeviceSetLiveParam)
	enum { IDD = IDD_DLG_DEVICE_SET_LIVE };
	int		m_iKnock;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceSetLiveParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceSetLiveParam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICESETLIVEPARAM_H__87849291_6975_440D_84B3_61AE0E078C81__INCLUDED_)
