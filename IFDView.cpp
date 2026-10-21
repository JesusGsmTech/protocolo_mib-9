// IFDView.cpp : implementation of the CIFDView class
//

#include "stdafx.h"
#include "IFD.h"

#include "IFDDoc.h"
#include "IFDView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern int m_iNumDenom;
const char *gpaCurrencyName[] = {
	"",
	"US Dollar",
	"Mexico",
	"Korea",
	"Euro",
	"Costa Rica",
	"China",
	"Turkey",
	"Costa Rica Colone",
	"Nicaragua",
	"Australia",
	"Singapore",
	"India",
	"Norway",
	"Newziland",
	"Poland",
	"Taiwan",
	"CZECHO",
	"LEBANON",
	"SWEDEN",
	"BRASIL",
	"Canada",
	"Syria",
	"Guatemala",
	"Iraq",
	"Israel",
	"Peru",
	"Coupon1",
    "Coupon2",
    "Coupon3",
    "Coupon4",
    "Coupon5",
    "Coupon6",
    "Japan",
    "Papua New Guinea",
    "Russia",
    "South Africa",
    "Arab Emirates",
    "Thailand",
    "England",
	"Venezuela",
	"Barcode",
	"Ukraine",
	"Kazakhstan",
	"Switzerland",
	"Saudi Arabia",
	"Jordan",
	"Kyrgyzstan",
	"Malaysia",
	"Malaysia cheque",
	"Indonesia",
	"Sudan",
	"Romania",
	"Belarus",
	"Azerbaijani",
	"Serbia",
	"Dominica",
	"Suriname",
	"Canada",
	"Hungary",
	"Croatia",
	"Ghana",
	"GEL",
	"EGP", 
	"UGX", 
	"MAD", 
	"LKR", 
	"AMD", 
	"NAD",	
	"HNL", 
	"KWD", 
	"HKD", 
	"ETB", 
	"PHP", 
	"MNT", 
	"IRR",	
	"SZL", 
	"BWP",	
	"QAR",	
	"STL",	
	"AOA",	
	"MZN",	
	"OMR", 
	"YER",	
	"BGN",	
	"PKR", 
	"MSP", 
	"LYD", 
	"NGN", 
	"LSL", 
	"BHD", 
	"TWD", 
	"ZAD", 
	"ZMK", 
	"ATS", 
	"CLP", 
	"DZD", 
	"DKK", 
	"XPF", 
	"MOP", 
	"MKD", 
	"FJD", 
	"BAM",	
	"VND",	
	"KES",	
	"XOF",	
	"LAK",	
	"MMK",	
	"BDT",	
	"CUP",	
	"MDL",	
	"SCP",	
	"IRP",	
	"XAF",	
	"CP7",	
	"ARS",	
	"GIS",	
	"BYN",	
	"NPR",	
	"IQD",	
	"TZS",	
	"RWF", 
	"BIF", 
	"ZWD",	
	"REKA",
	"ALL",	
	"MUR",	
	"TJS",	
	"CVE",	
	"DJF",	
	"VES",	
	"LCH",	
	"TCH",	
	"JMD",	
	"UZS",	
	"SYC",	
	"CDF",	
	"ONR",	
	"KHR",	
	"ZWL",	
	"BND",	

	"TEST1",
	"TEST2",
	"TEST3",
	"TEST4",
	"TEST5",
	"TEST6",
	"TEST7",
	"TEST8",
	"TEST9",
	"TEST10",

	"PYG",
	"GMD",
	"AFN",
	"NHV",	// NH bank Voucher
	"GYD",	// Guyana
	"MGA",	// Madagascar
	"TND",	// Tunisienne
	"SJV",	// Seongju Voucher
	"PBV",	// Paris Baguette Voucher
	"SLL",	// Sierra Leone
	"GNF",	// Guinea
	"LRD",	// Republic of Liberia
	"WST",	// Samoa
	"Other"
};

const char *gpaCurrencyCode[] = {
	"",
	"USD",
	"MXN",
	"KRW",
	"EUR",
	"COP",
	"CNY",
	"YTL",
	"CRC",
	"NIO",
	"AUD",
	"SGD",
	"INR",
	"NOK",
	"NZD",
	"PLN",
	"NTD",
	"CZK",
	"LBP",
	"SEK",
	"BRL",
	"CAD",
	"SYP",
	"GTQ",
	"NID",	// Iraq
	"ILS",
	"PEN",
	"Coupon1",
    "Coupon2",
    "Coupon3",
    "Coupon4",
    "Coupon5",
    "Coupon6",
    "JPY",
    "PGK",
    "RUB",
    "ZAR",
    "AED",
    "THB",
    "GBP",
	"VEB",
	"BAR",
	"UAH",
	"KZT",
	"CHF",
	"SAR",
	"JOD",
	"KGS",
	"MYR",
	"MCQ",
	"IDR",
	"SDG",
	"RON",
	"BYB",
	"AZN",
	"RSD",
	"DOP",
	"SRD",
	"TID",
	"HUF",
	"HRK",
	"GHS",
	"GEL",
	"EGP", 
	"UGX", 
	"MAD", 
	"LKR", 
	"AMD", 
	"NAD",	
	"HNL", 
	"KWD", 
	"HKD", 
	"ETB", 
	"PHP", 
	"MNT", 
	"IRR",	
	"SZL", 
	"BWP",	
	"QAR",	
	"STL",	
	"AOA",	
	"MZN",	
	"OMR", 
	"YER",	
	"BGN",	
	"PKR", 
	"MSP", 
	"LYD", 
	"NGN", 
	"LSL", 
	"BHD", 
	"TWD", 
	"ZAD", 
	"ZMK", 
	"ATS", 
	"CLP", 
	"DZD", 
	"DKK", 
	"XPF", 
	"MOP", 
	"MKD", 
	"FJD", 
	"BAM",	
	"VND",	
	"KES",	
	"XOF",	
	"LAK",	
	"MMK",	
	"BDT",	
	"CUP",	
	"MDL",	
	"SCP",	
	"IRP",	
	"XAF",	
	"CP7",	
	"ARS",	
	"GIS",	
	"BYN",	
	"NPR",	
	"IQD",	
	"TZS",	
	"RWF", 
	"BIF", 
	"ZWD",	
	"REKA",
	"ALL",	
	"MUR",	
	"TJS",	
	"CVE",	
	"DJF",	
	"VES",	
	"LCH",	
	"TCH",	
	"JMD",	
	"UZS",	
	"SYC",	
	"CDF",	
	"ONR",	
	"KHR",	
	"ZWL",	
	"BND",	

	"TEST1",
	"TEST2",
	"TEST3",
	"TEST4",
	"TEST5",
	"TEST6",
	"TEST7",
	"TEST8",
	"TEST9",
	"TEST10",

	"PYG",
	"GMD",
	"AFN",
	"NHV",	// NH bank Voucher
	"GYD",	// Guyana
	"MGA",	// Madagascar
	"TND",	// Tunisienne
	"SJV",	// Seongju Voucher
	"PBV",	// Paris Baguette Voucher
	"SLL",	// Sierra Leone
	"GNF",	// Guinea
	"LRD",	// Republic of Liberia
	"WST",	// Samoa
	"Other"
};

const char *gpaUSD_Denom[] =
{
	"$1",
	"$2",
	"$5",
	"$10", 
	"$20",
	"$50",
	"$100"
};

const char *gpaYTL_Denom[] =
{
	"L1",
	"L5",
	"L10",
	"L20", 
	"L50",
	"L100"
};

const char *gpaEURO_Denom[] =
{
	"e5",
	"e10",
	"e20",
	"e50", 
	"e100",
	"e200",
	"e500"
};

const unsigned long DEVICE_SET_LIVE_KNOCK	= 1;
const unsigned long DEVICE_SET_LIVE_ACK		= 2;
const unsigned long DEVICE_SET_LIVE_RELEASE	= 4;

const unsigned long MOTOR_SPEED_400		= 0;
const unsigned long MOTOR_SPEED_800		= 1;
const unsigned long MOTOR_SPEED_1000	= 2;
const unsigned long MOTOR_SPEED_1200	= 3;

const unsigned long ON			= 1;
const unsigned long OFF			= 0;

const unsigned long PARALLEL	= 1;
const unsigned long SERIAL		= 0;

const unsigned long ENABLE		= 1;
const unsigned long DISABLE		= 0;

const unsigned long AUTO		= 1;
const unsigned long MANUAL		= 0;

const unsigned long US_DOLLAR	= 1;
const unsigned long EURO		= 4;

const unsigned long COUNTING_COUNT_MODE				= 0;
const unsigned long COUNTING_MIXED_MODE				= 1;
const unsigned long COUNTING_SINGLE_MODE			= 2;
const unsigned long COUNTING_FACE_MODE				= 3;
const unsigned long COUNTING_ORIENT_MODE			= 4;
const unsigned long COUNTING_SERIAL_NO_PRINT_MODE	= 5;

const unsigned long REJECT_70_PCS			= 0;
const unsigned long REJECT_50_PCS			= 1;
const unsigned long REJECT_30_PCS			= 2;

const unsigned long STACKER_200_PCS			= 0;
const unsigned long STACKER_150_PCS			= 1;
const unsigned long STACKER_100_PCS			= 2;

const unsigned long MR_HIGH		= 0;
const unsigned long MR_MEDIUM	= 1;
const unsigned long MR_LOW		= 2;

// COUNT_START
const unsigned long NO_NEW_DEPOSIT	= 0;
const unsigned long NEW_DEPOSIT		= 1;

const unsigned long JAM_ERROR		= 1;
const unsigned long FEEDING_ERROR	= 2;
const unsigned long FEED_MOTOR_ERROR = 8;
const unsigned long MAIN_MOTOR_ERROR = 16;


