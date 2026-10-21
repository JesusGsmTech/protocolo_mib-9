// DlgRequestLog.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgRequestLog.h"


// CDlgRequestLog 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgRequestLog, CDialog)

CDlgRequestLog::CDlgRequestLog(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRequestLog::IDD, pParent)
{
	m_reqLogDate = 0;

}

CDlgRequestLog::~CDlgRequestLog()
{
}

void CDlgRequestLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DATE, m_reqLogDate);
}


BEGIN_MESSAGE_MAP(CDlgRequestLog, CDialog)
END_MESSAGE_MAP()


// CDlgRequestLog 메시지 처리기입니다.
