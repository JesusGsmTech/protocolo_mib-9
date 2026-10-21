// DlgDispenseStart.cpp : implementation file
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgDispenseStart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDispenseStart dialog


CDlgDispenseStart::CDlgDispenseStart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDispenseStart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDispenseStart)
	m_Amount = _T("");
	//}}AFX_DATA_INIT
	m_lAmount = _T(0x00);
}


void CDlgDispenseStart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDispenseStart)
	DDX_Text(pDX, IDC_DISPENSE_START_AMOUNT, m_Amount);
	DDV_MaxChars(pDX, m_Amount, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDispenseStart, CDialog)
	//{{AFX_MSG_MAP(CDlgDispenseStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDispenseStart message handlers

BOOL CDlgDispenseStart::PreTranslateMessage(MSG* pMsg) 
{
	if (pMsg->message == WM_KEYDOWN) {
		if ((pMsg->wParam >= 48) && (pMsg->wParam <= 57)) ;
		else if (pMsg->wParam == VK_BACK) ;
		else return TRUE;
	}

//		if ((pMsg->wParam == VK_RETURN) || (pMsg->wParam == VK_ESCAPE)) return TRUE;
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgDispenseStart::OnOK() 
{
	// TODO: Add extra validation here
	m_lAmount = 0x00;
	UpdateData(TRUE);

	unsigned char amount[9];
	wsprintf((char *)amount, (LPCTSTR)m_Amount, 8);
	m_lAmount = atoi((const char*)amount);

	if(m_lAmount <= 0x00ffffff)
	{
		CDialog::OnOK();
	}
	else
	{
		AfxMessageBox("Maximum value is 16777215!!!", IDOK, 0);
	}
}

