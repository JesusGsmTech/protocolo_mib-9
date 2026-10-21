// IFD.h : main header file for the IFD application
//

#if !defined(AFX_IFD_H__4CF5365B_8B5B_484A_8F7F_F12E96BD605E__INCLUDED_)
#define AFX_IFD_H__4CF5365B_8B5B_484A_8F7F_F12E96BD605E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#define CUR_USD         1 // US Dollar
#define CUR_PESOS       2 // Mexico
#define CUR_WON         3 // Korean
#define CUR_EURO        4 // Euro
#define CUR_COLOMBIA    5 // Costa Rica
#define CUR_WIAN        6 // Chiana
#define CUR_LIRA        7 // Turkey 
#define CUR_COSTA       8 // Costa Rica Colone
#define CUR_NICARA      9 // Nicaragua
#define CUR_AUSTRA      10 // Australia
#define CUR_SINGAPORE   11 // Singapore
#define CUR_INDIA       12 // India
#define CUR_NORWAY      13 // Norway
#define CUR_NEWZILAND   14 // Newziland
#define CUR_POLSKI      15 // Poland
#define CUR_TAIWAN      16 // Taiwan
#define CUR_CZECHO      17 // CZECHO
#define CUR_LEBANON	    18 // LEBANON
#define CUR_SWEDEN      19 // SWEDEN
#define CUR_BRASIL      20  // BRASIL
#define CUR_CANADA      21  // Canada

#define CUR_SYRIA		22  // Syria
#define CUR_GUATE		23  // Guatemala
#define CUR_IRAQ		24  // Iraq
#define CUR_ISRAEL		25  // Israel
#define CUR_PERU		26  // Peru
#define CUR_JPY			33  // Japan
#define CUR_PAPUA		34  // Papua New Guinea
#define CUR_RUSSIA		35  // Russia
#define CUR_SAFRICA		36  // South Africa
#define CUR_ARAB		37  // Arab Emirates
#define CUR_THAILAND	38  // Thailand
#define CUR_ENGLAND	    39  // England
#define CUR_VENEZUELA   40  // England
#define CUR_BARCODE	    41  // England
#define CUR_UKRAINE	    42  // England
#define CUR_KAZAKHSTAN  43  // England
#define CUR_SWITZERLAND 44  // England

#define CUR_SAR         45  // Saudi Arabia		    Saudi riyal (SAR)
#define CUR_JOD         46  // Jordan			    Jordanian dinar (JOD)
#define CUR_KGS	        47	// Kyrgyzstan			som (KGS)
#define CUR_MYR	        48	// Malaysia				ringgit (MYR)
#define CUR_MCQ         49  // Malaysia cheque      (MCQ)
#define CUR_IDR         50  // Indonesia            Indonesian rupiah (IDR)
#define CUR_SDD         51  // Sudan                Sudanese dinar (SDD)
#define CUR_RON         52  // Romania              Romania New Leu(RON)
#define CUR_BYB         53  // Belarus              Belarusian ruble (BYB)
#define CUR_AZN         54  // Azerbaijani          Azerbaijani manat (AZM)
#define CUR_RSD         55  // Serbia               Serbian Dinar (RSD)
#define CUR_DOP         56  // Dominica             Republic Dominican peso (DOP)
#define CUR_SRD         57  // Suriname             Surinam dallar (SRD)
#define CUR_TID         58  // Canada               Canada Tire Money (TID) 
#define CUR_HUF			59  // Hungary		(HUF)	
#define CUR_HRK         60  // Croatia               Croatia Kuna (HRK)
#define CUR_GHC         61  // Ghana                Ghana Cedi (GHC)
#define CUR_GEL         62  // Georgia
#define CUR_EGP         63  // EGYPT
#define CUR_UGX         64  // UGANDA             (GHC)
#define CUR_MAD         65  // MOROCCO           MAD
#define CUR_LKR         66  // SriLanka             LKR
#define CUR_AMD         67  // ARMENIA             AMD
#define CUR_NAD	        68  // Namibia		NAD
#define CUR_HNL         69  // Honduras     HNL
#define CUR_KWD         70  // Kuwait    KWD
#define CUR_HKD     71  // HONG KONG
#define CUR_ETB 	72  // Ethiopia    ETB
#define CUR_PHP 	73  // Philipin    PHP
#define CUR_MNT 	74  // Mongol			MNT
#define CUR_IRR		75  // IRAN			IRR
#define CUR_SZL   	76  // SWAZILAND SZL
#define CUR_BWP		77  // BOTSWANA  BWP
#define CUR_QAR	    78  // QATAR		QAR
#define CUR_STL		79  // SCOTLAND  STL
#define CUR_AOA		80  // ANGOLA  AOA
#define CUR_MZN		81  // Mozambique  MZN  // CUR_MZN
#define CUR_OMR     82  // OMAN   OMR      // CUR_OMR
#define CUR_YER     83
#define CUR_BGN     84
#define CUR_PKR     85
#define CUR_MSP     86  //MARKS & SPENCER POUND MSP(Coupon)
#define CUR_LYD     87	// Libyan LYD
#define CUR_NGN     88	// Nigeria NGN // CUR_NGN
#define CUR_LSL     89	// Lesotho LSL // CUR_LSL
#define CUR_BHD     90  // Bahrain    CUR_BHD
#define CUR_TWD         91  // Taiwan TWD
#define CUR_ZAD         92  // ZAR + NAD   (ZAD)
#define CUR_ZMK         93  // Zambia ZMK
#define CUR_ATS         94  // Austria ATS
#define CUR_CLP         95  // Chile (CLP)
#define CUR_DZD         96  // Algeria (DZD)
#define CUR_DKK         97  // Denmark (DKK)
#define CUR_XPF         98  // new caledonia (XPF)
#define CUR_MOP         99  // Macao (MOP)
#define CUR_MKD        100  // Macedonia (MKD)
#define CUR_FJD        101  // Fiji (FJD)
#define CUR_BAM		   102  // Bosnia and Herzegovina (BAM)
#define CUR_VND		   103  // Vietram (VND)
#define CUR_KES		   104  // Kenya (KES)
#define CUR_XOF		   105  // CFA Franc, West African States  (XOF)
#define CUR_LAK		   106  // Laos Kip (LAK)
#define CUR_MMK		   107  // Myanma Kyat (MMK)
#define CUR_BDT		   108  // Bangladesh Taka (BDT)
#define CUR_CUP		   109  // Cuba (CUP)
#define CUR_MDL		   110  // Moldova (MDL)
#define CUR_SCP	       111  // Scotland Pound  (SCP)
#define CUR_IRP	       112  // Ireland Irish Pound  (IRP)
#define CUR_XAF	       113  // Central African States (XAF)
#define CUR_CP7	       114  // CANADA Coupon (CA$)
#define CUR_ARS	       115  // Argentina (ARS)
#define CUR_GIS	       116  // GBP, IRP, SCP Pound  (GIS)
#define CUR_BYN	       117  // Belarussian Ruble(NEW)
#define CUR_NPR	       118  // Nepal Rupee(NPR)
#define CUR_IQD		   119  // Iraq  	            New Iraqi dinar (NID)
#define CUR_TZS	       120  // Tanzanian Shilling (TZS)
#define CUR_RWF        121  // RWANDA (RWF)
#define CUR_BIF        122  // Burundi Franc (BIF)
#define CUR_ZWD		   123  // ZIMBABWE Dollar (ZWD)
#define CUR_REKA	   124  // REKA CHECK & RAIL(Swiss check) 	
#define CUR_ALL	       125  // Albania Lek
#define CUR_MUR	       126  // Mauritius Rupee
#define CUR_TJS	       127  // Tajikistan Somoni
#define CUR_CVE	       128  //  Cabo Verde Escudo
#define CUR_DJF		   129  // Djibouti
#define CUR_VES		   130  // Venezuela
#define CUR_LCH		   131  // Lebanon check
#define CUR_TCH		   132  // Turkey check
#define CUR_JMD		   133  // Jamaican Dollar
#define CUR_UZS		   134  // Uzbekistan Sum
#define CUR_SYC		   135  // Syria check
#define CUR_CDF		   136  // Congolese Franc
#define CUR_ONR		   137  // ONNURI
#define CUR_KHR		   138  // CAMBODIA
#define CUR_ZWL		   139  //
#define CUR_BND		   140  // Brunei

