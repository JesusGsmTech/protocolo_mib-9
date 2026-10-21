#pragma once
#include "afxwin.h"


// CDlgSetAsAlarm 대화 상자입니다.

class CDlgSetAsAlarm : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetAsAlarm)

public:
	CDlgSetAsAlarm(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetAsAlarm();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_AS_ALARM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// AS alarm reference value
	unsigned long m_AsAlarmValue;
	// Alarm on, off bit value
	int m_AsAlarm_onOff;
};
