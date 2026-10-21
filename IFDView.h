// IFDView.h : interface of the CIFDView class
//
/////////////////////////////////////////////////////////////////////////////
//{{AFX_INCLUDES()
#include "ifdx_sb7.h"
//}}AFX_INCLUDES

#if !defined(AFX_IFDVIEW_H__9E66179B_DC64_4DD9_9491_271D42035ED3__INCLUDED_)
#define AFX_IFDVIEW_H__9E66179B_DC64_4DD9_9491_271D42035ED3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgDeviceSetLiveParam.h"
#include "DlgDeviceSetup2.h"
#include "DlgSetupStateData.h"
#include "DlgSetupStateData2.h"
#include "DlgSetupStateDataEx.h"
#include "DlgDispenseStart.h"
#include "DlgMultiBatch.h"
#include "DlgSetRefNumber.h"
#include "DlgRequestLog.h"
#include "DlgSetAsAlarm.h"
#include "DlgSetDateTime.h"

#define COMBO_STR_CLEAR_0	"Total Clear"
#define COMBO_STR_CLEAR_1	"JAM Clear"
#define COMBO_STR_CLEAR_2	"Stacker Pocket Clear"
#define COMBO_STR_CLEAR_3	"Reject Pocket Clear"
#define COMBO_STR_CLEAR_4	"Mixed Mode Total Clear"
#define COMBO_STR_CLEAR_5	"Simpe Mode Total Clear"
#define COMBO_STR_CLEAR_6	"Counting Report Clear"

#define COMBO_STR_REQUEST_0	"Setup Status Data Request"
#define COMBO_STR_REQUEST_1	"Counting Result Request"
#define COMBO_STR_REQUEST_2	"Error State Request"
#define COMBO_STR_REQUEST_3	"Resending Request"
#define COMBO_STR_REQUEST_4	"Sensor Stacker Status Request"
#define COMBO_STR_REQUEST_5	"Setup Status Data2 Request"
#define COMBO_STR_REQUEST_6	"Device Setup2 Request"
#define COMBO_STR_REQUEST_7	 "IR sensor state Request"
#define COMBO_STR_REQUEST_8	 "Counting Report Request"
#define COMBO_STR_REQUEST_9	 "SW Version Request"


class CIFDView : public CFormView
{
protected: // create from serialization only
	CIFDView();
	DECLARE_DYNCREATE(CIFDView)

public:
	//{{AFX_DATA(CIFDView)
	enum { IDD = IDD_IFD_FORM };
	CEdit	m_editSend;
	CComboBox	m_comboRequest;
	CComboBox	m_comboClear;
	CEdit	m_editReceive;
	CIFDX_SB7	m_IFDX;
	//}}AFX_DATA

// Attributes
public:

	CIFDDoc* GetDocument();

	bool m_bCommPortConnected;
	CDlgDeviceSetLiveParam m_dlgDeviceSetLive;
	CDlgDeviceSetup2 m_dlgDeviceSetup2;
	CDlgSetupStateData m_dlgSetupStateData;
	CDlgSetupStateData2 m_dlgSetupStateData2;
	CDlgSetupStateDataEx m_dlgSetupStateDataEx;
	CDlgDispenseStart m_dlgDispenseStart;
	CDlgMultiBatch m_dlgMultiBatch;
	CDlgSetRefNumber m_dlgSetRefNumber;
	CDlgRequestLog m_dlgReqLogDate;
	CDlgSetAsAlarm m_dlgSetAsAlarm;
	CDlgSetDateTime m_dlgSetDateTime;

	BOOL bDispensemode;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIFDView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CIFDView();

