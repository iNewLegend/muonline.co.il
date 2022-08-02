//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "TApp.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TApp"
//-----------------------------------------------------------------------------------------------------------------------

HWND	gHwnd		  	= NULL;
//-----------------------------------------------------------------------------------------------------------------------
TApp	* gParent		= NULL;
//-----------------------------------------------------------------------------------------------------------------------

TApp::TApp(void)
{
    m_isInit			= UNK;
    m_isClassReg		= UNK;
    m_isWndCreated		= UNK;
    m_IsMenuCreated		= UNK;
}
//-----------------------------------------------------------------------------------------------------------------------

TApp::~TApp(void)
{
    // -----
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::Init(APP_ARGS)
{
    gParent = this;
    // ----
    this->m_isInit		= NO;
    //---
    this->m_hIsnt		= hInstance;
    this->m_PrevhIsnt	= hPrevInstance;
    this->m_CmdLine		= lpCmdLine;
    this->m_ShowCmd		= (TAPP_SHOWWINDOW_COMMANDS)nShowCmd;
    //---
    this->m_isInit		= YES;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MyRegisterClass(LPCSTR AppName, WNDCLASSEX * wcex)
{
    this->m_isClassReg	= NO;
    // --
    wcex->lpfnWndProc	= sWndProc;
    wcex->hInstance		= this->m_hIsnt;
    wcex->hIcon			= LoadIcon(this->m_hIsnt, MAKEINTRESOURCE(m_Icon));
    wcex->hIconSm		= LoadIcon(this->m_hIsnt, MAKEINTRESOURCE(m_Icon));
    wcex->cbClsExtra	= 0;
    wcex->cbWndExtra	= 0;
    wcex->lpszMenuName	= AppName;
    wcex->lpszClassName	= AppName;
    // --
    RegisterClassEx(wcex);
    // --
    this->m_appName		= AppName;
    // --
    this->m_isClassReg	= YES;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MyWindowCreate(int Width, int Height, int xPos, int yPos, DWORD dwStyle)
{
    this->m_isWndCreated	= NO;
    // ----
    this->m_hWnd = CreateWindow(this->m_appName, this->m_appName, dwStyle, xPos,
                                yPos, Width, Height, NULL, NULL, this->m_hIsnt, NULL);
    // ----
    this->m_winWidth	= Width;
    this->m_winHeight	= Height;
    // ----
    if(this->m_hWnd == false)
    {
        MessageBoxA(0, "[TApp](MyWindowCreate) :: hWnd Error", 0, 0);
        return;
    }
    else
    {
        // # save handle for external functions
        gHwnd			= this->m_hWnd;
    }
    // ----
    ShowWindow(this->m_hWnd, this->m_ShowCmd);
    UpdateWindow(this->m_hWnd);
    // ----
    this->m_isWndCreated	= YES;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MyDestroyWindow()
{
    DestroyWindow(this->m_hWnd);
    // -----
    this->m_isWndCreated	= NO;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MyCloseWindow()
{
    CloseWindow(this->m_hWnd);
    // -----
    this->m_isWndCreated	= NO;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MoveToCenter()
{
    this->m_ScreenWidth		= GetSystemMetrics(SM_CXSCREEN);
    this->m_ScreenHeight	= GetSystemMetrics(SM_CYSCREEN);
    // ----
    MoveWindow(m_hWnd, (m_ScreenWidth - m_winWidth) / 2, (m_ScreenHeight - m_winHeight) / 2,
               m_winWidth, m_winHeight, true);
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::Size()
{
    GetClientRect(m_hWnd, & m_Rect);
    // -----
    m_winHeight		=	m_Rect.bottom;
    m_winWidth		=	m_Rect.right;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MsgLoop()
{
    if(GetMessage(& m_msg, this->m_hWnd, 0, NULL) != NULL)
    {
        if(TranslateAccelerator(m_msg.hwnd, 0, & m_msg) == false)
        {
            TranslateMessage(& m_msg);
            DispatchMessage(& m_msg);
        }
    }
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::MyCreateMenu()
{
    m_IsMenuCreated		= NO;
    // ----
    m_hMenu				= CreateMenu();
    // -----
    if(m_hMenu)
    {
        m_IsMenuCreated = YES;
        // -----
        SetMenu(m_hWnd, m_hMenu);
    }
}
//-----------------------------------------------------------------------------------------------------------------------

BYTE TApp::CreateMenuItem(const char * szName)
{
    BYTE bReturn			= m_MenuID;
    // -----
    m_hSubMenu[m_MenuID]	= CreatePopupMenu();
    // -----
    AppendMenu(m_hMenu, MF_STRING | MF_POPUP, (UINT)m_hSubMenu[m_MenuID], szName);
    // -----
    SetMenu(m_hWnd, m_hMenu);
    // -----
    m_MenuID++;
    // -----
    return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------

void TApp::CreateSubMenuItem(const char * szName, BYTE MenuID, BYTE RegisterCMD)
{
    AppendMenu(m_hSubMenu[MenuID], MF_STRING, RegisterCMD, szName);
    // -----
    SetMenu(m_hWnd, m_hMenu);
}
//-----------------------------------------------------------------------------------------------------------------------

APP_LPRESULTCB sWndProc(WNDPROC_ARGS)
{
    if((uMsg >= WM_APP) && (uMsg <= WM_MAX_APP))
    {
        gParent->OnAppRange(uMsg, wParam, lParam);
    }
    // ----
    switch(uMsg)
    {
        case WM_CREATE:
        {
            gParent->OnCreate();
        }
        break;

        case WM_PAINT:
        {
            gParent->OnPaint();
        }
        break;

		case WM_CLOSE:
        {
            gParent->OnClose();
            // # Leo123 : OnClose we dont need to back the defualt window function
            // -----
            return 0;
        }
        break;

        case WM_SIZE:
        {
            //gParent->OnSize();
        }
        break;

        case WM_APP:
        {
            gParent->OnApp(wParam, lParam);
        }
        break;

        case WM_COMMAND:
        {
            if(gParent->m_IsMenuCreated == YES)
            {
                gParent->OnCmd(wParam, lParam);
            }
        }
        break;

        case WM_SYSCOMMAND:
        {
            switch(wParam)
            {
                case SC_MAXIMIZE:
                {
                    //gParent->OnSize();
                }
                break;
            }
        }
        break;

        case WM_TIMER:
        {
            gParent->OnTimer(wParam, lParam);
        }
        break;
    }
    // -----
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
//-----------------------------------------------------------------------------------------------------------------------