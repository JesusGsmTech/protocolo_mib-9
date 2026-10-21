// DlgSetAsAlarm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgSetAsAlarm.h"


// CDlgSetAsAlarm 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgSetAsAlarm, CDialog)

CDlgSetAsAlarm::CDlgSetAsAlarm(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetAsAlarm::IDD, pParent)
{
	m_AsAlarm_onOff = 0;
}

CDlgSetAsAlarm::~CDlgSetAsAlarm()
{
}

void CDlgSetAsAlarm::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_AS_ALARM, m_AsAlarmValue);
	DDX_Radio(pDX, IDC_RADIO_ASALARM_OFF, m_AsAlarm_onOff);
}


BEGIN_MESSAGE_MAP(CDlgSetAsAlarm, CDialog)
END_MESSAGE_MAP()


// CDlgSetAsAlarm 메시지 처리기입니다.
