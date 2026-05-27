#pragma once


// NETWORKKK 대화 상자

class NETWORKKK : public CDialog
{
	DECLARE_DYNAMIC(NETWORKKK)

public:
	NETWORKKK(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~NETWORKKK();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORK_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
