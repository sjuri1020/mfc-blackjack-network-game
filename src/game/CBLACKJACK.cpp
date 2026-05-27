// CBLACKJACK.cpp: 구현 파일
//

#include "pch.h"
#include "NETWORK.h"
#include "CBLACKJACK.h"
#include "afxdialogex.h"
#include "NETWORKDlg.h"
#include "game_result.h"

// CBLACKJACK 대화 상자

IMPLEMENT_DYNAMIC(CBLACKJACK, CDialog)

CBLACKJACK::CBLACKJACK(CWnd* pParent /*=nullptr*/)
    : CDialog(IDD_DIALOG1, pParent)
    , m_PlayerCard1(_T(""))
    , m_PlayerCard2(_T(""))
    , m_PlayerCard3(_T(""))
    , m_PlayerCard5(_T(""))
    , m_PlayerCard4(_T(""))
    , m_DealerCard1(_T(""))
    , m_DealerCard2(_T(""))
    , m_DealerCard3(_T(""))
    , m_DealerCard4(_T(""))
    , m_DealerCard5(_T(""))
{
}

CBLACKJACK::~CBLACKJACK()
{
}

void CBLACKJACK::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_SPCARD1, m_PlayerCard1);
    DDX_Text(pDX, IDC_SPCARD2, m_PlayerCard2);
    DDX_Text(pDX, IDC_SPCARD3, m_PlayerCard3);
    DDX_Text(pDX, IDC_SPCARD4, m_PlayerCard4);
    DDX_Text(pDX, IDC_SPCARD5, m_PlayerCard5);
    DDX_Text(pDX, IDC_SDCARD1, m_DealerCard1);
    DDX_Text(pDX, IDC_SDCARD2, m_DealerCard2);
    DDX_Text(pDX, IDC_SDCARD3, m_DealerCard3);
    DDX_Text(pDX, IDC_SDCARD4, m_DealerCard4);
    DDX_Text(pDX, IDC_SDCARD5, m_DealerCard5);

    CFont boldFont;
    boldFont.CreateFont(60, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("나눔 고딕"));

    GetDlgItem(IDC_SPCARD1)->SetFont(&boldFont);
    GetDlgItem(IDC_SPCARD2)->SetFont(&boldFont);
    GetDlgItem(IDC_SPCARD3)->SetFont(&boldFont);
    GetDlgItem(IDC_SPCARD4)->SetFont(&boldFont);
    GetDlgItem(IDC_SPCARD5)->SetFont(&boldFont);

    GetDlgItem(IDC_SDCARD1)->SetFont(&boldFont);
    GetDlgItem(IDC_SDCARD2)->SetFont(&boldFont);
    GetDlgItem(IDC_SDCARD3)->SetFont(&boldFont);
    GetDlgItem(IDC_SDCARD4)->SetFont(&boldFont);
    GetDlgItem(IDC_SDCARD5)->SetFont(&boldFont);
}

BEGIN_MESSAGE_MAP(CBLACKJACK, CDialog)
    ON_BN_CLICKED(IDC_BGSTART, &CBLACKJACK::OnBnClickedBgstart)
    ON_BN_CLICKED(IDC_BHIT, &CBLACKJACK::OnBnClickedBhit)
    ON_BN_CLICKED(IDC_BSTAND, &CBLACKJACK::OnBnClickedBstand)
END_MESSAGE_MAP()

// CBLACKJACK 메시지 처리기

