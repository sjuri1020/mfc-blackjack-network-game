// CSever.cpp: 구현 파일
//

#include "pch.h"
#include "NETWORK.h"
#include "afxdialogex.h"
#include "CSever.h"


// CSever 대화 상자

IMPLEMENT_DYNAMIC(CSever, CDialog)

CSever::CSever(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_SERVERDIALOG, pParent)
	, m_StrName(_T(""))
{

}

CSever::~CSever()
{
}


BEGIN_MESSAGE_MAP(CSever, CDialog)
	ON_BN_CLICKED(IDC_BDISCON, &CSever::OnBnClickedBdiscon)
	ON_BN_CLICKED(IDC_BLISTEN, &CSever::OnBnClickedBlisten)
END_MESSAGE_MAP()

void CSever::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STRNAME, m_StrName);
}


BOOL CSever::OnInitDialog()
{
	CDialog::OnInitDialog();

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
	//SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	//SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_StrName = _T("localhost");
	UpdateData(FALSE);
	m_Ssocket.SetParent(this);
	m_Csocket.SetParent(this);
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSever::OnAccept()
{
	m_Ssocket.Accept(m_Csocket); //서버 소켓이 클라이언의 연결 요청을 수락 
	GetDlgItem(IDC_BCARDRAND)->EnableWindow(TRUE);
	GetDlgItem(IDC_BDISCON)->EnableWindow(TRUE); //연결 끊기 활성화
}

void CSever::OnConnect()
{
	GetDlgItem(IDC_BLISTEN)->EnableWindow(FALSE); //듣기 비활성화
	GetDlgItem(IDC_BDISCON)->EnableWindow(TRUE); //연결 끊기 활성화
}

void CSever::OnClose()
{

	m_Csocket.Close(); // 클라이언트 소켓 닫기
	m_Ssocket.Close(); // 서버 소켓 닫기 
	GetDlgItem(IDC_BDISCON)->EnableWindow(FALSE); //연결 끊기 비활성화
}

void CSever::OnReceive()
{
}

void CSever::OnSend()
{
}




// CSever 메시지 처리기

void CSever::OnBnClickedBlisten()
{
	//서버 소켓은 Create로 생성할 때 포트번호를 입력한다.
	m_Ssocket.Create(4000); // 서버는 포트 4000에서 들어오는 연결을 수신 가능
	m_Ssocket.Listen(); // 클라이언트로부터의 연결 요청을 수신 대기
	GetDlgItem(IDC_BLISTEN)->EnableWindow(FALSE); // 듣기 버튼 비활성화
	GetDlgItem(IDC_BDSTART)->EnableWindow(TRUE); // 게임시작 버튼 활성화
}


void CSever::OnBnClickedBdiscon()
{
	m_Csocket.Close(); //클라이언트 소켓 닫기
	m_Ssocket.Close(); //서버 소켓 닫기 
	GetDlgItem(IDC_BDISCON)->EnableWindow(FALSE); //연결 끊기 버튼 비활성화
}
