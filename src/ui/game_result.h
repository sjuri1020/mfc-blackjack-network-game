#pragma once
#include "CBLACKJACK.h"
#include "NETWORKDlg.h"

// game_result 대화 상자

class game_result : public CDialog
{
	DECLARE_DYNAMIC(game_result)

public:
	game_result(CNETWORKDlg* pParentNetwork = nullptr, CBLACKJACK* pParentBlackjack = nullptr); // 생성자 수정

	virtual ~game_result();
private:
	CBLACKJACK* m_pBlackjackParent;
	CNETWORKDlg* m_pNetworkParent;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog() override;
	void OnBnClickedButton1();
	 
	CString m_strResult;
	CString m_WinLoseText; // 승리 또는 패배 텍스트

private:
	int calculatedValue;
	int bettingCoinValue; // 추가: 배팅 금액 변수
};
