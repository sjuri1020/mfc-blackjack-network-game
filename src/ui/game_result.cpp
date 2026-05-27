// game_result.cpp: 구현 파일
// 게임 결과 창

#include "pch.h"
#include "NETWORK.h"
#include "game_result.h"
#include "afxdialogex.h"
#include "NETWORKKK.h"
#include "CBLACKJACK.h"
#include "NETWORKDlg.h"



// game_result 대화 상자

IMPLEMENT_DYNAMIC(game_result, CDialog)

game_result::game_result(CNETWORKDlg* pParentNetwork, CBLACKJACK* pParentBlackjack)
    : CDialog(IDD_DIALOG2, pParentNetwork != nullptr ? pParentNetwork : dynamic_cast<CWnd*>(pParentBlackjack))
    , m_pBlackjackParent(pParentBlackjack)
    , m_pNetworkParent(pParentNetwork)

{
    // 생성자 코드...
}


game_result::~game_result()
{
}



void game_result::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(game_result, CDialog)
    ON_BN_CLICKED(IDC_BUTTON1, &game_result::OnBnClickedButton1)
END_MESSAGE_MAP()

void game_result::OnBnClickedButton1()
{
    // CBLACKJACK 대화 상자를 닫기 위한 코드 추가
    CBLACKJACK* pBlackjackDialog = dynamic_cast<CBLACKJACK*>(GetParent());
    if (pBlackjackDialog != nullptr) {
        pBlackjackDialog->EndDialog(IDCANCEL);  // CBLACKJACK 대화 상자 닫기
    }
    
    OnOK();
}
BOOL game_result::OnInitDialog()
{
    CDialog::OnInitDialog();

    // CBLACKJACK 클래스의 객체 생성
    CBLACKJACK* pBlackjack = dynamic_cast<CBLACKJACK*>(GetParent());

    // IDC_NOW_COIN2 값 가져오기
    CString strNowCoin2 = pBlackjack->GetNowCoin2();

    int nInputValue = pBlackjack->m_nInputValue;

    // 플레이어와 딜러 카드 합 가져오기
    int m_PlayerCardSum = pBlackjack->GetPlayerCardSum();
    int m_DealerCardSum = pBlackjack->GetDealerCardSum();

    CString debugMsg;
    debugMsg.Format(_T("남은 금액: %s, 배팅금액: %d, 플레이어 합: %d, 딜러 합: %d"),
        strNowCoin2, nInputValue, m_PlayerCardSum, m_DealerCardSum);
    AfxMessageBox(debugMsg);

    CString strOutput;

    if (m_PlayerCardSum > m_DealerCardSum && m_PlayerCardSum <= 21)
    {
        int output = _ttoi(strNowCoin2) + nInputValue * 2;
        strOutput.Format(_T("%d"), output);
    }
    else if (m_PlayerCardSum < m_DealerCardSum && m_DealerCardSum <= 21)
    {
        strOutput = strNowCoin2;
    }
    else if (m_PlayerCardSum == m_DealerCardSum && m_PlayerCardSum <= 21)
    {
        int output = _ttoi(strNowCoin2) + nInputValue;
        strOutput.Format(_T("%d"), output);
    }
    else if (m_PlayerCardSum > 21)
    {
        strOutput = strNowCoin2;
    }
    else if (m_DealerCardSum > 21)
    {
        int output = _ttoi(strNowCoin2) + nInputValue * 2;
        strOutput.Format(_T("%d"), output);
    }

    CWnd* pWnd1 = GetDlgItem(IDC_EREMAIN_COIN);
    if (pWnd1 != nullptr)
        pWnd1->SetWindowText(strOutput);

    return TRUE;
}