const unsigned long RESULT_DATA_REJECT_POCKET	= 101;
const unsigned long RESULT_DATA_STACKER_POCKET	= 102;
const unsigned long RESULT_DATA_CF				= 103;


/////////////////////////////////////////////////////////////////////////////
// CIFDView

IMPLEMENT_DYNCREATE(CIFDView, CFormView)

BEGIN_MESSAGE_MAP(CIFDView, CFormView)
	//{{AFX_MSG_MAP(CIFDView)
	ON_BN_CLICKED(IDC_BUTTON_CURRENCY_CHANGE, OnButtonCurrencyChange)
	ON_BN_CLICKED(IDC_BUTTON_DEFAULT_LOADING, OnButtonDefaultLoading)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SET_LIVE, OnButtonDeviceSetLive)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SETUP2, OnButtonDeviceSetup2)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SETUP_STATE_DATA, OnButtonDeviceSetupStateData)
	ON_BN_CLICKED(IDC_BUTTON_SEND_START, OnButtonSendStart)
	ON_BN_CLICKED(IDC_BUTTON_SEND_CLEAR, OnButtonSendClear)
	ON_BN_CLICKED(IDC_BUTTON_SEND_REQUEST, OnButtonSendRequest)
	ON_COMMAND(ID_COMMPORT_CONNECT, OnCommportConnect)
	ON_UPDATE_COMMAND_UI(ID_COMMPORT_CONNECT, OnUpdateCommportConnect)
	ON_COMMAND(ID_COMMPORT_DISCONNECT, OnCommportDisconnect)
	ON_UPDATE_COMMAND_UI(ID_COMMPORT_DISCONNECT, OnUpdateCommportDisconnect)
	ON_BN_CLICKED(IDC_BUTTON_DISPENSE_START, OnButtonDispenseStart)
	ON_BN_CLICKED(IDC_BUTTON_OCR, OnButtonOcr)
	ON_BN_CLICKED(IDC_BUTTON_MULTI_BATCH, OnButtonMultiBatch)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SETUP_STATE_DATA2, OnButtonDeviceSetupStateData2)
	ON_BN_CLICKED(IDC_BUTTON_BARCODE, OnButtonBarcode)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON_SEND_STOP, &CIFDView::OnButtonSendStop)
	ON_COMMAND(ID_TCP_CONNECT, &CIFDView::OnTcpConnect)
	ON_UPDATE_COMMAND_UI(ID_TCP_CONNECT, &CIFDView::OnUpdateTcpConnect)
	ON_COMMAND(ID_TCP_DISCONNECT, &CIFDView::OnTcpDisconnect)
	ON_UPDATE_COMMAND_UI(ID_TCP_DISCONNECT, &CIFDView::OnUpdateTcpDisconnect)
	ON_BN_CLICKED(IDC_SEND_CANCEL_START, &CIFDView::OnBnClickedSendCancelStart)
	ON_BN_CLICKED(IDC_REBOOT, &CIFDView::OnBnClickedReboot)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BMP_TO_USB, &CIFDView::OnBnClickedButtonSaveBmpToUsb)
	ON_BN_CLICKED(IDC_BUTTON_SAVE_BMP_TO_USB2, &CIFDView::OnBnClickedButtonSaveBmpToUsb2)
	ON_BN_CLICKED(IDC_BUTTON_WING_MOTOR_START, &CIFDView::OnBnClickedButtonWingMotorStart)
	ON_BN_CLICKED(IDC_BUTTON_WING_MOTOR_STOP, &CIFDView::OnBnClickedButtonWingMotorStop)
	ON_BN_CLICKED(IDC_BUTT_SET_REF_NO, &CIFDView::OnBnClickedButtSetRefNo)
	ON_BN_CLICKED(IDC_BUTT_REQ_LOG, &CIFDView::OnBnClickedButtReqLog)
	//ON_BN_CLICKED(IDC_BUTT_AS_ALARM_REQ, &CIFDView::OnBnClickedButtAsAlarmReq)
	ON_BN_CLICKED(IDC_BUTT_AS_ALARM_SET, &CIFDView::OnBnClickedButtAsAlarmSet)
	ON_BN_CLICKED(IDC_BUTTON_DEVICE_SETUP_STATE_DATA_EX, &CIFDView::OnBnClickedButtonDeviceSetupStateDataEx)
	ON_BN_CLICKED(IDC_BUTT_DATE_TIME, &CIFDView::OnBnClickedButtDateTime)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIFDView construction/destruction

CIFDView::CIFDView()
	: CFormView(CIFDView::IDD)
{
	//{{AFX_DATA_INIT(CIFDView)
	//}}AFX_DATA_INIT

	m_bCommPortConnected = false;

}

CIFDView::~CIFDView()
{
}

void CIFDView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIFDView)
	DDX_Control(pDX, IDC_EDIT_SEND, m_editSend);
	DDX_Control(pDX, IDC_COMBO_REQUEST, m_comboRequest);
	DDX_Control(pDX, IDC_COMBO_CLEAR, m_comboClear);
	DDX_Control(pDX, IDC_EDIT_RECEIVE, m_editReceive);
	DDX_Control(pDX, IDC_IFDX_SB7CTRL, m_IFDX);
	//}}AFX_DATA_MAP
}

BOOL CIFDView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CIFDView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

	m_comboClear.AddString( COMBO_STR_CLEAR_0 );
	m_comboClear.AddString( COMBO_STR_CLEAR_1 );
	m_comboClear.AddString( COMBO_STR_CLEAR_2 );
	m_comboClear.AddString( COMBO_STR_CLEAR_3 );
	m_comboClear.AddString( COMBO_STR_CLEAR_4 );
	m_comboClear.AddString( COMBO_STR_CLEAR_5 );
	m_comboClear.AddString( COMBO_STR_CLEAR_6 );
	m_comboClear.SetCurSel( 0 );

	m_comboRequest.AddString( COMBO_STR_REQUEST_0	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_1	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_2	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_3	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_4	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_5	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_6	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_7	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_8	);
	m_comboRequest.AddString( COMBO_STR_REQUEST_9	);
	m_comboRequest.SetCurSel( 0 );

	((CEdit*)GetDlgItem(IDC_EDIT_SEND))->SetLimitText((DWORD)-1);
	((CEdit*)GetDlgItem(IDC_EDIT_RECEIVE))->SetLimitText((DWORD)-1);
}

/////////////////////////////////////////////////////////////////////////////
// CIFDView printing

BOOL CIFDView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIFDView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIFDView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIFDView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CIFDView diagnostics

#ifdef _DEBUG
void CIFDView::AssertValid() const
{
	CFormView::AssertValid();
}

