//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "GMain.h"
#include "GLog.h"
#include "GConfig.h"
#include "SRunEvent.h"
#include "SFastWrote.h"
#include "SConfusedEvent.h"
#include "Object.h"
#include "SEventManager.h"
#include "SAutoMessageManager.h"
#include "GMsgDisable.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "EnteryPoint"
//-----------------------------------------------------------------------------------------------------------------------

void StartUp()
{
	if(HeapSetInformation(GetProcessHeap(), HeapEnableTerminationOnCorruption, NULL, 0) == 0) {
		g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "heap failed");
	}
	// ----
	g_Config.readGmsAccessList(GMS_ACCESS_PATCH);
	g_Config.readInspectAccessList(INSPECT_ACCESS_LIST_PATCH);
	g_Config.readGameServerList(GAMESERVER_LIST_PATCH);
	g_Config.readBadProcesses(BAD_PROCESSES_LIST_PATCH);
	g_Config.readGoodProcesses(GOOD_PROCESSES_LIST_PATCH);
	// ----
	TRunEvent::LoadCords();
	TFastWrote::LoadWords();
	TConfusedEvent::LoadWords();
	// ----
	objectInit();
	// ----
	boost::shared_ptr<TIOCPHandler> h(new TIOCPHandler());
	// ----
	g_IOCP = h;
	// ----
	gDSIocp = new iocp::CIocpServer(555, h); // 7575 9999
	// ----
	TEventManager::startWorker();
	TAutoMessageManager::Start();
	g_MsgDisable.startWorker();
	// ----
	MessagesWebState(false);
}
//-----------------------------------------------------------------------------------------------------------------------

APP_MAIN(APP_ARGS)
{
	#ifdef _DEBUG
		g_Log.LogInit(true, "./../logs");
	#else
		g_Log.LogInit(true, "D:\\LOGS\\DataServerX");
	#endif

	g_Log.Add(-1, g_ModuleName, __FUNCTION__, (char *)"Log Initialize...");
	// ----
	g_Main.Initialize(APP_ARGS_PUSH);
	// ----
	StartUp();
	// ----
	g_Main.Run();
    // ----
    return SUCCESS;
}
//-----------------------------------------------------------------------------------------------------------------------