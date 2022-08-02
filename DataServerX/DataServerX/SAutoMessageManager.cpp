//-----------------------------------------------------------------------------------------------------------------------
// # Made by RoyeGM (Roye Elmaz)
// # mail	 : elmazr@walla.com
// # skype	 : elmazr21
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "SAutoMessageManager.h"
#include "Protocol.h"
#include "TDataBase.h"
#include "Object.h"

#define g_ModuleName "TAutoMessageManager"

struct AutoMessage
{
	std::string strMsg;
	short nTicks;
	short nAlreadyTicks;
};
typedef AutoMessage* LPAutoMsg;

std::vector<AutoMessage> mMessages;

void TAutoMessageManager::Start()
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Blue, "Starting Auto Message System");

	loadMessages();

	boost::thread make_thread(&TAutoMessageManager::worker);
}


void TAutoMessageManager::loadMessages()
{
	char msg[100] = { 0 };


	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::AliceBlue, "Starting Loading Auto Message System Messages");

	g_DB.Clear();
	bool returnVal = g_DB.Exec(-1, g_ModuleName, __FUNCTION__, (char *)"SELECT Msg, Ticks FROM muonline.dbo.AutoMessages");	
	// ----
	if (returnVal == false)
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Failed to execute loading of auto messages");
		return;
	}

	while (g_DB.Fetch() != SQL_NO_DATA)
	{
			AutoMessage autoMessage;
			// ----
			g_DB.GetStr("Msg", msg);
			autoMessage.nTicks = g_DB.GetInt("Ticks");
			autoMessage.nAlreadyTicks = 0;
			autoMessage.strMsg = msg;
			// ----
			g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::White, "Loaded Message %s with Tick Count of %d", autoMessage.strMsg.c_str(), autoMessage.nTicks);
			mMessages.push_back(autoMessage);
	}
	// ----
	g_DB.Clear();
}

void TAutoMessageManager::worker()
{
	try {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "START OK !");

		while (true) {
			g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Orange, "[Auto Message System] Tick Occured");

			for (std::vector<AutoMessage>::iterator it = mMessages.begin(); it != mMessages.end(); ++it) {
				AutoMessage msg = (*it);
				msg.nAlreadyTicks += 1;

				if (msg.nAlreadyTicks == msg.nTicks)
				{
					msg.nAlreadyTicks = 0;

					SendMessageToAllServers(msg.strMsg.c_str());
				}
			}

			boost::this_thread::sleep(boost::posix_time::minutes(1));
		}
	}
	catch (boost::thread_interrupted const&) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "THREAD INTERRUPTED !");
	}
}