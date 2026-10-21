#pragma once
#include "afxwin.h"


// CDlgRequestLog 대화 상자입니다.

class CDlgRequestLog : public CDialog
{
	DECLARE_DYNAMIC(CDlgRequestLog)

public:
	CDlgRequestLog(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgRequestLog();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_REQ_LOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	unsigned long m_reqLogDate;
};
