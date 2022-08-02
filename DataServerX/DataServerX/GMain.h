//-----------------------------------------------------------------------------------------------------------------------
#ifndef MAIN_H
#define MAIN_H
//-----------------------------------------------------------------------------------------------------------------------

#include "TAPP.h"
#include <list>
#include <boost/thread.hpp>
//-----------------------------------------------------------------------------------------------------------------------

#define MAIN_WORKER_THREAD			void Task(void *dummy){g_Main.Worker();}
#define MAIN_SETUP_WORKER			_beginthread(Task, 0 , 0)
#define MAIN_PROJECT_NAME			"[- DataServerX -] :: Leo123" /* GameServer Logo */
#define MAIN_PROJECT_WINDOW_WIDTH	700
#define MAIN_PROJECT_WINDOW_HEIGHT	500
//-----------------------------------------------------------------------------------------------------------------------

enum TMAIN_CMD_MENU_COMMANDS
{
    CMD_EXIT,
	CMD_AUTOSTARTUP_ON,
	CMD_AUTOSTARTUP_OFF,
	CMD_RELOADGMS,
	CMD_RELOADINSPECT,
	CMD_RELOADGSSLIST,
	CMD_RELOAD_RUNEVENT_CORDS,
	CMD_RLEOAD_WROTEEVENT_WORDS,
	CMD_RLEOAD_START_CONFUSED,
	CMD_RELOAD_PROCESSES,
	CMD_START_TARGIL,
	CMD_START_RUNEVENT,
	CMD_START_WROTEEVENT,
	CMD_START_LOTTERYEVENT,
	CMD_START_CONFUSED,
	CMD_START_MESSAGES,
	CMD_STOP_MESSAGES
};
//-----------------------------------------------------------------------------------------------------------------------

enum TMAIN_CMD_APP_RANGE_COMMANDS
{
    FIRST = (WM_APP + 1),
};
//-----------------------------------------------------------------------------------------------------------------------

class TMain : TApp
{
    private:
        friend APP_LPRESULTCB	sWndProc(WNDPROC_ARGS);
        // ----
        int						m_iWorkerDelay;
		// ----
		boost::thread			m_threadWorker;
    public:
        TMain(void);
        ~TMain(void);
		// ----
		static bool	autoStartup;
		// ----
        bool	m_bWorkStop;
        // ----
        void	Initialize(APP_ARGS);
		void	Run();
        void	MsgBox(char * szFormat , ...);
		// ----
	protected:
		void	Worker();
		void	SetupMenu();
        // ----
		void	OnExit();
        void	OnCreate();
        void	OnPaint();
        void	OnClose();
        void	OnSize();
        void	OnCmd(WPARAM Param, LPARAM lParam);
        void	OnApp(WPARAM wParam, LPARAM lParam);
        void	OnAppRange(UINT uMsg, WPARAM wParam, LPARAM lParam);
        void	OnTimer(WPARAM wParam, LPARAM lParam);
        // ----
        void inline SetIcon(int icon)
        {
            m_Icon = icon;
        };
};
//-----------------------------------------------------------------------------------------------------------------------

extern TMain g_Main;
extern std::list<std::pair <int, int>>  g_MainConnectionsListNum;
//-----------------------------------------------------------------------------------------------------------------------
#endif /* MAIN_H */
//-----------------------------------------------------------------------------------------------------------------------