void CIFDView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CIFDDoc* CIFDView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIFDDoc)));
	return (CIFDDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CIFDView message handlers

void CIFDView::OnButtonCurrencyChange() 
{
	if( m_IFDX.SendCurrencyChange() )
		AddStrToSendEdit( "->SendCurrencyChange() OK\n" );
	else
		AddStrToSendEdit( "->SendCurrencyChange() Error\n" );
}

void CIFDView::OnButtonDefaultLoading() 
{
	if( m_IFDX.SendDefaultLoading() )
		AddStrToSendEdit( "->SendDefaultLoading() OK\n" );
	else
		AddStrToSendEdit( "->SendDefaultLoading() Error\n" );
}

void CIFDView::OnButtonDeviceSetLive() 
{
	LONG lParam;

	m_dlgDeviceSetLive.m_iKnock = 0;

	if( m_dlgDeviceSetLive.DoModal() == IDOK )
	{
		if( m_dlgDeviceSetLive.m_iKnock == 0 )
		{
			AddStrToSendEdit( "\nlParam = DEVICE_SET_LIVE_KNOCK\n" );
			lParam = DEVICE_SET_LIVE_KNOCK;
		}
		else
		{
			AddStrToSendEdit( "\nlParam = DEVICE_SET_LIVE_RELEASE\n" );
			lParam = DEVICE_SET_LIVE_RELEASE;
		}
			
		if( m_IFDX.SendDeviceSetLive( lParam ) )
		{
			AddStrToSendEdit( "->SendDeviceSetLive() OK\n" );

			CString str;
			m_editSend.GetWindowText( str );

			CWnd *pWnd = GetDlgItem( IDC_STATIC_DEVICE_ALIVE );
			pWnd->ShowWindow( SW_HIDE );
			pWnd = GetDlgItem( IDC_STATIC_DEVICE_NOTALIVE );
			pWnd->ShowWindow( SW_SHOW );
		}
		else
			AddStrToSendEdit( "->SendDeviceSetLive() Error\n" );
	}
	
}

void CIFDView::OnButtonDeviceSetup2() 
{
	LONG lByteCountingEnable, lLockKeyPad;

	if( m_IFDX.GetLByteCountingEnable() == 1 )
		m_dlgDeviceSetup2.m_bByteCounting = true;

	if( m_IFDX.GetLLockKeyPad() == 1 )
		m_dlgDeviceSetup2.m_bLockKeyPad = true;

	if( m_dlgDeviceSetup2.DoModal() == IDOK )
	{
		if( m_dlgDeviceSetup2.m_bByteCounting == 1 )
			AddStrToSendEdit( "\nlByteCountingEnable = TRUE\n" );
		else
			AddStrToSendEdit( "\nlLockKeyPad = FALSE\n" );

		lByteCountingEnable = (LONG)m_dlgDeviceSetup2.m_bByteCounting;


		if( m_dlgDeviceSetup2.m_bLockKeyPad == 1 )
			AddStrToSendEdit( "\nlByteCountingEnable = TRUE\n" );
		else
			AddStrToSendEdit( "\nlLockKeyPad = FALSE\n" );

		lLockKeyPad = (LONG)m_dlgDeviceSetup2.m_bLockKeyPad;


		if( m_IFDX.SendDeviceSetup2( lByteCountingEnable, lLockKeyPad ) )
			AddStrToSendEdit( "->SendDeviceSetup2() OK\n" );
		else
			AddStrToSendEdit( "->SendDeviceSetup2() Error\n" );
	}
	
}

void CIFDView::OnButtonDeviceSetupStateData() 
{
	m_dlgSetupStateData.m_bAddOn	= (BOOL)m_IFDX.GetLADDOn();
	m_dlgSetupStateData.m_bBatchOn	= (BOOL)m_IFDX.GetLBatchOn();
	m_dlgSetupStateData.m_bBeepEnable = (BOOL)m_IFDX.GetLBeepEnable();
	m_dlgSetupStateData.m_bAuto		= (BOOL)m_IFDX.GetLAuto();
	m_dlgSetupStateData.m_bUVOn		= (BOOL)m_IFDX.GetLUVOn();
	m_dlgSetupStateData.m_bMROn		= (BOOL)m_IFDX.GetLMROn();
	m_dlgSetupStateData.m_bModeLockOn = (BOOL)m_IFDX.GetLModeLockOn();
	m_dlgSetupStateData.m_lBatchCountNum = (BYTE)m_IFDX.GetLBatchCountNum();

	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_COUNT_MODE]	 = (BYTE)m_IFDX.GetLCountMode();
	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_DENOM]		 = (BYTE)m_IFDX.GetLDenom();
	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_REJECT_POCKET] = (BYTE)m_IFDX.GetLRejPocketCap();
	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_STACK_POCKET]  = (BYTE)m_IFDX.GetLStkPocketCap();
	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_MR_SENSITIVE]  = (BYTE)m_IFDX.GetLMRSensitive();
	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_PRINTER_TYPE]	 = (BYTE)m_IFDX.GetLPrintType();

	m_dlgSetupStateData.m_baSelect[ENUM_SETUP_CURRENCY_CODE] = (BYTE)(m_IFDX.GetLCurrencyCode() - 1);

	if(m_dlgSetupStateData.m_lBatchCountNum == 0)
		m_dlgSetupStateData.m_lBatchCountNum = 10;

	if( m_dlgSetupStateData.DoModal() == IDOK )
	{
		m_IFDX.SetLADDOn( m_dlgSetupStateData.m_bAddOn );
		m_IFDX.SetLBatchOn( m_dlgSetupStateData.m_bBatchOn );
		m_IFDX.SetLBeepEnable( m_dlgSetupStateData.m_bBeepEnable );
		m_IFDX.SetLAuto( m_dlgSetupStateData.m_bAuto );
		m_IFDX.SetLUVOn( m_dlgSetupStateData.m_bUVOn );
		m_IFDX.SetLMROn( m_dlgSetupStateData.m_bMROn );
		m_IFDX.SetLModeLockOn( m_dlgSetupStateData.m_bModeLockOn );
		m_IFDX.SetLCountMode( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_COUNT_MODE] );
		m_IFDX.SetLDenom( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_DENOM] );
		m_IFDX.SetLRejPocketCap( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_REJECT_POCKET] );
		m_IFDX.SetLStkPocketCap( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_STACK_POCKET] );
		m_IFDX.SetLMRSensitive( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_MR_SENSITIVE] );
		m_IFDX.SetLPrintType( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_PRINTER_TYPE] );
		m_IFDX.SetLBatchCountNum( m_dlgSetupStateData.m_lBatchCountNum );

		m_IFDX.SetLCurrencyCode( m_dlgSetupStateData.m_baSelect[ENUM_SETUP_CURRENCY_CODE] + 1 );


		CString str;

		str.Format( "SetLADDOn(%d)\n", m_IFDX.GetLADDOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchOn(%d)\n", m_IFDX.GetLBatchOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBeepEnable(%d)\n", m_IFDX.GetLBeepEnable() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLAuto(%d)\n", m_IFDX.GetLAuto() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLUVOn(%d)\n", m_IFDX.GetLUVOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMROn(%d)\n", m_IFDX.GetLMROn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLModeLockOn(%d)\n", m_IFDX.GetLModeLockOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCountMode(%d)\n", m_IFDX.GetLCountMode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLDenom(%d)\n", m_IFDX.GetLDenom() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLRejPocketCap(%d)\n", m_IFDX.GetLRejPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLStkPocketCap(%d)\n", m_IFDX.GetLStkPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMRSensitive(%d)\n", m_IFDX.GetLMRSensitive() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLPrintType(%d)\n", m_IFDX.GetLPrintType() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCurrencyCode(%d)\n", m_IFDX.GetLCurrencyCode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchCountNum(%d)\n", m_IFDX.GetLBatchCountNum() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetupStateData() )
			AddStrToSendEdit( "->SendSetupStateData() OK\n" );
		else
			AddStrToSendEdit( "->SendSetupStateData() Error\n" );
	}	
}

void CIFDView::OnButtonDispenseStart() 
{
	if( m_dlgDispenseStart.DoModal() == IDOK )
	{
		m_IFDX.SetLAmount( m_dlgDispenseStart.m_lAmount );

		CString str;
		str.Format( "SetLAmount(%d)\n", m_IFDX.GetLAmount() ); AddStrToSendEdit( LPCTSTR(str) );

		m_IFDX.SetLReadDispense(0);		// set to "Write Operation"
		if( m_IFDX.SendDispenseAmount() )
			AddStrToSendEdit( "->SendDispenseAmount(): Write OK\n" );
		else
			AddStrToSendEdit( "->SendDispenseAmount(): Write Error\n" );
	}		
}

void CIFDView::OnButtonSendStart() 
{ 
	CString str;



	//str.Format( " count = %d\n",m_editReceive.GetWindowTextLength() );
	AddStrToSendEdit( LPCTSTR(str) );

	if(m_editReceive.GetWindowTextLength() > 40000)
	{
		m_editReceive.SetWindowText(_T(""));

	}
	else if(m_editSend.GetWindowTextLength() > 30000)
	{
		m_editSend.SetWindowText(_T(""));
	}
	//m_IFDX.
	if( m_IFDX.SendStart() )
		AddStrToSendEdit( "->SendStart() OK\n" );
	else
		AddStrToSendEdit( "->SendStart() Error\n" );
	
}

void CIFDView::OnButtonSendClear() 
{
	switch( m_comboClear.GetCurSel() )
	{
	case 0:
		AddStrToSendEdit( "SendTotalClear()\n" );
		m_IFDX.SendTotalClear();
		break;
	case 1:
		AddStrToSendEdit( "SendJAMClear()\n" );
		m_IFDX.SendJAMClear();
		break;
	case 2:
		AddStrToSendEdit( "SendStackerPoketClear()\n" );
		m_IFDX.SendStackerPoketClear();
		break;
	case 3:
		AddStrToSendEdit( "SendRejectPocketClear()\n" );
		m_IFDX.SendRejectPocketClear();
		break;
	case 4:
		AddStrToSendEdit( "SendMixedModeGrandTotalClear()\n" );
		m_IFDX.SendMixedModeGrandTotalClear();
		break;
	case 5:
		AddStrToSendEdit( "SendSimpleModeGrandTotalClear()\n" );
		m_IFDX.SendSimpleModeGrandTotalClear();
		break;
	case 6:
		AddStrToSendEdit( "SendCountingReportClear()\n" );
		m_IFDX.SendCountingReportClear();
		break;
	}	
}

void CIFDView::OnButtonSendRequest() 
{
	switch( m_comboRequest.GetCurSel() )
	{
	case 0:
		AddStrToSendEdit( "SendSetupStatusDataRequest()\n" );
		m_IFDX.SendSetupStatusDataRequest();
		break;
	case 1:
		AddStrToSendEdit( "SendCountingResultRequest()\n" );
		m_IFDX.SendCountingResultRequest();
		break;
	case 2:
		AddStrToSendEdit( "SendErrorStateRequest()\n" );
		m_IFDX.SendErrorStateRequest();
		break;
	case 3:
		AddStrToSendEdit( "SendResendingRequest()\n" );
		m_IFDX.SendResendingRequest();

		break;
	case 4:
		AddStrToSendEdit( "SendSensorStackerStatusRequest()\n" );
		m_IFDX.SendSensorStackerStatusRequest();
		break;
	case 5:
		AddStrToSendEdit( "SendSetupStatusData2Request()\n" );
		m_IFDX.SendSetupStatusData2Request();
		break;
	case 6:
		AddStrToSendEdit( "SendDeviceStatus2DataRequest()\n" );
		m_IFDX.SendDeviceStatus2DataRequest();
		break;
	case 7:
		AddStrToSendEdit( "SendSend_Request_Err()\n" );
		m_IFDX.Send_Request_Err();
		break;
	case 8:
		AddStrToSendEdit( "SendCountingReportRequest()\n" );
		m_IFDX.SendCountingReportRequest();
		break;
	case 9:
		AddStrToSendEdit( "SendSwVersionRequest()\n" );
		m_IFDX.SendSwVersionRequest();
		break;

	}	
}

void CIFDView::OnCommportConnect() 
{
	if( m_IFDX.CommPortOpen() )
		m_bCommPortConnected = true;
	
}

void CIFDView::OnUpdateCommportConnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( !m_bCommPortConnected );
	
}

void CIFDView::OnCommportDisconnect() 
{
	if( m_bCommPortConnected )
	{
		m_IFDX.CommPortClose();
		m_bCommPortConnected = false;
	}
	
}

void CIFDView::OnUpdateCommportDisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable( m_bCommPortConnected );
	
}

