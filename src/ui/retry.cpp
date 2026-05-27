// retry.cpp: 구현 파일
//

#include "pch.h"
#include "NETWORK.h"
#include "retry.h"
#include "afxdialogex.h"


// retry 대화 상자

IMPLEMENT_DYNAMIC(retry, CDialog)

retry::retry(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG2, pParent)
{

}

retry::~retry()
{
}

void retry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(retry, CDialog)
	ON_STN_CLICKED(IDC_STATIC_NOW_COIN2, &retry::OnStnClickedStaticNowCoin2)
END_MESSAGE_MAP()


// retry 메시지 처리기


void retry::OnStnClickedStaticNowCoin2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
