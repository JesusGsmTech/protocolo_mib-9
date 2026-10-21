// DlgSetupStateData2.cpp : implementation file
//

#include "stdafx.h"
#include "ifd.h"
#include "DlgSetupStateData2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int m_iNumDenom;
/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData2 dialog

CDlgSetupStateData2::CDlgSetupStateData2(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetupStateData2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetupStateData2)
	m_bAddon = FALSE;
	m_bAuto = FALSE;
	m_bBatch = FALSE;
	m_bBeep = FALSE;
	m_bIROn = FALSE;
	m_bModeLock = FALSE;
	m_bMROn = FALSE;
	m_bUVOn = FALSE;
	m_lBatchCnt = 0;
	m_lIRLevel = 0;
	m_lMRLevel = 0;
	m_lUVLevel = 0;
	//}}AFX_DATA_INIT
}


void CDlgSetupStateData2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetupStateData2)
	DDX_Control(pDX, IDC_COMBO_STACK_POCKET_SETUP2, m_comboStaPocket);
	DDX_Control(pDX, IDC_COMBO_REJECT_POCKET_SETUP2, m_comboRejPocket);
	DDX_Control(pDX, IDC_COMBO_DENOM_SETUP2, m_comboDenom);
	DDX_Control(pDX, IDC_COMBO_CURRENCY_CODE_SETUP2, m_comboCurrency);
	DDX_Control(pDX, IDC_COMBO_COUNT_MODE_SETUP2, m_comboCountMode);
	DDX_Check(pDX, IDC_CHECK_ADD_SETUP2, m_bAddon);
	DDX_Check(pDX, IDC_CHECK_AUTO_SETUP2, m_bAuto);
	DDX_Check(pDX, IDC_CHECK_BATCH_SETUP2, m_bBatch);
	DDX_Check(pDX, IDC_CHECK_BEEP_SETUP2, m_bBeep);
	DDX_Check(pDX, IDC_CHECK_IR_SETUP2, m_bIROn);
	DDX_Check(pDX, IDC_CHECK_MODE_LOCK_SET, m_bModeLock);
	DDX_Check(pDX, IDC_CHECK_MR_SETUP2, m_bMROn);
	DDX_Check(pDX, IDC_CHECK_UV_SETUP2, m_bUVOn);
	DDX_Text(pDX, IDC_EDIT_BATCH_COUNT_SETUP2, m_lBatchCnt);
	DDV_MinMaxInt(pDX, m_lBatchCnt, 10, 200);
	DDX_Text(pDX, IDC_EDIT_IR_LEVEL_SETUP2, m_lIRLevel);
	DDV_MinMaxInt(pDX, m_lIRLevel, 1, 15);
	DDX_Text(pDX, IDC_EDIT_MR_LEVEL_SETUP2, m_lMRLevel);
	DDV_MinMaxInt(pDX, m_lMRLevel, 1, 15);
	DDX_Text(pDX, IDC_EDIT_UV_LEVEL_SETUP2, m_lUVLevel);
	DDV_MinMaxInt(pDX, m_lUVLevel, 1, 15);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetupStateData2, CDialog)
	//{{AFX_MSG_MAP(CDlgSetupStateData2)
	ON_CBN_SELCHANGE(IDC_COMBO_CURRENCY_CODE_SETUP2, OnSelchangeComboCurrencyCodeSetup2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData2 message handlers

void CDlgSetupStateData2::OnSelchangeComboCurrencyCodeSetup2() 
{
	// TODO: Add your control notification handler code here
	SetDenomCombo( 1 );	
}

void CDlgSetupStateData2::OnOK() 
{
	// TODO: Add extra validation here
    int index;
    char lpDenomString[100];
    char lpModeString[100];
	
    index = m_comboCountMode.GetCurSel();
    m_comboCountMode.GetLBText(index, lpModeString);
    if (strcmp(lpModeString, "COUNT") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 0; 
    else if (strcmp(lpModeString, "MIXED") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 1;
    else if (strcmp(lpModeString, "SINGLE") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 2;
    else if (strcmp(lpModeString, "FACE") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 3;
    else if (strcmp(lpModeString, "ORIENT") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 4;
    else if (strcmp(lpModeString, "RESERVED") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 5;
    else if (strcmp(lpModeString, "ISSUE") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 6;
    else if (strcmp(lpModeString, "RESERVED") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 7;
    else if (strcmp(lpModeString, "SERIAL") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 8;
    else if (strcmp(lpModeString, "MIXED CURR") == 0) m_baSelect[ENUM_SETUP_COUNT_MODE] = 9;
    
	m_baSelect[ENUM_SETUP_CURRENCY_CODE]	= m_comboCurrency.GetCurSel();
    index = m_comboDenom.GetCurSel();
    m_comboDenom.GetLBText(index, lpDenomString);
    if (strcmp(lpDenomString, "DD") == 0) m_baSelect[ENUM_SETUP_DENOM] = 31; // DD
    else if (strcmp(lpDenomString, "DD ALL") == 0) m_baSelect[ENUM_SETUP_DENOM] = 30; // DD ALL
    else m_baSelect[ENUM_SETUP_DENOM] = index;

    
	m_baSelect[ENUM_SETUP_REJECT_POCKET]	= m_comboRejPocket.GetCurSel();
	m_baSelect[ENUM_SETUP_STACK_POCKET]		= m_comboStaPocket.GetCurSel();
	
	CDialog::OnOK();	
}

void CDlgSetupStateData2::SetDenomCombo( int iCurrency )
{
	m_comboDenom.ResetContent();

	switch( m_comboCurrency.GetCurSel() + 1 )
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
        m_comboDenom.AddString( "STATIC" );
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

BOOL CDlgSetupStateData2::OnInitDialog() 
{
    int index;    
	CDialog::OnInitDialog();
	
	m_comboCountMode.AddString( "COUNT" );
	m_comboCountMode.AddString( "MIXED" );
	m_comboCountMode.AddString( "SINGLE" );
	m_comboCountMode.AddString( "FACE" );
	m_comboCountMode.AddString( "ORIENT" );
	m_comboCountMode.AddString( "RESERVED" );
	m_comboCountMode.AddString( "ISSUE" );
	m_comboCountMode.AddString( "RESERVED" );
	m_comboCountMode.AddString( "SERIAL" );
	m_comboCountMode.AddString( "MIXED CURR" );
	m_comboCountMode.SetCurSel( m_baSelect[ENUM_SETUP_COUNT_MODE] );

	extern const char *gpaCurrencyName[];
	for( int i = 1; i < MAX_CURRENCY+1; i++ )
		m_comboCurrency.AddString( gpaCurrencyName[i] );

	m_comboCurrency.SetCurSel( m_baSelect[ENUM_SETUP_CURRENCY_CODE] );

	SetDenomCombo( m_baSelect[ENUM_SETUP_CURRENCY_CODE] );

	m_iNumDenom = m_comboDenom.GetCount();

    index = m_baSelect[ENUM_SETUP_DENOM];
    if (index == 31) // DD
    {
        m_comboDenom.SetCurSel(m_iNumDenom-1);
    } else
    {
    	m_comboDenom.SetCurSel( index );
    }

	// m_comboDenom --> 이동...

	m_comboRejPocket.AddString( "30" );
	m_comboRejPocket.AddString( "20" );
	m_comboRejPocket.AddString( "10" );
	m_comboRejPocket.SetCurSel( m_baSelect[ENUM_SETUP_REJECT_POCKET] );
	
	m_comboStaPocket.AddString( "200" );
	m_comboStaPocket.AddString( "150" );
	m_comboStaPocket.AddString( "100" );
	m_comboStaPocket.SetCurSel( m_baSelect[ENUM_SETUP_STACK_POCKET] );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