BEGIN_EVENTSINK_MAP(CIFDView, CFormView)
    //{{AFX_EVENTSINK_MAP(CIFDView)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 11 /* MSG_BYTE_COUNT_DATA */, OnByteCountDataIfdxctrl, VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 6 /* MSG_CD_ERROR */, OnCdErrorIfdxctrl, VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 4 /* MSG_COUNT_START */, OnCountStartIfdxctrl, VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 5 /* MSG_COUNT_STOP */, OnCountStopIfdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 2 /* MSG_DEVICE_SET_LIVE */, OnDeviceSetLiveIfdxctrl, VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 8 /* MSG_DEVICE_SETUP2 */, OnDeviceSetup2Ifdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 12 /* MSG_RESULT_DENOM */, OnResultDenomIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 13 /* MSG_RESULT_PRE_DENOM */, OnResultPreDenomIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 10 /* MSG_SENSOR_STATUS */, OnSensorStatusIfdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 9 /* MSG_SETUP_NO_ACCEPT */, OnSetupNoAcceptIfdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 3 /* MSG_SETUP_STATE_DATA */, OnSetupStateDataIfdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 19 /* MSG_SETUP_STATE_DATA2 */, OnSetupStateData2Ifdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 14 /* MSG_DISPENSE_AMOUNT */, OnDispenseAmountIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 15 /* MSG_DISPENSE_MATCH_AMOUNT */, OnDispenseMatchAmountIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 16 /* MSG_OCR */, OnOcrIfdxctrl, VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 17 /* MSG_MULTI_BATCH */, OnMultiBatchIfdxctrl, VTS_PI4 VTS_PI4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 18 /* MSG_MULTI_BATCH_MATCH */, OnMultiBatchMatchIfdxctrl, VTS_PI4 VTS_PI4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 20 /* MSG_BARCODE */, OnBarCodeIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 25 /* MSG_SETUP_STATE_DATA_EX */, OnSetupStateDataExIfdxctrl, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 27 /* eventidMSG_IR_ERR_REQUEST */, OnCheckIR, VTS_NONE)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 26 /* eventidMSG_COUNTING_REPORT_DATA */, OnCountingReportDataIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 28 /* eventidMSG_MC_STATUS */, OnMC_StatusIfdxctrl, VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 29 /* eventidMSG_SW_VERSION */, OnSwVersionIfdxctrl, VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 30 /* eventidMSG_OCR_RESULT */, OnOcrResultIfdxctrl, VTS_PI1)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 31 /* eventidMSG_IFD_RESULT_PROFIS */, OnRdResultProfisIfdxctrl, VTS_I8 VTS_I8 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 32 /* eventidMSG_MAINTENANCE_VALUE */, OnAsAlarmValueIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 33 /* MSG_RESULT_VALUE_COUNT */, OnResultValueCountIfdxctrl, VTS_I4 VTS_I4)
	ON_EVENT(CIFDView, IDC_IFDX_SB7CTRL, 34 /* eventidMSG_DATE_TIME_VALUE */, OnSetDateTimeIfdxctrl, VTS_I4 VTS_I4 VTS_I4)
	
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CIFDView::OnByteCountDataIfdxctrl(long lData) 
{
	CString str;

	str.Format( "MSG_BYTE_COUNT_DATA : %2d\n", (unsigned char)lData );
	AddStrToReceiveEdit( LPCTSTR(str) );
	
}

void CIFDView::OnCdErrorIfdxctrl(long lErrorCode) 
{
	// bit 0 == 1 : JAM Error
	// bit 1 == 1 : Feeding Error
	
	if( lErrorCode == 0 )
	{
		AddStrToReceiveEdit( "MSG_CD_ERROR : NO Error\n" );
	}
	else if( lErrorCode == 4 )
	{
		AddStrToReceiveEdit( "MSG_CD_ERROR : USER STOP\n" );
	}
	else if( lErrorCode == 8 )
	{
		AddStrToReceiveEdit( "MSG_CD_ERROR : Feed Motor Error\n" );
	}
	else if( lErrorCode == 3 )
	{
		AddStrToReceiveEdit( "MSG_CD_ERROR : Main Motor Error\n" );
	}
	else
	{
		if( lErrorCode % 2 )
			AddStrToReceiveEdit( "MSG_CD_ERROR : JAM Error\n" );
		if( lErrorCode / 2 )
			AddStrToReceiveEdit( "MSG_CD_ERROR : Feeding Error\n" );
	}
	
}

void CIFDView::OnCountStartIfdxctrl(long lNewDeposit) 
{
	// bit 1 == 1 : NEW Deposit
	if( lNewDeposit / 2 )
		AddStrToReceiveEdit( "MSG_COUNT_START : New Deposit\n" );
	else
		AddStrToReceiveEdit( "MSG_COUNT_START\n" );
}

void CIFDView::OnCountStopIfdxctrl() 
{
	AddStrToReceiveEdit( "MSG_COUNT_STOP\n" );
	
}

void CIFDView::OnDeviceSetLiveIfdxctrl(long bLive) 
{
	TRACE( "MSG_DEVICE_SET_LIVE : bLive = %d\n", bLive );
	if( bLive == 1 )
	{
		AddStrToReceiveEdit( "MSG_DEVICE_SET_LIVE : KNOCK\n" );
		m_IFDX.SendDeviceSetLive( 2 ); // send ACK
	}
	else // bLive == 2;
	{
		AddStrToReceiveEdit( "MSG_DEVICE_SET_LIVE : ACK\n" );
		m_IFDX.SendSetupStatusData2Request();
    }

	CWnd *pWnd = GetDlgItem( IDC_STATIC_DEVICE_ALIVE );
	pWnd->ShowWindow( SW_SHOW );
	pWnd = GetDlgItem( IDC_STATIC_DEVICE_NOTALIVE );
	pWnd->ShowWindow( SW_HIDE );
	
}

void CIFDView::OnDeviceSetup2Ifdxctrl(long lByteCountingEnable, long lLocKeyPad) 
{
	AddStrToReceiveEdit( "MSG_DEVICE_SETUP2\n" );

	if( lByteCountingEnable )
		AddStrToReceiveEdit( "  - Byte Counting Enable\n" );
	else
		AddStrToReceiveEdit( "  - Byte Counting Disable\n" );

	if( lLocKeyPad )
		AddStrToReceiveEdit( "  - Keypad Lock\n" );
	else
		AddStrToReceiveEdit( "  - KeyPad Released\n" );
	
}

void CIFDView::OnResultDenomIfdxctrl(long lDenomNumber, long lCount) 
{
	CString str;
	AddStrToReceiveEdit( "MSG_RESULT_DENOM\n" );

	if( lDenomNumber == 101 )
	{
		str.Format( "  - Reject Pocket : %3d\n", lCount );
		AddStrToReceiveEdit( LPCTSTR(str) );
	}
	else if( lDenomNumber == 102 )
	{
		str.Format( "  - Stack Pocket : %3d\n", lCount );
		AddStrToReceiveEdit( LPCTSTR(str) );
	}
	else if( lDenomNumber == 103 )
	{
		str.Format( "  - Num of CF : %3d\n", lCount );
		AddStrToReceiveEdit( LPCTSTR(str) );
	}
	else if(lDenomNumber == 105)
	{
		str.Format( "  - Currency code : %3d\n", lCount );
		AddStrToReceiveEdit( LPCTSTR(str) );
	}
	else
	{
		str.Format( "  - lDenomNumber %d : %3d\n", lDenomNumber, lCount );
		AddStrToReceiveEdit( LPCTSTR(str) );
	}	
}


void CIFDView::OnResultPreDenomIfdxctrl(long lDenomNumber, long lCount) 
{
	CString str;

	AddStrToReceiveEdit( "MSG_RESULT_PRE_DENOM\n" );

	str.Format( "  - lDenomNumber %d : %3d\n", lDenomNumber, lCount );
	AddStrToReceiveEdit( LPCTSTR(str) );
	
}

