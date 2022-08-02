//-----------------------------------------------------------------------------------------------------------------------
#ifndef TAPP_H
#define TAPP_H
//-----------------------------------------------------------------------------------------------------------------------

#define MAX_MENU_ITEM	10
//-----------------------------------------------------------------------------------------------------------------------

#define APP_MAIN		int APIENTRY WinMain
#define APP_ARGS		HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd
#define APP_ARGS_PUSH	hInstance,hPrevInstance,lpCmdLine,nShowCmd
//-----------------------------------------------------------------------------------------------------------------------

#define APP_LPRESULTCB	LRESULT CALLBACK
#define APP_LPRESULT	LRESULT
//-----------------------------------------------------------------------------------------------------------------------

#define WNDPROC_ARGS	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam
//-----------------------------------------------------------------------------------------------------------------------

#define WM_MAX_APP		0x000BFFF
//-----------------------------------------------------------------------------------------------------------------------

enum TAPP_MAIN_RETURN_TYPE
{
    FAILL		= 0x00,
    SUCCESS		= 0x01,
};
//-----------------------------------------------------------------------------------------------------------------------

enum TAPP_SHOWWINDOW_COMMANDS
{
    ESW_HIDE = 0x00,
    ESW_SHOWNORMAL,
    ESW_NORMAL,
    ESW_SHOWMINIMIZED,
    ESW_SHOWMAXIMIZED,
    ESW_MAXIMIZE,
    ESW_SHOWNOACTIVATE,
    ESW_SHOW,
    ESW_MINIMIZE,
    ESW_SHOWMINNOACTIVE,
    ESW_SHOWNA,
    ESW_RESTORE,
    ESW_SHOWDEFAULT,
    ESW_FORCEMINIMIZE,
    ESW_MAX,
};
//-----------------------------------------------------------------------------------------------------------------------

enum TAPP_MYNEW_VAR
{
    UNK = 0x00,
    NO	= 0x01,
    YES = 0x02,
};
//-----------------------------------------------------------------------------------------------------------------------

APP_LPRESULTCB					sWndProc(WNDPROC_ARGS);
//-----------------------------------------------------------------------------------------------------------------------

class TApp
{
        friend APP_LPRESULTCB sWndProc(WNDPROC_ARGS);
        // ----
    public:
        TApp(void);
        ~TApp(void);
        // ----
    private:
        HINSTANCE						m_hIsnt;
        HINSTANCE						m_PrevhIsnt;
        HWND							m_hWnd;
        HMENU							m_hMenu;
        HMENU							m_hSubMenu[MAX_MENU_ITEM];
        LPCSTR							m_CmdLine;
        TAPP_SHOWWINDOW_COMMANDS		m_ShowCmd;
        LPCSTR							m_appName;
        MSG								m_msg;
        // ----
        TAPP_MYNEW_VAR					m_isInit;
        TAPP_MYNEW_VAR					m_isClassReg;
        TAPP_MYNEW_VAR					m_isWndCreated;
        TAPP_MYNEW_VAR					m_IsMenuCreated;
        // ----
        BYTE							m_MenuID;
    public:
        int								m_Icon;
        RECT							m_Rect;
        int								m_ScreenWidth;
        int								m_ScreenHeight;
        int								m_winWidth;
        int								m_winHeight;
        // ----
        void							Init(APP_ARGS);
        void							MyRegisterClass(LPCSTR AppName, WNDCLASSEX * wcex);
        void							MyWindowCreate(int Width, int Height, int xPos, int yPos, DWORD dwStyle);
        void							MyDestroyWindow();
        void							MyCloseWindow();
        void							MoveToCenter();
        void							Size();
        void							MsgLoop();
        void							MyCreateMenu();
        BYTE							CreateMenuItem(const char * szName);
        void							CreateSubMenuItem(const char * szName, BYTE MenuID, BYTE RegisterCMD);
        APP_LPRESULT					WndProc(WNDPROC_ARGS);
        // ----
        virtual	void					OnPaint() {};
        virtual void					OnCreate() {};
        virtual void					OnClose() {};
        virtual void					OnSize() {};
        virtual void					OnCmd(WPARAM Param, LPARAM lParam) {};
        virtual void					OnApp(WPARAM wParam, LPARAM lParam) {};
        virtual void					OnAppRange(UINT uMsg, WPARAM wParam, LPARAM lParam) {};
        virtual void					OnTimer(WPARAM wParam, LPARAM lParam) {};
};
//-----------------------------------------------------------------------------------------------------------------------

extern HWND gHwnd;
//-----------------------------------------------------------------------------------------------------------------------
#endif /* TAPP_H */
//-----------------------------------------------------------------------------------------------------------------------