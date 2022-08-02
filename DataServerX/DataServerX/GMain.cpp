//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "resource.h"
#include "GMain.h"
#include "GLog.h"
#include "GConfig.h"
#include "SEventManager.h"
#include "SRunEvent.h"
#include "SFastWrote.h"
#include "SConfusedEvent.h"
#include "Object.h"
//-----------------------------------------------------------------------------------------------------------------------

bool TMain::autoStartup = false;
//-----------------------------------------------------------------------------------------------------------------------

std::list<std::pair <int, int>>  g_MainConnectionsListNum;
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TMain"
//-----------------------------------------------------------------------------------------------------------------------

TMain		g_Main;
//-----------------------------------------------------------------------------------------------------------------------

TMain::TMain(void)
{
    m_iWorkerDelay	= 1200;
    m_bWorkStop		= false;
    // ----
	this->SetIcon(IDI_ICON1);
}
//-----------------------------------------------------------------------------------------------------------------------

TMain::~TMain(void)
{
    // ----
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::Initialize(APP_ARGS)
{
    nShowCmd				= SW_NORMAL;
    // ----
    Init(APP_ARGS_PUSH);
    // ----
    WNDCLASSEX wcex;
    wcex.cbSize				= sizeof(WNDCLASSEX);
    wcex.style				= CS_HREDRAW | CS_VREDRAW;
    wcex.cbClsExtra			= 0;
    wcex.cbWndExtra			= 0;
    wcex.hCursor			= LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground		= (HBRUSH)(COLOR_3DSHADOW + 1);
    // ----
    MyRegisterClass(MAIN_PROJECT_NAME, & wcex);
    MyWindowCreate(MAIN_PROJECT_WINDOW_WIDTH, MAIN_PROJECT_WINDOW_HEIGHT,
                   0, 0, WS_CAPTION | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME);
    // ----
    MoveToCenter();
    SetupMenu();
	// ----
	m_threadWorker = boost::thread(&TMain::Worker, this);
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::Run()
{
	while (g_Main.m_bWorkStop == false) {
		MsgLoop();
	}
	// ----
	m_threadWorker.join();
	// ----
	DestroyWindow(gHwnd);
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::MsgBox(char * szFormat, ...)
{
	static char szTemp[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, szFormat);
	vsprintf(szTemp, szFormat, pArguments);
	va_end(pArguments);
	// ----
	MessageBox(NULL, szTemp, "error", MB_OK | MB_APPLMODAL);
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::Worker()
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "Wokrer started.");
	// ----
	try {
		do {
			boost::this_thread::interruption_point();
			g_Log.LogTextPaint(gHwnd);

			boost::this_thread::sleep(boost::posix_time::milliseconds(m_iWorkerDelay));
		} while (m_bWorkStop == false);
	}
	catch (boost::thread_interrupted const&) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "THREAD INTERRUPTED !");
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::SetupMenu()
{
    BYTE ID	= 0x00;
    // ----
    MyCreateMenu();
    // ----
    ID = CreateMenuItem("&File");
    CreateSubMenuItem("&Exit", ID , (BYTE)CMD_EXIT);
	// ----
	ID = CreateMenuItem("&StartUP");
	CreateSubMenuItem("&ON", ID , (BYTE)CMD_AUTOSTARTUP_ON);
	CreateSubMenuItem("&OFF", ID , (BYTE)CMD_AUTOSTARTUP_OFF);
    // ----
    ID = CreateMenuItem("&Reload");
    CreateSubMenuItem("&Reload GMS Access", ID , (BYTE)CMD_RELOADGMS);
	// ----
	CreateSubMenuItem("&Reload INSPECTORS Access", ID , (BYTE)CMD_RELOADINSPECT);
	// ----
	CreateSubMenuItem("&Reload GS List", ID , (BYTE)CMD_RELOADGSSLIST);
	CreateSubMenuItem("&Reload RunEvent Cords", ID , (BYTE)CMD_RELOAD_RUNEVENT_CORDS);
    CreateSubMenuItem("&Reload WroteEvent Words", ID , (BYTE)CMD_RLEOAD_WROTEEVENT_WORDS);
	CreateSubMenuItem("&Reload ConfuseEvent Words", ID , (BYTE)CMD_RLEOAD_START_CONFUSED);
	CreateSubMenuItem("&Reload Processes", ID, (BYTE)CMD_RELOAD_PROCESSES);
	// ----
	ID = CreateMenuItem("&Start event");
    CreateSubMenuItem("&Start Targil Event", ID , (BYTE)CMD_START_TARGIL);
	CreateSubMenuItem("&Start RunEvent", ID , (BYTE)CMD_START_RUNEVENT);
	CreateSubMenuItem("&Start WroteEvent", ID , (BYTE)CMD_START_WROTEEVENT);
	CreateSubMenuItem("&Start LotteryEvent", ID , (BYTE)CMD_START_LOTTERYEVENT);
	CreateSubMenuItem("&Start ConfusedWordsEvent", ID , (BYTE)CMD_START_CONFUSED);
	// ----
	ID = CreateMenuItem("&Web");
	CreateSubMenuItem("&Start Messages", ID , (BYTE)CMD_START_MESSAGES);
	CreateSubMenuItem("&Stop Messages", ID , (BYTE)CMD_STOP_MESSAGES);
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnExit()
{
	m_bWorkStop = true;
	// ----
	m_threadWorker.interrupt();
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnCreate()
{
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnClose()
{
    if(MessageBoxA(gHwnd, "Are you sure?", "Close DataServerX", MB_YESNO) == IDYES)
    {
		this->OnExit();
    }
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnPaint()
{
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnSize()
{
    g_Log.LogTextPaint(gHwnd);
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnCmd(WPARAM Param, LPARAM lParam)
{
	switch (LOWORD(Param))
	{
	case(BYTE)CMD_EXIT:
	{
		OnClose();
	}
	break;

	case(BYTE)CMD_AUTOSTARTUP_ON:
	{
		TMain::autoStartup = true;
	}
	break;

	case(BYTE)CMD_AUTOSTARTUP_OFF:
	{
		TMain::autoStartup = false;
	}
	break;

	case(BYTE)CMD_RELOADGMS:
	{
		if (g_Config.readGmsAccessList(GMS_ACCESS_PATCH) == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "%s failed to read", GMS_ACCESS_PATCH);
		}
	}
	break;
	case(BYTE)CMD_RELOADINSPECT:
	{
		if (g_Config.readInspectAccessList(INSPECT_ACCESS_LIST_PATCH) == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "%s failed to read", INSPECT_ACCESS_LIST_PATCH);
		}
	}
	break;

	case(BYTE)CMD_RELOADGSSLIST:
	{
		if (g_Config.readGameServerList(GAMESERVER_LIST_PATCH) == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "%s failed to read", GAMESERVER_LIST_PATCH);
		}
	}
	break;

	case(BYTE)CMD_START_TARGIL:
	{
		TEventManager::start(
			TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_EXERISE,
			TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_ADMIN);
	}
	break;

	case(BYTE)CMD_START_RUNEVENT:
	{
		TEventManager::start(
			TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_RUN,
			TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_ADMIN);
	}
	break;

	case(BYTE)CMD_RELOAD_RUNEVENT_CORDS:
	{
		TRunEvent::LoadCords();
	}
	break;

	case(BYTE)CMD_START_WROTEEVENT:
	{
		TEventManager::start(
			TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_FASTWROTE,
			TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_ADMIN);
	}
	break;

	case(BYTE)CMD_RLEOAD_WROTEEVENT_WORDS:
	{
		TFastWrote::LoadWords();
	}
	break;

	case(BYTE)CMD_START_LOTTERYEVENT:
	{
		TEventManager::start(
			TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_LOTTERY,
			TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_ADMIN);
	}
	break;

	// # roye add
	case (BYTE)CMD_START_CONFUSED:
	{
		TEventManager::start(
			TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_CONFUSED,
			TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_ADMIN);
	}
	break;

	case (BYTE)CMD_RLEOAD_START_CONFUSED:
	{
		TConfusedEvent::LoadWords();
	}
	break;

	case (BYTE)CMD_START_MESSAGES:
	{
		MessagesWebState(false);
	}
	break;

	case (BYTE)CMD_STOP_MESSAGES:
	{
		MessagesWebState(true);
	}
	break;

	case (BYTE)CMD_RELOAD_PROCESSES:
	{
		g_Config.readBadProcesses(BAD_PROCESSES_LIST_PATCH);
		g_Config.readGoodProcesses(GOOD_PROCESSES_LIST_PATCH);
	}
	break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnApp(WPARAM wParam, LPARAM lParam)
{
    switch(wParam)
    {
    }
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnAppRange(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {

    }
}
//-----------------------------------------------------------------------------------------------------------------------

void TMain::OnTimer(WPARAM Param, LPARAM lParam)
{

}
//-----------------------------------------------------------------------------------------------------------------------