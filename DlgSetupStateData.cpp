// DlgSetupStateData.cpp : implementation file
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgSetupStateData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData dialog


CDlgSetupStateData::CDlgSetupStateData(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetupStateData::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetupStateData)
	m_bBeepEnable = FALSE;
	m_bAuto = FALSE;
	m_bAddOn = FALSE;
	m_bUVOn = FALSE;
	m_bMROn = FALSE;
	m_bModeLockOn = FALSE;
	m_bBatchOn = FALSE;
	m_lBatchCountNum = 0;
	//}}AFX_DATA_INIT
}


void CDlgSetupStateData::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetupStateData)
	DDX_Control(pDX, IDC_COMBO_STACK_POCKET, m_comboStackPocket);
	DDX_Control(pDX, IDC_COMBO_REJECT_POCKET, m_comboRejectPocket);
	DDX_Control(pDX, IDC_COMBO_CURRENCY_CODE, m_comboCurrencyCode);
	DDX_Control(pDX, IDC_COMBO_COUNT_MODE, m_comboCountMode);
	DDX_Control(pDX, IDC_COMBO_DENOM, m_comboDenom);
	DDX_Check(pDX, IDC_CHECK_BEEP, m_bBeepEnable);
	DDX_Check(pDX, IDC_CHECK_AUTO, m_bAuto);
	DDX_Check(pDX, IDC_CHECK_ADD, m_bAddOn);
	DDX_Check(pDX, IDC_CHECK_UV, m_bUVOn);
	DDX_Check(pDX, IDC_CHECK_MR, m_bMROn);
	DDX_Check(pDX, IDC_CHECK_MODE_LOCK, m_bModeLockOn);
	DDX_Check(pDX, IDC_CHECK_BATCH, m_bBatchOn);
	DDX_Text(pDX, IDC_EDIT_BATCH_COUNT, m_lBatchCountNum);
	DDV_MinMaxLong(pDX, m_lBatchCountNum, 10, 999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetupStateData, CDialog)
	//{{AFX_MSG_MAP(CDlgSetupStateData)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENCY_CODE, OnSelchangeComboCurrencyCode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData message handlers