	void AddStrToSendEdit( const char *pStr );
	void AddStrToReceiveEdit( const char *pStr );

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CIFDView)
	afx_msg void OnButtonCurrencyChange();
	afx_msg void OnButtonDefaultLoading();
	afx_msg void OnButtonDeviceSetLive();
	afx_msg void OnButtonDeviceSetup2();
	afx_msg void OnButtonDeviceSetupStateData();
	afx_msg void OnButtonSendStart();
	afx_msg void OnButtonSendClear();
	afx_msg void OnButtonSendRequest();
	afx_msg void OnCommportConnect();
	afx_msg void OnUpdateCommportConnect(CCmdUI* pCmdUI);
	afx_msg void OnCommportDisconnect();
	afx_msg void OnUpdateCommportDisconnect(CCmdUI* pCmdUI);
	afx_msg void OnByteCountDataIfdxctrl(long lData);
	afx_msg void OnCdErrorIfdxctrl(long lErrorCode);
	afx_msg void OnCountStartIfdxctrl(long lNewDeposit);
	afx_msg void OnCountStopIfdxctrl();
	afx_msg void OnDeviceSetLiveIfdxctrl(long bLive);
	afx_msg void OnDeviceSetup2Ifdxctrl(long lByteCountingEnable, long lLocKeyPad);
	afx_msg void OnResultDenomIfdxctrl(long lDenomNumber, long lCount);
	afx_msg void OnResultPreDenomIfdxctrl(long lDenomNumber, long lCount);
	afx_msg void OnSensorStatusIfdxctrl();
	afx_msg void OnSetupNoAcceptIfdxctrl();
	afx_msg void OnSetupStateDataIfdxctrl();
	afx_msg void OnSetupStateData2Ifdxctrl();
	afx_msg void OnSetupStateDataExIfdxctrl();
	afx_msg void OnButtonDispenseStart();
	afx_msg void OnDispenseAmountIfdxctrl(long lAmount, long lCount);
	afx_msg void OnDispenseMatchAmountIfdxctrl(long lAmount, long lCount);
	afx_msg void OnOcrIfdxctrl(long lTotal_Index, long strOCR, long lDenom);
	afx_msg void OnButtonOcr();
	afx_msg void OnButtonMultiBatch();
	afx_msg void OnMultiBatchIfdxctrl(long FAR* lpMultiBatchSet, long FAR* lpCurDenomCnt);
	afx_msg void OnMultiBatchMatchIfdxctrl(long FAR* lpMultiBatchSet, long FAR* lpCurDenomCnt);
	afx_msg void OnButtonDeviceSetupStateData2();
	afx_msg void OnBarCodeIfdxctrl(long lTotal_Index, long strBARCODE);
	afx_msg void OnButtonBarcode();
	afx_msg void OnCountingReportDataIfdxctrl(long lTotal_StackerCount, long lTotal_RejectorCount);
	afx_msg void OnMC_StatusIfdxctrl(long lMC_StatusCode);
	afx_msg void OnSwVersionIfdxctrl(long lSwVerUpper, long lSwVerLower, long lChksumUpper, long lChksumLower);
	afx_msg void OnOcrResultIfdxctrl(char * pBuf);
	afx_msg void OnRdResultProfisIfdxctrl(__int64 llRdIfdRefNo, __int64 llRdIfdDateTime, UINT lRdIfdAmount, UINT lRdIfdCurr, UINT lRdIfdMode);
	afx_msg void OnAsAlarmValueIfdxctrl(UINT lAlarmOnOff, UINT lAlarmValue);
	afx_msg void OnResultValueCountIfdxctrl(unsigned long lValue, unsigned short lCount);
	afx_msg	void CIFDView::OnSetDateTimeIfdxctrl(UINT lDateValue, UINT lTimeValue, UINT lDateTimeReq);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonSendStop();
	afx_msg void OnTcpConnect();

	afx_msg void OnUpdateTcpConnect(CCmdUI *pCmdUI);
	afx_msg void OnTcpDisconnect();
	afx_msg void OnUpdateTcpDisconnect(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedSendCancelStart();
	afx_msg void OnBnClickedReboot();
	void OnCheckIR(void);
	afx_msg void OnBnClickedButtonSaveBmpToUsb();
	afx_msg void OnBnClickedButtonSaveBmpToUsb2();

	afx_msg void OnBnClickedButtonWingMotorStart();
	afx_msg void OnBnClickedButtonWingMotorStop();
	afx_msg void OnBnClickedButtSetRefNo();
	afx_msg void OnBnClickedButtReqLog();
	//afx_msg void OnBnClickedButtAsAlarmReq();
	afx_msg void OnBnClickedButtAsAlarmSet();
	afx_msg void OnBnClickedButtonDeviceSetupStateDataEx();
	afx_msg void OnBnClickedButtDateTime();
};

#ifndef _DEBUG  // debug version in IFDView.cpp
inline CIFDDoc* CIFDView::GetDocument()
   { return (CIFDDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IFDVIEW_H__9E66179B_DC64_4DD9_9491_271D42035ED3__INCLUDED_)
