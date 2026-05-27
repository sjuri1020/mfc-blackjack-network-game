// CMySocket.cpp: 구현 파일
//

#include "pch.h"
#include "NETWORK.h"
#include "CMySocket.h"
#include "NETWORKDlg.h"
#include "CBLACKJACK.h"
#include "CSever.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}

// CMySocket 멤버 함수
void CMySocket::SetParent(CDialog* pWnd)
{
	m_pWnd = pWnd;
}

void CMySocket::OnAccept(int nErrorCode)
{
    if (nErrorCode == 0 && m_pWnd != nullptr)
    {
        if (dynamic_cast<CBLACKJACK*>(m_pWnd))
        {
            ((CBLACKJACK*)m_pWnd)->OnAccept();
        }
        else if (dynamic_cast<CSever*>(m_pWnd))
        {
            ((CSever*)m_pWnd)->OnAccept();
        }
    }
    CAsyncSocket::OnAccept(nErrorCode);
}

void CMySocket::OnConnect(int nErrorCode)
{
    if (nErrorCode == 0 && m_pWnd != nullptr)
    {
        if (dynamic_cast<CBLACKJACK*>(m_pWnd))
        {
            ((CBLACKJACK*)m_pWnd)->OnConnect();
        }
        else if (dynamic_cast<CSever*>(m_pWnd))
        {
            ((CSever*)m_pWnd)->OnConnect();
        }
    }
    CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode)
{
    if (nErrorCode == 0 && m_pWnd != nullptr)
    {
        if (dynamic_cast<CBLACKJACK*>(m_pWnd))
        {
            ((CBLACKJACK*)m_pWnd)->OnReceive();
        }
        else if (dynamic_cast<CSever*>(m_pWnd))
        {
            ((CSever*)m_pWnd)->OnReceive();
        }
    }
    CAsyncSocket::OnReceive(nErrorCode);
}

void CMySocket::OnClose(int nErrorCode)
{
    if (nErrorCode == 0 && m_pWnd != nullptr)
    {
        if (dynamic_cast<CBLACKJACK*>(m_pWnd))
        {
            ((CBLACKJACK*)m_pWnd)->OnClose();
        }
        else if (dynamic_cast<CSever*>(m_pWnd))
        {
            ((CSever*)m_pWnd)->OnClose();
        }
    }
    CAsyncSocket::OnClose(nErrorCode);
}

void CMySocket::OnSend(int nErrorCode)
{
    if (nErrorCode == 0 && m_pWnd != nullptr)
    {
        if (dynamic_cast<CBLACKJACK*>(m_pWnd))
        {
            ((CBLACKJACK*)m_pWnd)->OnSend();
        }
        else if (dynamic_cast<CSever*>(m_pWnd))
        {
            ((CSever*)m_pWnd)->OnSend();
        }
    }
    CAsyncSocket::OnSend(nErrorCode);
}
