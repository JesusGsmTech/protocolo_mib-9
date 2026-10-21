// DlgSetRefNumber.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "IFD.h"
#include "DlgSetRefNumber.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CDlgSetRefNumber 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgSetRefNumber, CDialog)

CDlgSetRefNumber::CDlgSetRefNumber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetRefNumber::IDD, pParent)
{
	m_llRefNo = 0LL;
}

CDlgSetRefNumber::~CDlgSetRefNumber()
{
}

void CDlgSetRefNumber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REF_NO, m_llRefNo);
}


BEGIN_MESSAGE_MAP(CDlgSetRefNumber, CDialog)
END_MESSAGE_MAP()


// CDlgSetRefNumber 메시지 처리기입니다.