void CBLACKJACK::OnBnClickedBgstart()
{

    GetDlgItem(IDC_BGSTART)->EnableWindow(FALSE);

    // hit 버튼 활성화
    GetDlgItem(IDC_BHIT)->EnableWindow(TRUE);
    // stand 버튼 활성화
    GetDlgItem(IDC_BSTAND)->EnableWindow(TRUE);

    int nCurrentValue = m_nCurrentValue; //현재 값 저장
    CString strCurrentValue;
    strCurrentValue.Format(_T("%d"), nCurrentValue); //값을 문자열로 변환
    SetDlgItemText(IDC_ENOW_COIN2, strCurrentValue); //값을 IDC_NOW_COIN2에 설정

    int nInputValue = m_nInputValue; //현재 값 저장
    CString strInputValue;
    strInputValue.Format(_T("%d"), nInputValue); //값을 문자열로 변환
    SetDlgItemText(IDC_EDIT_BATTING, strInputValue); //값을 IDC_NOW_COIN2에 설정

    srand(static_cast<unsigned int>(time(nullptr))); // 랜덤 시드 초기화
     // IDC_EDIT_BATTING의 값을 얻어와서 출력


    // 플레이어에게 카드 할당
    CString card1 = GetRandomCard();
    CString card2 = GetRandomCard();
    CString card3 = GetRandomCard();
    CString card4 = GetRandomCard();

    m_PlayerCard1 = card1; // 첫 번째 플레이어 카드
    m_PlayerCard2 = card2; // 두 번째 플레이어 카드
    m_DealerCard1 = card3; // 첫 번째 딜러 카드
    m_DealerCard2 = card4; // 두 번째 딜러 카드

    NoShowDealerCard();

    // 딜러의 카드 합 계산
    int dealerSum = GetCardValue(m_DealerCard1) + GetCardValue(m_DealerCard2);
    while (dealerSum <= 17 && m_DealerCard3 == _T("")) {
        m_DealerCard3 = GetRandomCard();
        dealerSum += GetCardValue(m_DealerCard3);
    }

    // 딜러의 카드 합이 17 이하일 때 추가 카드 받기
    while (dealerSum <= 17 && m_DealerCard4 == _T("") && m_DealerCard3 != _T("")) {
        m_DealerCard4 = GetRandomCard();
        dealerSum += GetCardValue(m_DealerCard4);
    }

    while (dealerSum <= 17 && m_DealerCard5 == _T("") && m_DealerCard4 != _T("")) {
        m_DealerCard5 = GetRandomCard();
        dealerSum += GetCardValue(m_DealerCard5);
    }
    UpdateData(FALSE);

    // 딜러의 카드 합이 21을 초과하는 경우 게임 종료
    if (dealerSum > 21) {
        ShowDealerCard();
        MessageBox(_T("플레이어가 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }

   
}

void CBLACKJACK::OnBnClickedBhit()
{
    // 랜덤 시드 초기화
    srand(static_cast<unsigned int>(time(nullptr)));

    if (m_PlayerCard3 == _T(""))
    {
        m_PlayerCard3 = GetRandomCard(); // 첫 번째 클릭에 m_PlayerCard3에만 카드 할당
        UpdateData(FALSE); // 데이터 업데이트
    }
    else if (m_PlayerCard4 == _T(""))
    {
        m_PlayerCard4 = GetRandomCard(); // 두 번째 클릭에 m_PlayerCard4에만 카드 할당
        UpdateData(FALSE); // 데이터 업데이트
    }
    else if (m_PlayerCard5 == _T(""))
    {
        m_PlayerCard5 = GetRandomCard(); // 세 번째 클릭에 m_PlayerCard5에만 카드 할당
        UpdateData(FALSE); // 데이터 업데이트
    }

    // 플레이어의 카드 합 계산
    int playerSum = GetCardValue(m_PlayerCard1) + GetCardValue(m_PlayerCard2) + GetCardValue(m_PlayerCard3)
        + GetCardValue(m_PlayerCard4) + GetCardValue(m_PlayerCard5);

    // 플레이어의 카드 합이 21을 초과하는 경우 결과 
    if (playerSum > 21)
    {
        // 플레이어가 패배한 경우 처리 코드
        ShowDealerCard();
        MessageBox(_T("플레이어가 패배하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else if (m_PlayerCard5 != _T(""))
    {
        // 플레이어가 다섯 번째 카드를 뽑은 경우 딜러와의 카드 합 비교
        int dealerSum = GetCardValue(m_DealerCard1) + GetCardValue(m_DealerCard2) + GetCardValue(m_DealerCard3)
            + GetCardValue(m_DealerCard4) + GetCardValue(m_DealerCard5);

        if (playerSum > dealerSum && playerSum <= 21)
        {
            // 플레이어가 승리한 경우 처리 코드
            ShowDealerCard();
            MessageBox(_T("플레이어가 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
            game_result gameresultDialog;
            gameresultDialog.DoModal();
        }
        else if (playerSum == dealerSum)
        {
            // 딜러와 플레이어의 카드 합이 같은 경우 (무승부)
            ShowDealerCard();
            MessageBox(_T("무승부입니다!"), NULL, MB_OK | MB_ICONINFORMATION);
            game_result gameresultDialog;
            gameresultDialog.DoModal();
        }
        else
        {
            // 플레이어가 패배한 경우 처리 코드
            ShowDealerCard();
            MessageBox(_T("플레이어가 패배하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
            game_result gameresultDialog;
            gameresultDialog.DoModal();
        }
    }
}

void CBLACKJACK::OnBnClickedBstand()
{
    // Stand 버튼을 누르면 Hit 버튼 비활성화
    GetDlgItem(IDC_BHIT)->EnableWindow(FALSE);

    // 플레이어와 딜러 카드 합 비교
    int playerSum = GetCardValue(m_PlayerCard1) + GetCardValue(m_PlayerCard2) + GetCardValue(m_PlayerCard3)
        + GetCardValue(m_PlayerCard4) + GetCardValue(m_PlayerCard5);
    int dealerSum = GetCardValue(m_DealerCard1) + GetCardValue(m_DealerCard2) + GetCardValue(m_DealerCard3)
        + GetCardValue(m_DealerCard4) + GetCardValue(m_DealerCard5);

    ShowDealerCard();

    if (playerSum > dealerSum && playerSum <= 21)
    {
        // 플레이어가 승리한 경우 처리 코드
        MessageBox(_T("플레이어가 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else if (playerSum == dealerSum)
    {
        // 딜러와 플레이어의 카드 합이 같은 경우 (무승부)
        MessageBox(_T("무승부입니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else
    {
        // 플레이어가 패배한 경우 처리 코드
        MessageBox(_T("플레이어가 패배하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
}

void CBLACKJACK::CheckPlayerCardSum()
{
    int playerSum = 0;
    int dealerSum = 0;

    playerSum = GetCardValue(m_PlayerCard1) + GetCardValue(m_PlayerCard2) + GetCardValue(m_PlayerCard3)
        + GetCardValue(m_PlayerCard4) + GetCardValue(m_PlayerCard5);
    dealerSum = GetCardValue(m_DealerCard1) + GetCardValue(m_DealerCard2) + GetCardValue(m_DealerCard3)
        + GetCardValue(m_DealerCard4) + GetCardValue(m_DealerCard5);

    if (playerSum == 21)
    {
        // 플레이어가 블랙잭인 경우 처리 코드
        MessageBox(_T("플레이어가 블랙잭으로 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else if (dealerSum > 21)
    {
        // 딜러가 21을 초과한 경우 처리 코드
        MessageBox(_T("딜러가 21을 초과하여 플레이어가 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else if (playerSum > dealerSum && playerSum <= 21)
    {
        // 플레이어가 승리한 경우 처리 코드
        MessageBox(_T("플레이어가 승리하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else if (playerSum == dealerSum)
    {
        // 딜러와 플레이어의 카드 합이 같은 경우 처리 코드 (무승부)
        MessageBox(_T("무승부입니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
    else
    {
        // 플레이어가 패배한 경우 처리 코드
        MessageBox(_T("플레이어가 패배하였습니다!"), NULL, MB_OK | MB_ICONINFORMATION);
        game_result gameresultDialog;
        gameresultDialog.DoModal();
    }
}

int CBLACKJACK::GetCardValue(const CString& card)
{
    if (card == _T("A")) return 1; // A는 1로 처리
    else if (card == _T("J") || card == _T("Q") || card == _T("K")) return 10; // J, Q, K는 10으로 처리
    else return _ttoi(card); // 나머지 카드는 해당 값으로 처리
}

CString CBLACKJACK::GetRandomCard()
{
    // 랜덤하게 카드 값(A, 2, 3, ..., K) 생성
    int randomNumber = rand() % 13 + 1;
    CString cardValue;

    // 숫자를 카드 값으로 매핑 (1은 A, 11은 J, 12는 Q, 13은 K로)
    if (randomNumber == 1)
        cardValue = _T("A");
    else if (randomNumber == 11)
        cardValue = _T("J");
    else if (randomNumber == 12)
        cardValue = _T("Q");
    else if (randomNumber == 13)
        cardValue = _T("K");
    else
    {
        // 숫자 카드 (2부터 10까지)
        cardValue.Format(_T("%d"), randomNumber);
    }

    return cardValue;
}

void CBLACKJACK::ShowDealerCard()
{
    GetDlgItem(IDC_SDCARD2)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_SDCARD3)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_SDCARD4)->ShowWindow(SW_SHOW);
    GetDlgItem(IDC_SDCARD5)->ShowWindow(SW_SHOW);

    UpdateData(FALSE);
}

void CBLACKJACK::NoShowDealerCard()
{
    GetDlgItem(IDC_SDCARD2)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_SDCARD3)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_SDCARD4)->ShowWindow(SW_HIDE);
    GetDlgItem(IDC_SDCARD5)->ShowWindow(SW_HIDE);
    UpdateData(FALSE);

}

//처음에 playercardsum 인식 못할 때 선언해준 함수
int CBLACKJACK::GetPlayerCardSum()
{
    return GetCardValue(m_PlayerCard1) + GetCardValue(m_PlayerCard2)
        + GetCardValue(m_PlayerCard3) + GetCardValue(m_PlayerCard4) + GetCardValue(m_PlayerCard5);
}

//처음에 dealercardsum 인식 못할 때 선언해준 함수
int CBLACKJACK::GetDealerCardSum()
{
    return GetCardValue(m_DealerCard1) + GetCardValue(m_DealerCard2)
        + GetCardValue(m_DealerCard3) + GetCardValue(m_DealerCard4) + GetCardValue(m_DealerCard5);
}




CString CBLACKJACK::GetNowCoin2()
{
    CString strNowCoin2;
    GetDlgItemText(IDC_ENOW_COIN2, strNowCoin2);
    return strNowCoin2;
}


