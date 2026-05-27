
// NETWORKDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "NETWORK.h"
#include "NETWORKDlg.h"
#include "afxdialogex.h"
#include "CBLACKJACK.h"
#include "game_result.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNETWORKDlg 대화 상자



CNETWORKDlg::CNETWORKDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NETWORK_DIALOG, pParent)
	//, m_NowCoin(1000)
	, m_BattingCoin(_T(""))
	, m_enow_coin(_T("1000"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNETWORKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//DDX_Text(pDX, IDC_STATIC_NOW_COIN, m_NowCoin);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_BattingCoin);
	//DDX_Text(pDX, IDC_STATIC_NOW_COIN, m_NowCoin);
	DDX_Text(pDX, IDC_EDIT_NOW_COIN, m_enow_coin);
}

BEGIN_MESSAGE_MAP(CNETWORKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTT_START, &CNETWORKDlg::OnBnClickedButtStart)
END_MESSAGE_MAP()


// CNETWORKDlg 메시지 처리기

BOOL CNETWORKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CNETWORKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CNETWORKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CNETWORKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNETWORKDlg::OnBnClickedButtStart()
{
	// IDC_EDIT_NOW_COIN에서 현재 값 가져오기
	CString strCurrentValue;
	GetDlgItemText(IDC_EDIT_NOW_COIN, strCurrentValue);
	int nCurrentValue = _ttoi(strCurrentValue);

	// IDC_EDIT_INPUT에서 값 가져오기
	CString strInputValue;
	GetDlgItemText(IDC_EDIT_INPUT, strInputValue);
	int nInputValue = _ttoi(strInputValue);
	CBLACKJACK BlackJackDialog;

	// game_result 대화 상자의 IDC_EREMAIN_COIN 값 가져오기
	CString strGameResultValue;
	// game_result 대화 상자의 포인터를 획득하여 IDC_EREMAIN_COIN의 값을 얻어온다
	CWnd* pGameResultDlg = GetDlgItem(IDD_DIALOG2); // IDD_DIALOG_GAME_RESULT에 game_result의 대화 상자 ID를 넣어주세요.
	if (pGameResultDlg != nullptr) {
		CWnd* pGameResultControl = pGameResultDlg->GetDlgItem(IDC_EREMAIN_COIN);
		if (pGameResultControl != nullptr) {
			pGameResultControl->GetWindowText(strGameResultValue);
		}
	}
	// IDC_EREMAIN_COIN 값 가져오기 끝

	int nGameResultValue = _ttoi(strGameResultValue);
	if (nCurrentValue < nInputValue)
	{
		AfxMessageBox(_T("돈이 부족합니다."));
		return;
	}

	int nNewCurrentValue = nCurrentValue - nInputValue;
	SetDlgItemInt(IDC_EDIT_NOW_COIN, nNewCurrentValue);

	SetDlgItemText(IDC_EREMAIN_COIN, strGameResultValue);

	SetDlgItemText(IDC_EDIT_INPUT, _T(""));

	//CBLACKJACK BlackJackDialog;
	BlackJackDialog.m_nCurrentValue = nNewCurrentValue;
	BlackJackDialog.m_nInputValue = nInputValue;

	if (BlackJackDialog.DoModal() == IDOK)
	{
		// 필요한 로직 추가
	}
}

void CNETWORKDlg::SetEditNowCoin(int newValue)
{
	CString strNewValue;
	strNewValue.Format(_T("%d"), newValue);
	m_enow_coin = strNewValue; // m_enow_coin을 업데이트

	UpdateData(FALSE); // 변수 값을 컨트롤에 반영
}


