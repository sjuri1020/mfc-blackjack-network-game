#pragma once
#include "afxdialogex.h"
#include "CMySocket.h"


// CSever 대화 상자

class CSever : public CDialog
{
	DECLARE_DYNAMIC(CSever)

public:
	CSever(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSever();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERVERDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	CMySocket m_Ssocket, m_Csocket;
	CString m_StrName;
	//서버 소켓, 클라이언트 소켓
	void OnAccept();
	void OnConnect();
	void OnClose();
	void OnReceive();
	void OnSend();
	afx_msg void OnBnClickedBlisten();
	afx_msg void OnBnClickedBdiscon();

};
