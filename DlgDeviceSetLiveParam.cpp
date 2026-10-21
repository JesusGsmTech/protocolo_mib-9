// DlgDeviceSetLiveParam.cpp : implementation file
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgDeviceSetLiveParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetLiveParam dialog


CDlgDeviceSetLiveParam::CDlgDeviceSetLiveParam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceSetLiveParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeviceSetLiveParam)
	m_iKnock = -1;
	//}}AFX_DATA_INIT
}


void CDlgDeviceSetLiveParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceSetLiveParam)
	DDX_Radio(pDX, IDC_RADIO_KNOCK, m_iKnock);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceSetLiveParam, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceSetLiveParam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetLiveParam message handlers