void CDlgSetupStateData::SetDenomCombo( int iCurrency )
{
	m_comboDenom.ResetContent();

	switch( m_comboCurrencyCode.GetCurSel() + 1 )
	{
	case CUR_USD:
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_PESOS:
		m_comboDenom.AddString( "P20" );
		m_comboDenom.AddString( "P50" );
		m_comboDenom.AddString( "P100" );
		m_comboDenom.AddString( "P200" );
		m_comboDenom.AddString( "P500" );
		m_comboDenom.AddString( "P1000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_WON:
		m_comboDenom.AddString( "$1000" );
		m_comboDenom.AddString( "$5000" );
		m_comboDenom.AddString( "$10000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_EURO:
		m_comboDenom.AddString( "5 EURO" );
		m_comboDenom.AddString( "10 EURO" );
		m_comboDenom.AddString( "20 EURO" );
		m_comboDenom.AddString( "50 EURO" );
		m_comboDenom.AddString( "100 EURO" );
		m_comboDenom.AddString( "200 EURO" );
		m_comboDenom.AddString( "500 EURO" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_COLOMBIA:
		m_comboDenom.AddString( "P1000" );
		m_comboDenom.AddString( "P2000" );
		m_comboDenom.AddString( "P5000" );
		m_comboDenom.AddString( "P10000" );
		m_comboDenom.AddString( "P20000" );
		m_comboDenom.AddString( "P50000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_WIAN: // 표에 없어서 못 넣었슴
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_LIRA:
		m_comboDenom.AddString( "L1" );
		m_comboDenom.AddString( "L5" );
		m_comboDenom.AddString( "L10" );
		m_comboDenom.AddString( "L20" );
		m_comboDenom.AddString( "L50" );
		m_comboDenom.AddString( "L100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_COSTA: // 표에 없어서 못 넣었슴
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_NICARA: // 표에 없어서 못 넣었슴
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_AUSTRA:
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_SINGAPORE: // 표에 없어서 못 넣었슴
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_INDIA:
		m_comboDenom.AddString( "R10" );
		m_comboDenom.AddString( "R20" );
		m_comboDenom.AddString( "R50" );
		m_comboDenom.AddString( "R100" );
		m_comboDenom.AddString( "R500" );
		m_comboDenom.AddString( "R1000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_NORWAY:
		m_comboDenom.AddString( "K50" );
		m_comboDenom.AddString( "K100" );
		m_comboDenom.AddString( "K200" );
		m_comboDenom.AddString( "K500" );
		m_comboDenom.AddString( "K1000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_NEWZILAND:
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_POLSKI:
		m_comboDenom.AddString( "Z10" );
		m_comboDenom.AddString( "Z20" );
		m_comboDenom.AddString( "Z50" );
		m_comboDenom.AddString( "Z100" );
		m_comboDenom.AddString( "Z200" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_TAIWAN:
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "$200" );
		m_comboDenom.AddString( "$500" );
		m_comboDenom.AddString( "$1000" );
		m_comboDenom.AddString( "$2000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_CZECHO:
		m_comboDenom.AddString( "K50" );
		m_comboDenom.AddString( "K100" );
		m_comboDenom.AddString( "K200" );
		m_comboDenom.AddString( "K500" );
		m_comboDenom.AddString( "K1000" );
		m_comboDenom.AddString( "K2000" );
		m_comboDenom.AddString( "K5000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_LEBANON: // 표에 없어서 못 넣었슴
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_SWEDEN:
		m_comboDenom.AddString( "K20" );
		m_comboDenom.AddString( "K50" );
		m_comboDenom.AddString( "K100" );
		m_comboDenom.AddString( "K500" );
		m_comboDenom.AddString( "K1000" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_BRASIL:
//		m_comboDenom.AddString( "5 REAL" );
//		m_comboDenom.AddString( "10 REAL" );
//		m_comboDenom.AddString( "20 REAL" );
//		m_comboDenom.AddString( "50 REAL" );
//		m_comboDenom.AddString( "100 REAL" );
//		m_comboDenom.AddString( "200 REAL" );
//		m_comboDenom.AddString( "500 REAL" );
//		m_comboDenom.AddString( "STATIC" );

		m_comboDenom.AddString( "1 REAL" );
		m_comboDenom.AddString( "2 REAL" );
		m_comboDenom.AddString( "5 REAL" );
		m_comboDenom.AddString( "10 REAL" );
		m_comboDenom.AddString( "20 REAL" );
		m_comboDenom.AddString( "50 REAL" );
		m_comboDenom.AddString( "100 REAL" );
		m_comboDenom.AddString( "DD" );
		break;
	case CUR_CANADA:
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "$5N" );
		m_comboDenom.AddString( "$10N" );
		m_comboDenom.AddString( "$50N" );
		m_comboDenom.AddString( "$100N" );
		m_comboDenom.AddString( "$10NN" );
		m_comboDenom.AddString( "DD" );
		break;
    case CUR_SYRIA:
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "200" );
        m_comboDenom.AddString( "500" );
        m_comboDenom.AddString( "1000" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_GUATE:
        m_comboDenom.AddString( "5" );
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_IRAQ:
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "250" );
        m_comboDenom.AddString( "500" );
        m_comboDenom.AddString( "1000" );
        m_comboDenom.AddString( "5000" );
        m_comboDenom.AddString( "10000" );
        m_comboDenom.AddString( "25000" );
		m_comboDenom.AddString( "DD" );
        break;
        
	case CUR_ISRAEL: 
		m_comboDenom.AddString( "20" );
		m_comboDenom.AddString( "50" );
		m_comboDenom.AddString( "100" );
		m_comboDenom.AddString( "200" );
		m_comboDenom.AddString( "DD" );
		break;

	case CUR_PERU: 
		m_comboDenom.AddString( "10" );
		m_comboDenom.AddString( "20" );
		m_comboDenom.AddString( "50" );
		m_comboDenom.AddString( "100" );
		m_comboDenom.AddString( "200" );
		m_comboDenom.AddString( "DD" );
		break;
    case CUR_JPY: 
        m_comboDenom.AddString( "1000" );
        m_comboDenom.AddString( "2000" );
        m_comboDenom.AddString( "5000" );
        m_comboDenom.AddString( "10000" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_PAPUA: 
        m_comboDenom.AddString( "2" );
        m_comboDenom.AddString( "5" );
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_RUSSIA: 
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "500" );
        m_comboDenom.AddString( "1000" );
        m_comboDenom.AddString( "5000" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_SAFRICA: 
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "200" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_ARAB: 
        m_comboDenom.AddString( "5" );
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "200" );
        m_comboDenom.AddString( "500" );
        m_comboDenom.AddString( "1000" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_THAILAND: 
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "500" );
        m_comboDenom.AddString( "1000" );
		m_comboDenom.AddString( "DD" );
        break;
    case CUR_ENGLAND: 
        m_comboDenom.AddString( "5" );
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
		m_comboDenom.AddString( "DD" );
        break;

	case CUR_VENEZUELA:
        m_comboDenom.AddString( "VEB2" );
        m_comboDenom.AddString( "VEB5" );
        m_comboDenom.AddString( "VEB10" );
        m_comboDenom.AddString( "VEB20" );
        m_comboDenom.AddString( "VEB50" );
        m_comboDenom.AddString( "VEB100" );
		m_comboDenom.AddString( "DD" );
		break;

	case CUR_BARCODE:
		break;

	case CUR_UKRAINE:
		break;

	case CUR_KAZAKHSTAN:
		break;

	case CUR_SWITZERLAND:
        m_comboDenom.AddString( "CHF10" );
        m_comboDenom.AddString( "CHF20" );
        m_comboDenom.AddString( "CHF50" );
        m_comboDenom.AddString( "CHF100" );
        m_comboDenom.AddString( "CHF200" );
        m_comboDenom.AddString( "CHF1000" );
		m_comboDenom.AddString( "DD" );
		break;

    case CUR_SAR:
		break;
		
    case CUR_JOD:
		break;

    case CUR_KGS:
		break;

    case CUR_MYR:
		break;

    case CUR_MCQ:
		break;

    case CUR_IDR:
		break;

    case CUR_SDD:
		break;

    case CUR_RON:
		break;

    case CUR_BYB:
		break;

    case CUR_AZN:
		break;

    case CUR_RSD:
		break;

    case CUR_DOP:
		break;

    case CUR_SRD:
		break;

	case CUR_TID:
		break;

	case CUR_HUF:
		break;

	case CUR_HRK:
        m_comboDenom.AddString( "5" );
        m_comboDenom.AddString( "10" );
        m_comboDenom.AddString( "20" );
        m_comboDenom.AddString( "50" );
        m_comboDenom.AddString( "100" );
        m_comboDenom.AddString( "200" );
		m_comboDenom.AddString( "500" );
		m_comboDenom.AddString( "1000" );
		m_comboDenom.AddString( "DD" );
		break;

	case CUR_GHC:
		break;
	default:
		m_comboDenom.AddString( "$1" );
		m_comboDenom.AddString( "$2" );
		m_comboDenom.AddString( "$5" );
		m_comboDenom.AddString( "$10" );
		m_comboDenom.AddString( "$20" );
		m_comboDenom.AddString( "$50" );
		m_comboDenom.AddString( "$100" );
		m_comboDenom.AddString( "DD" );
		break;
	};

}

BOOL CDlgSetupStateData::OnInitDialog() 
{
    int index;
    
	CDialog::OnInitDialog();
	
	m_comboCountMode.AddString( "COUNT" );
	m_comboCountMode.AddString( "MIXED" );
	m_comboCountMode.AddString( "SINGLE" );
	m_comboCountMode.AddString( "FACE" );
	m_comboCountMode.AddString( "ORIENT" );
	m_comboCountMode.AddString( "ISSUE" );
	m_comboCountMode.SetCurSel( m_baSelect[ENUM_SETUP_COUNT_MODE] );

	extern const char *gpaCurrencyName[];
	for( int i = 1; i < MAX_CURRENCY+1; i++ )
		m_comboCurrencyCode.AddString( gpaCurrencyName[i] );

	m_comboCurrencyCode.SetCurSel( m_baSelect[ENUM_SETUP_CURRENCY_CODE] );

	SetDenomCombo( m_baSelect[ENUM_SETUP_CURRENCY_CODE] );

    index = m_baSelect[ENUM_SETUP_DENOM];
    if (index == 31) // DD
    {
        m_comboDenom.SetCurSel(m_comboDenom.GetCount()-1);
    } else
    {
    	m_comboDenom.SetCurSel( index );
    }

	m_comboRejectPocket.AddString( "30" );
	m_comboRejectPocket.AddString( "20" );
	m_comboRejectPocket.AddString( "10" );
	m_comboRejectPocket.SetCurSel( m_baSelect[ENUM_SETUP_REJECT_POCKET] );
	
	m_comboStackPocket.AddString( "200" );
	m_comboStackPocket.AddString( "150" );
	m_comboStackPocket.AddString( "100" );
	m_comboStackPocket.SetCurSel( m_baSelect[ENUM_SETUP_STACK_POCKET] );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgSetupStateData::OnOK() 
{
    int index;
    char lpDenomString[100];
    char lpModeString[100];
    
	//m_baSelect[ENUM_SETUP_COUNT_MODE]		= m_comboCountMode.GetCurSel();
    index = m_comboCountMode.GetCurSel();
    m_comboCountMode.GetLBText(index, lpModeString);
    if (strcmp(lpModeString, "COUNT") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 0; 
    else if (strcmp(lpModeString, "MIXED") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 1;
    else if (strcmp(lpModeString, "SINGLE") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 2;
    else if (strcmp(lpModeString, "ISSUE") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 6;
    
	m_baSelect[ENUM_SETUP_CURRENCY_CODE]	= m_comboCurrencyCode.GetCurSel();
    
    index = m_comboDenom.GetCurSel();
    m_comboDenom.GetLBText(index, lpDenomString);
    if (strcmp(lpDenomString, "DD") == 0) m_baSelect[ENUM_SETUP_DENOM] = 31; // DD
    else if (strcmp(lpDenomString, "DD ALL") == 0) m_baSelect[ENUM_SETUP_DENOM] = 30; // DD ALL
    else m_baSelect[ENUM_SETUP_DENOM] = index;

    
	m_baSelect[ENUM_SETUP_REJECT_POCKET]	= m_comboRejectPocket.GetCurSel();
	m_baSelect[ENUM_SETUP_STACK_POCKET]		= m_comboStackPocket.GetCurSel();
	
	CDialog::OnOK();
}

void CDlgSetupStateData::OnSelchangeComboCurrencyCode() 
{
	SetDenomCombo( 1 );
}