void CIFDView::OnResultValueCountIfdxctrl(unsigned long lValue, unsigned short lCount) 
{
	CString str;

	AddStrToReceiveEdit( "MSG_RESULT_VALUE_COUNT\n" );

	str.Format( "  - lValue %d : %3d\n", lValue, lCount );
	AddStrToReceiveEdit( LPCTSTR(str) );
	
}
void CIFDView::OnSensorStatusIfdxctrl() 
{
	CString str, sub;
	CString On = "On\n", Off = "Off\n";
	CString Open = "Opened\n", Close = "Closed\n";

	AddStrToReceiveEdit( "MSG_SENSOR_STATUS\n" );

	sub = m_IFDX.GetLRP1_Left() ? On : Off;
	str = "  - RP1 Left : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLRP1_Right() ? On : Off;
	str = "  - RP1 Right : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	//sub = m_IFDX.GetLRP2_Left() ? On : Off;
	//str = "  - RP2 Left " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	//sub = m_IFDX.GetLRP2_Right() ? On : Off;
	//str = "  - RP2 Right " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLJP_Left() ? On : Off;
	str = "  - JP Left : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLJP_Right() ? On : Off;
	str = "  - JP Right : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLSP_Left() ? On : Off;
	str = "  - SP Left : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLSP_Right() ? On : Off;
	str = "  - SP Right : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLStacker() ? On : Off;
	str = "  - Stacker : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLRejecter() ? On : Off;
	str = "  - Rejecter Front : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLRejecterRear() ? On : Off;
	str = "  - Rejecter Rear : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLFrontCover() ? Open : Close;
	str = "  - Front cover : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
	sub = m_IFDX.GetLRearCover() ? Open : Close;
	str = "  - Rear cover : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLHopper() ? "bank notes\n" :"no bank note on hopper\n";
	str = "  - Hopper " + sub; AddStrToReceiveEdit( LPCTSTR(str) );

#if 0
	str.Format("  - Reject Pocket : %d\n", m_IFDX.GetLNumRejPocket()); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format("  - Stacker Pocket : %d\n", m_IFDX.GetLNumStkPocket()); AddStrToReceiveEdit( LPCTSTR(str) );
#endif //0

	switch( m_IFDX.GetLErrorStatus() )
	{
	case 0:
		sub = "NO Error\n";
		break;
	case 1:
		sub = "JAM1 Error\n";
		break;
	case 2:
		sub = "JAM2 Error\n";
		break;
	case 3:
		sub = "JAM3 Error\n";
		break;
	case 4:
		sub = "JAM4 Error\n";
		break;
	case 5:
		sub = "Feeding Error\n";
		break;
	case 6:
		sub = "Front cover open Error\n";
		break;
	case 7:
		sub = "Rear cover open Error\n";
		break;
	case 8:
		sub = "Feed Motor Error\n";
		break;
	case 9:
		sub = "Main Motor Error\n";
		break;
	}

	str = "  - Error Status : " + sub; AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnSetupNoAcceptIfdxctrl() 
{
	AddStrToReceiveEdit( "MSG_SETUP_NO_ACCEPT\n" );
	
}

void CIFDView::OnSetupStateDataIfdxctrl() 
{
	CString str, sub;

	AddStrToReceiveEdit( "MSG_SETUP_STATE_DATA\n" );

	switch( m_IFDX.GetLSpeed() )
	{
	case 0:
		str.Format( "  - Motor Speed = %4d rpm\n", 1000 ); break;
	case 1:
		str.Format( "  - Motor Speed = %4d rpm\n", 1200 ); break;
	case 2:
		str.Format( "  - Motor Speed = %4d rpm\n", 1500 ); break;
	}
	AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLBatchOn() ? "On" : "Off";
	str.Format( "  - Batch %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

//	sub = m_IFDX.GetLPrintType() ? "Parallel" : "Serial";
//    str.Format( "  - Print Type %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLBeepEnable() ? "Enable" : "Disable";
	str.Format( "  - warning beep %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLAuto() ? "Auto" : "Manual";
	str.Format( "  - auto/manual : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLADDOn() ? "On" : "Off";
    str.Format( "  - ADD %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLUVOn() ? "On" : "Off";
	str.Format( "  - UV Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLMROn() ? "On" : "Off";
	str.Format( "  - MR Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLModeLockOn() ? "On" : "Off";
	str.Format( "  - Mode Lock %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	{
		LONG lCurrencyCode;
		
		if( m_IFDX.GetLCurrencyCode() > MAX_CURRENCY )
			lCurrencyCode = 1;
		else
			lCurrencyCode = m_IFDX.GetLCurrencyCode();
		
		sub = gpaCurrencyName[lCurrencyCode];
	}

	str.Format( "  - Currency Code : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - denomination value : %d\n", m_IFDX.GetLDenom() ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLCountMode() )
	{
	case 0 : sub = "COUNT mode"; break;
	case 1 : sub = "MIXED mode"; break;
	case 2 : sub = "SINGLE mode"; break;
	case 3 : sub = "FACE mode"; break;
	case 4 : sub = "ORIENT mode"; break;
	case 6 : sub = "ISSUE mode"; break;
	}
	str.Format( "  - counting mode : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLRejPocketCap() )
	{
	case 0: sub = "30 PCS\n"; break;
	case 1: sub = "20 PCS\n"; break;
	case 2: sub = "10 PCS\n"; break;
	}
	str.Format( "  - Reject Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLStkPocketCap() )
	{
	case 0: sub = "200 PCS\n"; break;
	case 1: sub = "150 PCS\n"; break;
	case 2: sub = "100 PCS\n"; break;
	}
	str.Format( "  - Stacker Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Batch Counter Number : %d\n", m_IFDX.GetLBatchCountNum() ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLMRSensitive() )
	{
	case 0: sub = "HIGH\n"; break;
	case 1: sub = "MEDIUM\n"; break;
	case 2: sub = "LOW\n"; break;
	}
	str.Format( "  - MR sensitivity : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );	
}

void CIFDView::OnSetupStateData2Ifdxctrl() 
{
	CString str, sub;

	AddStrToReceiveEdit( "MSG_SETUP_STATE_DATA\n" );

	switch( m_IFDX.GetLSpeed() )
	{
	case 0:
		str.Format( "  - Motor Speed = %4d rpm\n", 1000 ); break;
	case 1:
		str.Format( "  - Motor Speed = %4d rpm\n", 1200 ); break;
	case 2:
		str.Format( "  - Motor Speed = %4d rpm\n", 1500 ); break;
	}
	AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLBatchOn() ? "On" : "Off";
	str.Format( "  - Batch %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );


	sub = m_IFDX.GetLBeepEnable() ? "Enable" : "Disable";
	str.Format( "  - warning beep %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLAuto() ? "Auto" : "Manual";
	str.Format( "  - auto/manual : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLADDOn() ? "On" : "Off";
    str.Format( "  - ADD %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLUVOn() ? "On" : "Off";
	str.Format( "  - UV Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLMROn() ? "On" : "Off";
	str.Format( "  - MR Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLIROn() ? "On" : "Off";
	str.Format( "  - IR Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLModeLockOn() ? "On" : "Off";
	str.Format( "  - Mode Lock %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	{
		LONG lCurrencyCode;
		
		if( m_IFDX.GetLCurrencyCode() > MAX_CURRENCY )
			lCurrencyCode = 1;
		else
			lCurrencyCode = m_IFDX.GetLCurrencyCode();
		
		sub = gpaCurrencyName[lCurrencyCode];
	}

	str.Format( "  - Currency Code : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - denomination value : %d\n", m_IFDX.GetLDenom() ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLCountMode() )
	{
	case 0 : sub = "COUNT mode"; break;
	case 1 : sub = "MIXED mode"; break;
	case 2 : sub = "SINGLE mode"; break;
	case 3 : sub = "FACE mode"; break;
	case 4 : sub = "ORIENT mode"; break;
	case 5 : sub = "RESERVED mode"; break;
	case 6 : sub = "ISSUE mode"; break;
	case 7 : sub = "RESERVED mode"; break;
	case 8 : sub = "SERIAL mode"; break;
	case 9 : sub = "MIXED CURR mode"; break;
	}
	str.Format( "  - counting mode : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLRejPocketCap() )
	{
	case 0: sub = "30 PCS\n"; break;
	case 1: sub = "20 PCS\n"; break;
	case 2: sub = "10 PCS\n"; break;
	}
	str.Format( "  - Reject Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLStkPocketCap() )
	{
	case 0: sub = "200 PCS\n"; break;
	case 1: sub = "150 PCS\n"; break;
	case 2: sub = "100 PCS\n"; break;
	}
	str.Format( "  - Stacker Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - Batch Counter Number : %d\n", m_IFDX.GetLBatchCountNum() ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - UV LEVEL : %d\n", m_IFDX.GetLUVLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - MR LEVEL : %d\n", m_IFDX.GetLMRLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - IR LEVEL : %d\n", m_IFDX.GetLIRLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
}

//void CIFDView::OnDispenseStartIfdxctrl(long lAmount, long lCount)
//{
//	CString str;
//	str.Format( "  - Dispense, amount  : %d\n", lAmount ); AddStrToReceiveEdit( LPCTSTR(str) );	
//}

void CIFDView::OnMC_StatusIfdxctrl(long lMC_StatusCode) 
{
	// bit 0 == 1 : CLEAR HOPPER
	// bit 1 == 1 : Rev.1
	
	if( lMC_StatusCode == 1 )
	{
		AddStrToReceiveEdit( "MSG_CLEAR_HOPPER\n" );
	}
}


void CIFDView::AddStrToSendEdit( const char *pStr )
{
	int i, j;
	char pBuf[128];

	for( i = 0, j = 0; pStr[i] != 0; i++ )
	{
		if( pStr[i] == 0x0a )
			pBuf[j++] = 0x0d;

		pBuf[j++] = pStr[i];
	}
	pBuf[j] = 0;

	m_editSend.SetSel(0, -1); 
	m_editSend.SetSel(-1,-1);
	m_editSend.ReplaceSel( pBuf );
}

void CIFDView::AddStrToReceiveEdit( const char *pStr )
{
	int i, j;
	char pBuf[128];

	for( i = 0, j = 0; pStr[i] != 0; i++ )
	{
		if( pStr[i] == 0x0a )
			pBuf[j++] = 0x0d;

		pBuf[j++] = pStr[i];
	}
	pBuf[j] = 0;

	m_editReceive.SetSel(0, -1); 
	m_editReceive.SetSel(-1,-1);
	m_editReceive.ReplaceSel( pBuf );
}




void CIFDView::OnDispenseAmountIfdxctrl(long lAmount, long lCount) 
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Format( "  - Dispense, Setting Amount  : %d\n", lAmount ); AddStrToReceiveEdit( LPCTSTR(str) );	
	str.Format( "  - Dispense, current Amount  : %d\n", lCount ); AddStrToReceiveEdit( LPCTSTR(str) );	
}

void CIFDView::OnDispenseMatchAmountIfdxctrl(long lAmount, long lCount) 
{
	// TODO: Add your control notification handler code here
	CString str;
	str.Format( "  - Dispense, match Amount!!!  : %d\n", lAmount ); AddStrToReceiveEdit( LPCTSTR(str) );	
}

void CIFDView::OnOcrIfdxctrl(long lTotal_Index, long strOCR, long lDenom) 
{
	// TODO: Add your control notification handler code here
	CString str;
	int iTotal;
	int iCurIndex;
	char *pStr;
	CString sDenom;
	int CurrencyCode;

	iTotal = (lTotal_Index>>16) & 0xffff;
	iCurIndex = (lTotal_Index) & 0xffff;
	pStr = (char*)strOCR;
	TRACE("%X\n", lTotal_Index);

	CurrencyCode = m_IFDX.GetLCurrencyCode();
	if (CurrencyCode == CUR_USD)
	{
		if (lDenom < (sizeof(gpaUSD_Denom)/sizeof(char*)) )
			sDenom = gpaUSD_Denom[lDenom];
		else
			sDenom = "";
	}
	else if (CurrencyCode == CUR_EURO)
	{
		if (lDenom < (sizeof(gpaUSD_Denom)/sizeof(char*)) )
			sDenom = gpaEURO_Denom[lDenom];
		else
			sDenom = "";
	}
	else if (CurrencyCode == CUR_LIRA)
	{
		if (lDenom < (sizeof(gpaUSD_Denom)/sizeof(char*)) )
			sDenom = gpaYTL_Denom[lDenom]; 
		else
			sDenom = "";
	}
	else 
		sDenom = "";

	str.Format( "OCR: %3d/%3d : (%4s)\t%s\n", iCurIndex, iTotal, sDenom, pStr);
	AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnBarCodeIfdxctrl(long lTotal_Index, long strBARCODE) 
{
	// TODO: Add your control notification handler code here
	CString str;
	int iTotal;
	int iCurIndex;
	char *pStr;
	CString sDenom;
	int CurrencyCode;

	iTotal = (lTotal_Index>>16) & 0xffff;
	iCurIndex = (lTotal_Index) & 0xffff;
	pStr = (char*)strBARCODE;
	TRACE("%X\n", lTotal_Index);

	str.Format( "BARCODE: %3d/%3d : %s\n", iCurIndex, iTotal, pStr);
	AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnButtonOcr() 
{
	// TODO: Add your control notification handler code here
	AddStrToSendEdit( "SendSerialOCRRequest()\n" );
	m_IFDX.SendSerialOCRRequest();
}

void CIFDView::OnButtonMultiBatch() 
{
	// TODO: Add your control notification handler code here
	if (m_dlgMultiBatch.DoModal() == IDOK)
	{
		CString str;
		str.Format( "SetMultiBatchDenom:\n" );	AddStrToReceiveEdit( LPCTSTR(str) );
		str.Format( " $1(%d) $2(%d) $5(%d) $10(%d) $20(%d) $50(%d) $100(%d)\n",					\
			m_dlgMultiBatch.m_iDenom0, m_dlgMultiBatch.m_iDenom1, m_dlgMultiBatch.m_iDenom2,	\
			m_dlgMultiBatch.m_iDenom3, m_dlgMultiBatch.m_iDenom4, m_dlgMultiBatch.m_iDenom5,	\
			m_dlgMultiBatch.m_iDenom6 );	AddStrToReceiveEdit( LPCTSTR(str) );

		LONG laMultiBatchSet[40];
		LONG laCurDenomCnt[40] = {0, };

		laMultiBatchSet[0] = m_dlgMultiBatch.m_iDenom0;
		laMultiBatchSet[1] = m_dlgMultiBatch.m_iDenom1;
		laMultiBatchSet[2] = m_dlgMultiBatch.m_iDenom2;
		laMultiBatchSet[3] = m_dlgMultiBatch.m_iDenom3;
		laMultiBatchSet[4] = m_dlgMultiBatch.m_iDenom4;
		laMultiBatchSet[5] = m_dlgMultiBatch.m_iDenom5;
		laMultiBatchSet[6] = m_dlgMultiBatch.m_iDenom6;
		if( m_IFDX.SetMultiBatchDenom(7, laMultiBatchSet, laCurDenomCnt) )
			AddStrToSendEdit( "->SetMultiBatchDenom(): Write OK\n" );
		else
			AddStrToSendEdit( "->SetMultiBatchDenom(): Write Error\n" );
	}
/*
	if( m_dlgDispenseStart.DoModal() == IDOK )
	{
		m_IFDX.SetLAmount( m_dlgDispenseStart.m_lAmount );

		CString str;
		str.Format( "SetLAmount(%d)\n", m_IFDX.GetLAmount() ); AddStrToSendEdit( LPCTSTR(str) );

		m_IFDX.SetLReadDispense(0);		// set to "Write Operation"
		if( m_IFDX.SendDispenseAmount() )
			AddStrToSendEdit( "->SendDispenseAmount(): Write OK\n" );
		else
			AddStrToSendEdit( "->SendDispenseAmount(): Write Error\n" );
	}		
*/	
}

void CIFDView::OnMultiBatchIfdxctrl(long FAR* lpMultiBatchSet, long FAR* lpCurDenomCnt) 
{
	// TODO: Add your control notification handler code here
	CString str;
	int i, B[40];

	str.Format( "  - Read Multi Batch Denom  :\n"); AddStrToReceiveEdit( LPCTSTR(str) );	

	for (i = 0; i < 7; i++) B[i] = lpMultiBatchSet[i];
	str.Format( " -Set: $1(%d) $2(%d) $5(%d) $10(%d) $20(%d) $50(%d) $100(%d)\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6]); AddStrToReceiveEdit( LPCTSTR(str) );	

	for (i = 0; i < 7; i++) B[i] = lpCurDenomCnt[i];
	str.Format( " -Cnt: $1(%d) $2(%d) $5(%d) $10(%d) $20(%d) $50(%d) $100(%d)\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6]); AddStrToReceiveEdit( LPCTSTR(str) );	
}

void CIFDView::OnMultiBatchMatchIfdxctrl(long FAR* lpMultiBatchSet, long FAR* lpCurDenomCnt) 
{
	// TODO: Add your control notification handler code here
	CString str;
	int i, B[40];
	str.Format( "  - Multi Batch match Denom!!!  :\n"); AddStrToReceiveEdit( LPCTSTR(str) );	

	for (i = 0; i < 7; i++) B[i] = lpMultiBatchSet[i];
	str.Format( " -Set: $1(%d) $2(%d) $5(%d) $10(%d) $20(%d) $50(%d) $100(%d)\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6]); AddStrToReceiveEdit( LPCTSTR(str) );	

	for (i = 0; i < 7; i++) B[i] = lpCurDenomCnt[i];
	str.Format( " -Cnt: $1(%d) $2(%d) $5(%d) $10(%d) $20(%d) $50(%d) $100(%d)\n", B[0], B[1], B[2], B[3], B[4], B[5], B[6]); AddStrToReceiveEdit( LPCTSTR(str) );	
}

void CIFDView::OnButtonDeviceSetupStateData2() 
{
	// TODO: Add your control notification handler code here
	m_dlgSetupStateData2.m_bAddon	= (BOOL)m_IFDX.GetLADDOn();
	m_dlgSetupStateData2.m_bBatch	= (BOOL)m_IFDX.GetLBatchOn();
	m_dlgSetupStateData2.m_bBeep = (BOOL)m_IFDX.GetLBeepEnable();
	m_dlgSetupStateData2.m_bAuto		= (BOOL)m_IFDX.GetLAuto();
	m_dlgSetupStateData2.m_bUVOn		= (BOOL)m_IFDX.GetLUVOn();
	m_dlgSetupStateData2.m_bMROn		= (BOOL)m_IFDX.GetLMROn();
	m_dlgSetupStateData2.m_bIROn		= (BOOL)m_IFDX.GetLIROn();
	m_dlgSetupStateData2.m_bModeLock = (BOOL)m_IFDX.GetLModeLockOn();
	m_dlgSetupStateData2.m_lBatchCnt = (BYTE)m_IFDX.GetLBatchCountNum();
	m_dlgSetupStateData2.m_lUVLevel = (BYTE)m_IFDX.GetLUVLevel();
	m_dlgSetupStateData2.m_lMRLevel = (BYTE)m_IFDX.GetLMRLevel();
	m_dlgSetupStateData2.m_lIRLevel = (BYTE)m_IFDX.GetLIRLevel();

	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_COUNT_MODE]	  = (BYTE)m_IFDX.GetLCountMode();
	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_REJECT_POCKET] = (BYTE)m_IFDX.GetLRejPocketCap();
	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_STACK_POCKET]  = (BYTE)m_IFDX.GetLStkPocketCap();
	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_PRINTER_TYPE]  = (BYTE)m_IFDX.GetLPrintType();
	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_CURRENCY_CODE] = (BYTE)(m_IFDX.GetLCurrencyCode() - 1);

	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_DENOM] = (BYTE)m_IFDX.GetLDenom();

	if(m_dlgSetupStateData2.m_lBatchCnt == 0)
		m_dlgSetupStateData2.m_lBatchCnt = 10;

	if( m_dlgSetupStateData2.DoModal() == IDOK )
	{
		m_IFDX.SetLADDOn( m_dlgSetupStateData2.m_bAddon );
		m_IFDX.SetLBatchOn( m_dlgSetupStateData2.m_bBatch );
		m_IFDX.SetLBeepEnable( m_dlgSetupStateData2.m_bBeep );
		m_IFDX.SetLAuto( m_dlgSetupStateData2.m_bAuto );
		m_IFDX.SetLUVOn( m_dlgSetupStateData2.m_bUVOn );
		m_IFDX.SetLMROn( m_dlgSetupStateData2.m_bMROn );
		m_IFDX.SetLIROn( m_dlgSetupStateData2.m_bIROn );
		m_IFDX.SetLModeLockOn( m_dlgSetupStateData2.m_bModeLock );
		m_IFDX.SetLCountMode( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_COUNT_MODE] );
		m_IFDX.SetLRejPocketCap( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_REJECT_POCKET] );
		m_IFDX.SetLStkPocketCap( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_STACK_POCKET] );
		m_IFDX.SetLPrintType( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_PRINTER_TYPE] );
		m_IFDX.SetLBatchCountNum( m_dlgSetupStateData2.m_lBatchCnt );
		m_IFDX.SetLUVLevel( m_dlgSetupStateData2.m_lUVLevel );
		m_IFDX.SetLMRLevel( m_dlgSetupStateData2.m_lMRLevel );
		m_IFDX.SetLIRLevel( m_dlgSetupStateData2.m_lIRLevel );

		if(	m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_DENOM] == (m_iNumDenom-1))
		{
			m_IFDX.SetLDenom( 31 ); // DD
		}
		else
		{
			m_IFDX.SetLDenom( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_DENOM] );
		}

		m_IFDX.SetLCurrencyCode( m_dlgSetupStateData2.m_baSelect[ENUM_SETUP_CURRENCY_CODE] + 1 );

		CString str;

		str.Format( "SetLADDOn(%d)\n", m_IFDX.GetLADDOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchOn(%d)\n", m_IFDX.GetLBatchOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBeepEnable(%d)\n", m_IFDX.GetLBeepEnable() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLAuto(%d)\n", m_IFDX.GetLAuto() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLUVOn(%d)\n", m_IFDX.GetLUVOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMROn(%d)\n", m_IFDX.GetLMROn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLIROn(%d)\n", m_IFDX.GetLIROn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLModeLockOn(%d)\n", m_IFDX.GetLModeLockOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCountMode(%d)\n", m_IFDX.GetLCountMode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLDenom(%d)\n", m_IFDX.GetLDenom() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLRejPocketCap(%d)\n", m_IFDX.GetLRejPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLStkPocketCap(%d)\n", m_IFDX.GetLStkPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLPrintType(%d)\n", m_IFDX.GetLPrintType() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCurrencyCode(%d)\n", m_IFDX.GetLCurrencyCode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchCountNum(%d)\n", m_IFDX.GetLBatchCountNum() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLUVLevel(%d)\n", m_IFDX.GetLUVLevel() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMRLevel(%d)\n", m_IFDX.GetLMRLevel() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLIRLevel(%d)\n", m_IFDX.GetLIRLevel() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetupStateData2() )
			AddStrToSendEdit( "->SendSetupStateData2() OK\n" );
		else
			AddStrToSendEdit( "->SendSetupStateData2() Error\n" );
	}		
}

void CIFDView::OnButtonBarcode() 
{
	// TODO: Add your control notification handler code here
	AddStrToSendEdit( "SendBarCodeRequest()\n" );
	m_IFDX.SendBarCodeRequest();
}



void CIFDView::OnButtonSendStop()
{
	if( m_IFDX.SendStop() )
		AddStrToSendEdit( "->Send Stop() OK\n" );
	else
		AddStrToSendEdit( "->Send Stop() Error\n" );
}

void CIFDView::OnTcpConnect()
{
	m_IFDX.SocketOpen();
	m_bCommPortConnected = false;
}

void CIFDView::OnTcpDisconnect()
{
	
	m_IFDX.SocketClose();
}

void CIFDView::OnUpdateTcpConnect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(!m_IFDX.IsSocketConnect());
}

void CIFDView::OnUpdateTcpDisconnect(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_IFDX.IsSocketConnect());
}



void CIFDView::OnBnClickedSendCancelStart()
{
	if( m_IFDX.SendCancelStart() )
		AddStrToSendEdit( "->Send Cancel() OK\n" );
	else
		AddStrToSendEdit( "->Send Cancel() Error\n" );
}

void CIFDView::OnBnClickedReboot()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if( m_IFDX.SendREBOOT() )
		AddStrToSendEdit( "->Send Reboot() OK\n" );
	else
		AddStrToSendEdit( "->Send Reboot() Error\n" );
}

void CIFDView::OnCheckIR(void)
{
	if(m_IFDX.GetLIrErr())
		AddStrToReceiveEdit( "->IR SENSOR ERROR \n" );
	else 
		AddStrToReceiveEdit( "->IR SENSOR OK\n" );
}

void CIFDView::OnBnClickedButtonSaveBmpToUsb()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//m_IFDX.
	if( m_IFDX.SendSaveBMPtoUSB_ON() )
		AddStrToSendEdit( "->SendSaveBMPtoUSB_ON() OK\n" );
	else
		AddStrToSendEdit( "->SendSaveBMPtoUSB_ON() Error\n" );
}

void CIFDView::OnCountingReportDataIfdxctrl(long lTotal_StackerCount, long lTotal_RejectorCount)
{
	CString str;

	AddStrToReceiveEdit( "COUNTING_REPORT\n" );
	str.Format( " - Total Counting Stacker : %d\n", lTotal_StackerCount); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( " - Total Counting Rejector : %d\n",lTotal_RejectorCount); AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnSwVersionIfdxctrl(long lSwVerUpper, long lSwVerLower, long lChksumUpper, long lChksumLower)
{
	CString str;

	str.Format( " - SW Version : %02d.%02d\n", lSwVerUpper, lSwVerLower); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( " - Check sum  : %02x%02x\n", lChksumUpper, lChksumLower); AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnOcrResultIfdxctrl(char * pBuf)
{
	CString str;

	AddStrToReceiveEdit( "OCR_RESULT\n" );

	str.Format("%s\n", pBuf);
	AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnBnClickedButtonSaveBmpToUsb2()
{
	//m_IFDX.
	if( m_IFDX.SendSaveBMPtoUSB_OFF() )
		AddStrToSendEdit( "->SendSaveBMPtoUSB_OFF() OK\n" );
	else
		AddStrToSendEdit( "->SendSaveBMPtoUSB_OFF() Error\n" );
}

void CIFDView::OnBnClickedButtonWingMotorStart()
{
	//m_IFDX.
	if( m_IFDX.SendWingMotor_Start() )
		AddStrToSendEdit( "->SendWingMotor_Start() OK\n" );
	else
		AddStrToSendEdit( "->SendWingMotor_Start() Error\n" );
}
void CIFDView::OnBnClickedButtonWingMotorStop()
{
	//m_IFDX.
	if( m_IFDX.SendWingMotor_Stop() )
		AddStrToSendEdit( "->SendWingMotor_Stop() OK\n" );
	else
		AddStrToSendEdit( "->SendWingMotor_Stop() Error\n" );
}


void CIFDView::OnBnClickedButtSetRefNo()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dlgSetRefNumber.m_llRefNo	= m_IFDX.GetLLRefNo();

	if( m_dlgSetRefNumber.DoModal() == IDOK )
	{
		m_IFDX.SetLLRefNo( m_dlgSetRefNumber.m_llRefNo );

		CString str;
		m_dlgSetRefNumber.m_llRefNo = m_IFDX.GetLLRefNo();

		str.Format( "SetLRefNo(%lld)\n", m_dlgSetRefNumber.m_llRefNo ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetupRefNo() )
			AddStrToSendEdit( "->SendSetupRefNo() OK\n" );
		else
			AddStrToSendEdit( "->SendSetupRefNo() Error\n" );
	}		
}

void CIFDView::OnBnClickedButtReqLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dlgReqLogDate.m_reqLogDate = m_IFDX.GetLReqLogDate();

	if( m_dlgReqLogDate.DoModal() == IDOK )
	{
		m_IFDX.SetLReqLogDate( m_dlgReqLogDate.m_reqLogDate );

		CString str;

		str.Format( "SetLReqLogDate(%u)\n", m_IFDX.GetLReqLogDate() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendReqLog() )
			AddStrToSendEdit( "->SendReqLog() OK\n" );
		else
			AddStrToSendEdit( "->SendReqLog() Error\n" );
	}		
}

void CIFDView::OnRdResultProfisIfdxctrl(__int64 llRdIfdRefNo, __int64 llRdIfdDateTime, UINT lRdIfdAmount, UINT lRdIfdCurr, UINT lRdIfdMode)
{
	CString str;
	AddStrToReceiveEdit( "MSG_IFD_RESULT_PROFIS\n" );

	str.Format( "  - Reference Number : %12lld\n", llRdIfdRefNo );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Date & time : %14lld\n", llRdIfdDateTime );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Amount : %10d\n", lRdIfdAmount );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Currency : %2d\n", lRdIfdCurr );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Mode : %2d\n", lRdIfdMode );
	AddStrToReceiveEdit( LPCTSTR(str) );
}


void CIFDView::OnBnClickedButtAsAlarmSet()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dlgSetAsAlarm.m_AsAlarmValue = m_IFDX.GetLAsAlarmValue();//

	if( m_dlgSetAsAlarm.DoModal() == IDOK )
	{
		m_IFDX.SetLAsAlarmValue( m_dlgSetAsAlarm.m_AsAlarmValue );
		m_IFDX.SetLAsAlarmOnOff( m_dlgSetAsAlarm.m_AsAlarm_onOff );

		CString str;

		str.Format( "SetLAsAlarmOnOff(%u)\n", m_IFDX.GetLAsAlarmOnOff() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLAsAlarmValue(%u)\n", m_IFDX.GetLAsAlarmValue() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetAsAlarm() )
			AddStrToSendEdit( "->SendSetAsAlarm() OK\n" );
		else
			AddStrToSendEdit( "->SendSetAsAlarm() Error\n" );
	}		
}

void CIFDView::OnAsAlarmValueIfdxctrl(UINT lAlarmOnOff, UINT lAlarmValue)
{
	CString str;
	AddStrToReceiveEdit( "MSG_MAINTENANCE_VALUE\n" );

	str.Format( "  - Alarm on/off : %1d\n", lAlarmOnOff );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Alarm count : %1d\n", lAlarmValue );
	AddStrToReceiveEdit( LPCTSTR(str) );
}

void CIFDView::OnBnClickedButtonDeviceSetupStateDataEx() 
{
	// TODO: Add your control notification handler code here
	m_dlgSetupStateDataEx.m_bAddon	= (BOOL)m_IFDX.GetLADDOn();
	m_dlgSetupStateDataEx.m_bBatch	= (BOOL)m_IFDX.GetLBatchOn();
	m_dlgSetupStateDataEx.m_bBeep = (BOOL)m_IFDX.GetLBeepEnable();
	m_dlgSetupStateDataEx.m_bAuto		= (BOOL)m_IFDX.GetLAuto();
	m_dlgSetupStateDataEx.m_bUVOn		= (BOOL)m_IFDX.GetLUVOn();
	m_dlgSetupStateDataEx.m_bMROn		= (BOOL)m_IFDX.GetLMROn();
	m_dlgSetupStateDataEx.m_bIROn		= (BOOL)m_IFDX.GetLIROn();
	m_dlgSetupStateDataEx.m_bModeLock = (BOOL)m_IFDX.GetLModeLockOn();
	m_dlgSetupStateDataEx.m_lBatchCnt = (BYTE)m_IFDX.GetLBatchCountNum();
	m_dlgSetupStateDataEx.m_lUVLevel = (BYTE)m_IFDX.GetLUVLevel();
	m_dlgSetupStateDataEx.m_lMRLevel = (BYTE)m_IFDX.GetLMRLevel();
	m_dlgSetupStateDataEx.m_lIRLevel = (BYTE)m_IFDX.GetLIRLevel();

	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_COUNT_MODE]	  = (BYTE)m_IFDX.GetLCountMode();
	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_REJECT_POCKET] = (BYTE)m_IFDX.GetLRejPocketCap();
	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_STACK_POCKET]  = (BYTE)m_IFDX.GetLStkPocketCap();
	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_PRINTER_TYPE]  = (BYTE)m_IFDX.GetLPrintType();
	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_CURRENCY_CODE] = (BYTE)(m_IFDX.GetLCurrencyCode() - 1);

	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_DENOM] = (BYTE)m_IFDX.GetLDenom();

	if(m_dlgSetupStateDataEx.m_lBatchCnt == 0)
		m_dlgSetupStateDataEx.m_lBatchCnt = 10;

	if( m_dlgSetupStateDataEx.DoModal() == IDOK )
	{
		m_IFDX.SetLADDOn( m_dlgSetupStateDataEx.m_bAddon );
		m_IFDX.SetLBatchOn( m_dlgSetupStateDataEx.m_bBatch );
		m_IFDX.SetLBeepEnable( m_dlgSetupStateDataEx.m_bBeep );
		m_IFDX.SetLAuto( m_dlgSetupStateDataEx.m_bAuto );
		m_IFDX.SetLUVOn( m_dlgSetupStateDataEx.m_bUVOn );
		m_IFDX.SetLMROn( m_dlgSetupStateDataEx.m_bMROn );
		m_IFDX.SetLIROn( m_dlgSetupStateDataEx.m_bIROn );
		m_IFDX.SetLModeLockOn( m_dlgSetupStateDataEx.m_bModeLock );
		m_IFDX.SetLCountMode( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_COUNT_MODE] );
		m_IFDX.SetLRejPocketCap( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_REJECT_POCKET] );
		m_IFDX.SetLStkPocketCap( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_STACK_POCKET] );
		m_IFDX.SetLPrintType( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_PRINTER_TYPE] );
		m_IFDX.SetLBatchCountNum( m_dlgSetupStateDataEx.m_lBatchCnt );
		m_IFDX.SetLUVLevel( m_dlgSetupStateDataEx.m_lUVLevel );
		m_IFDX.SetLMRLevel( m_dlgSetupStateDataEx.m_lMRLevel );
		m_IFDX.SetLIRLevel( m_dlgSetupStateDataEx.m_lIRLevel );

		if(	m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_DENOM] == (m_iNumDenom-1))
		{
			m_IFDX.SetLDenom( 31 ); // DD
		}
		else
		{
			m_IFDX.SetLDenom( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_DENOM] );
		}

		m_IFDX.SetLCurrencyCode( m_dlgSetupStateDataEx.m_baSelect[ENUM_SETUP_CURRENCY_CODE] + 1 );

		CString str;

		str.Format( "SetLADDOn(%d)\n", m_IFDX.GetLADDOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchOn(%d)\n", m_IFDX.GetLBatchOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBeepEnable(%d)\n", m_IFDX.GetLBeepEnable() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLAuto(%d)\n", m_IFDX.GetLAuto() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLUVOn(%d)\n", m_IFDX.GetLUVOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMROn(%d)\n", m_IFDX.GetLMROn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLIROn(%d)\n", m_IFDX.GetLIROn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLModeLockOn(%d)\n", m_IFDX.GetLModeLockOn() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCountMode(%d)\n", m_IFDX.GetLCountMode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLDenom(%d)\n", m_IFDX.GetLDenom() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLRejPocketCap(%d)\n", m_IFDX.GetLRejPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLStkPocketCap(%d)\n", m_IFDX.GetLStkPocketCap() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLPrintType(%d)\n", m_IFDX.GetLPrintType() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLCurrencyCode(%d)\n", m_IFDX.GetLCurrencyCode() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLBatchCountNum(%d)\n", m_IFDX.GetLBatchCountNum() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLUVLevel(%d)\n", m_IFDX.GetLUVLevel() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLMRLevel(%d)\n", m_IFDX.GetLMRLevel() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLIRLevel(%d)\n", m_IFDX.GetLIRLevel() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetupStateDataEx() )
			AddStrToSendEdit( "->SendSetupStateDataEx() OK\n" );
		else
			AddStrToSendEdit( "->SendSetupStateDataEx() Error\n" );
	}		
}

