#pragma once
#include "afxwin.h"


// CDlgSetRefNumber 대화 상자입니다.

class CDlgSetRefNumber : public CDialog
{
	DECLARE_DYNAMIC(CDlgSetRefNumber)

public:
	CDlgSetRefNumber(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgSetRefNumber();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_INPUT_REF_NO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	__int64 m_llRefNo;
};
