#pragma once


// CBLACKJACK 대화 상자

class CBLACKJACK : public CDialog
{
	DECLARE_DYNAMIC(CBLACKJACK)

public:
	CBLACKJACK(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBLACKJACK();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBgstart();
	afx_msg void OnBnClickedBhit();
	afx_msg void OnBnClickedBstand();
	void ShowDealerCard();
	void NoShowDealerCard();
	CString GetRandomCard();
	int m_nCurrentValue; // 현재 코인 값을 저장할 변수
	int m_nInputValue;
	CString m_PlayerCard1;
	CString m_PlayerCard2;
	CString m_PlayerCard3;
	CString m_PlayerCard4;
	CString m_PlayerCard5;
	CString m_DealerCard1;
	CString m_DealerCard2;
	CString m_DealerCard3;
	CString m_DealerCard4;
	CString m_DealerCard5; 
	int playerSum;
	void CheckPlayerCardSum();
	int GetCardValue(const CString& card);
	CString m_PlayerCardSum; // 변수 추가
	CString m_DealerCardSum; // 변수 추가
	int GetPlayerCardSum();
	int GetDealerCardSum();
	CString GetNowCoin2();
};
