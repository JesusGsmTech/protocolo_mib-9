// DlgDeviceSetup2.cpp : implementation file
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgDeviceSetup2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup2 dialog


CDlgDeviceSetup2::CDlgDeviceSetup2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceSetup2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeviceSetup2)
	m_bByteCounting = FALSE;
	m_bLockKeyPad = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgDeviceSetup2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceSetup2)
	DDX_Check(pDX, IDC_CHECK_BYTE_COUNTING, m_bByteCounting);
	DDX_Check(pDX, IDC_CHECK_LOCK_KEYPAD, m_bLockKeyPad);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceSetup2, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceSetup2)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup2 message handlers
