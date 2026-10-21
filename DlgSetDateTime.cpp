// DlgSetDateTime.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgSetDateTime.h"


// CDlgSetDateTime 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgSetDateTime, CDialog)

CDlgSetDateTime::CDlgSetDateTime(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetDateTime::IDD, pParent)
{
	m_SetDateValue = 0;
	m_SetTimeValue = 0;
	m_SetDateTimeReq = 0;
}

CDlgSetDateTime::~CDlgSetDateTime()
{
}

void CDlgSetDateTime::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SET_DATE, m_SetDateValue);
	DDX_Text(pDX, IDC_EDIT_SET_TIME, m_SetTimeValue);
	DDX_Radio(pDX, IDC_RADIO_DATE_TIME_REQ, m_SetDateTimeReq);
}


BEGIN_MESSAGE_MAP(CDlgSetDateTime, CDialog)
END_MESSAGE_MAP()


// CDlgSetDateTime 메시지 처리기입니다.
