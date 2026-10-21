// DlgMultiBatch.cpp : implementation file
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgMultiBatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiBatch dialog


CDlgMultiBatch::CDlgMultiBatch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMultiBatch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMultiBatch)
	m_iDenom0 = 0;
	m_iDenom1 = 0;
	m_iDenom2 = 0;
	m_iDenom3 = 0;
	m_iDenom4 = 0;
	m_iDenom5 = 0;
	m_iDenom6 = 0;
	//}}AFX_DATA_INIT
}


void CDlgMultiBatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMultiBatch)
	DDX_Text(pDX, IDC_EDIT_DENOM0, m_iDenom0);
	DDV_MinMaxInt(pDX, m_iDenom0, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM1, m_iDenom1);
	DDV_MinMaxInt(pDX, m_iDenom1, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM2, m_iDenom2);
	DDV_MinMaxInt(pDX, m_iDenom2, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM3, m_iDenom3);
	DDV_MinMaxInt(pDX, m_iDenom3, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM4, m_iDenom4);
	DDV_MinMaxInt(pDX, m_iDenom4, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM5, m_iDenom5);
	DDV_MinMaxInt(pDX, m_iDenom5, 0, 255);
	DDX_Text(pDX, IDC_EDIT_DENOM6, m_iDenom6);
	DDV_MinMaxInt(pDX, m_iDenom6, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMultiBatch, CDialog)
	//{{AFX_MSG_MAP(CDlgMultiBatch)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMultiBatch message handlers
