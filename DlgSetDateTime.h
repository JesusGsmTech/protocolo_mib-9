#pragma once
#include "afxwin.h"


// CDlgSetDateTime 대화 상자입니다.

class CDlgSetDateTime : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetDateTime)

public:
	CDlgSetDateTime(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetDateTime();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_SET_DATE_TIME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	// Date & time reference value
	unsigned long m_SetDateValue;
	unsigned long m_SetTimeValue;
	int m_SetDateTimeReq;
};
