// NETWORKKK.cpp: 구현 파일
//

#include "pch.h"
#include "NETWORK.h"
#include "NETWORKKK.h"
#include "afxdialogex.h"


// NETWORKKK 대화 상자

IMPLEMENT_DYNAMIC(NETWORKKK, CDialog)

NETWORKKK::NETWORKKK(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NETWORK_DIALOG, pParent)
{

}

NETWORKKK::~NETWORKKK()
{
}

void NETWORKKK::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(NETWORKKK, CDialog)
END_MESSAGE_MAP()


// NETWORKKK 메시지 처리기