/* ------------ for test -------------------------
#define CUR_MIP		   141  // Test PHP
#define CUR_MIW		   142  // Test KRW
#define CUR_HDV		   143  // Hyundai Department store Voucher
#define CUR_KMV		   144  // KookMin travel Voucher
#define CUR_GSV		   145  // GS oil Voucher
#define CUR_HOV		   146  // Hyundai Oil Voucher
#define CUR_SKV		   147  // SK oil Voucher
#define CUR_SSV		   148  // SamSung Voucher
#define CUR_SOV		   149  // S-Oil Voucher
#define CUR_DMV		   150  // DaeMyungresort Voucher
---------------------------------------------------*/

#define CUR_PYG		   151  // Paraguay
#define CUR_GMD		   152  // Guarani
#define CUR_AFN		   153  // Afghanistan
#define CUR_NHV		   154  // NH bank Voucher
#define CUR_GYD		   155  // Guyana
#define CUR_MGA		   156  // Madagascar
#define CUR_TND		   157  // Tunisienne
#define CUR_SJV		   158  // Seongju Voucher
#define CUR_PBV		   159  // Paris Baguette Voucher
#define CUR_SLL		   160  // Sierra Leone
#define CUR_GNF		   161  // Guinea
#define CUR_LRD        162  // Republic of Liberia
#define CUR_WST        163  // Samoa


#define MAX_CURRENCY	164

#define DIAGNOSYS  99
#define CUR_RESV3  253 // Nothing
#define CUR_RESV4  254 // Nothing
#define CUR_RESV5  255 // Nothing


/////////////////////////////////////////////////////////////////////////////
// CDlgSetupStateData dialog
enum {
	ENUM_SETUP_PRINTER_TYPE = 0,
	ENUM_SETUP_DENOM,
	ENUM_SETUP_COUNT_MODE,
	ENUM_SETUP_CURRENCY_CODE,
	ENUM_SETUP_MR_SENSITIVE,
	ENUM_SETUP_REJECT_POCKET,
	ENUM_SETUP_STACK_POCKET
};

/////////////////////////////////////////////////////////////////////////////
// CIFDApp:
// See IFD.cpp for the implementation of this class
//

class CIFDApp : public CWinApp
{
public:
	CIFDApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFDApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CIFDApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFD_H__4CF5365B_8B5B_484A_8F7F_F12E96BD605E__INCLUDED_)