void CIFDView::OnSetupStateDataExIfdxctrl() 
{
	CString str, sub;

	AddStrToReceiveEdit( "MSG_SETUP_STATE_DATA_EX\n" );

	switch( m_IFDX.GetLSpeed() )
	{
		case 0:
			str.Format( "  - Motor Speed = %4d rpm\n", 1000 ); break;
		case 1:
			str.Format( "  - Motor Speed = %4d rpm\n", 1200 ); break;
		case 2:
			str.Format( "  - Motor Speed = %4d rpm\n", 1500 ); break;
	}
	AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLBatchOn() ? "On" : "Off";
	str.Format( "  - Batch %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );


	sub = m_IFDX.GetLBeepEnable() ? "Enable" : "Disable";
	str.Format( "  - warning beep %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLAuto() ? "Auto" : "Manual";
	str.Format( "  - auto/manual : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLADDOn() ? "On" : "Off";
    str.Format( "  - ADD %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLUVOn() ? "On" : "Off";
	str.Format( "  - UV Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLMROn() ? "On" : "Off";
	str.Format( "  - MR Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLIROn() ? "On" : "Off";
	str.Format( "  - IR Detection %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	sub = m_IFDX.GetLModeLockOn() ? "On" : "Off";
	str.Format( "  - Mode Lock %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	{
		LONG lCurrencyCode;
		
		if( m_IFDX.GetLCurrencyCode() > MAX_CURRENCY )
			lCurrencyCode = 1;
		else
			lCurrencyCode = m_IFDX.GetLCurrencyCode();
		
		sub = gpaCurrencyName[lCurrencyCode];
	}

	str.Format( "  - Currency Code : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - denomination value : %d\n", m_IFDX.GetLDenom() ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLCountMode() )
	{
	case 0 : sub = "COUNT mode"; break;
	case 1 : sub = "MIXED mode"; break;
	case 2 : sub = "SINGLE mode"; break;
	case 3 : sub = "FACE mode"; break;
	case 4 : sub = "ORIENT mode"; break;
	case 6 : sub = "ISSUE mode"; break;
    case 8 : sub = "SERIAL mode"; break;
    case 9 : sub = "MIXED CURR mode"; break;
	}
	str.Format( "  - counting mode : %s\n", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLRejPocketCap() )
	{
	case 0: sub = "30 PCS\n"; break;
	case 1: sub = "20 PCS\n"; break;
	case 2: sub = "10 PCS\n"; break;
	}
	str.Format( "  - Reject Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );

	switch( m_IFDX.GetLStkPocketCap() )
	{
	case 0: sub = "200 PCS\n"; break;
	case 1: sub = "150 PCS\n"; break;
	case 2: sub = "100 PCS\n"; break;
	}
	str.Format( "  - Stacker Pocket Capacity : %s", LPCTSTR(sub) ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - Batch Counter Number : %d\n", m_IFDX.GetLBatchCountNum() ); AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - UV LEVEL : %d\n", m_IFDX.GetLUVLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - MR LEVEL : %d\n", m_IFDX.GetLMRLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
	str.Format( "  - IR LEVEL : %d\n", m_IFDX.GetLIRLevel() ); AddStrToReceiveEdit( LPCTSTR(str) );
}




void CIFDView::OnBnClickedButtDateTime()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_dlgSetDateTime.m_SetDateValue = m_IFDX.GetLDateValue();//
	m_dlgSetDateTime.m_SetTimeValue = m_IFDX.GetLTimeValue();//

	if( m_dlgSetDateTime.DoModal() == IDOK )
	{
#if 1
		m_IFDX.SetLDateValue( m_dlgSetDateTime.m_SetDateValue );
		m_IFDX.SetLTimeValue( m_dlgSetDateTime.m_SetTimeValue );
		m_IFDX.SetLSetDateTimeReq( m_dlgSetDateTime.m_SetDateTimeReq );

		CString str;

		str.Format( "SetLDateValue(%u)\n", m_IFDX.GetLDateValue() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLTimeValue(%u)\n", m_IFDX.GetLTimeValue() ); AddStrToSendEdit( LPCTSTR(str) );
		str.Format( "SetLSetDateTimeReq(%u)\n", m_IFDX.GetLSetDateTimeReq() ); AddStrToSendEdit( LPCTSTR(str) );

		if( m_IFDX.SendSetDateTime() )
			AddStrToSendEdit( "->SendSetDateTime() OK\n" );
		else
			AddStrToSendEdit( "->SendSetDateTime() Error\n" );
#endif
	}		
}

void CIFDView::OnSetDateTimeIfdxctrl(UINT lDateValue, UINT lTimeValue, UINT lDateTimeReq)
{
	CString str;
	AddStrToReceiveEdit( "MSG_DATE_TIME_VALUE\n" );

	str.Format( "  - Date time request : %1d\n", lDateTimeReq );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Date value : %1d\n", lDateValue );
	AddStrToReceiveEdit( LPCTSTR(str) );

	str.Format( "  - Time value : %1d\n", lTimeValue );
	AddStrToReceiveEdit( LPCTSTR(str) );
}


