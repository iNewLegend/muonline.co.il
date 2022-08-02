//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"
#include "SRunEvent.h"
#include "GLog.h"
#include "Object.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TRunEvent"
//-----------------------------------------------------------------------------------------------------------------------

int TRunEvent_RoledCord  = 0;
int TRunEvent_CordsCount = 0;
//-----------------------------------------------------------------------------------------------------------------------

CORDS_MAP TRunEvent_CordsMap;
//-----------------------------------------------------------------------------------------------------------------------

RUNEVENT_STATE TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_NULL;
//-----------------------------------------------------------------------------------------------------------------------

bool TRunEvent::run(UINT minutesBeforeRun, bool isManualStart)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Green, "randomzie new time : randomTime : %d minute(s)", minutesBeforeRun);
	// ----
	// NOT USED
	//char szTemp[1024] = { 0 };
	//sprintf(szTemp, "אוונט רוץ ילד רוץ נקבע לעוד %d דקות", minutesBeforeRun);
	//ObjectSendNoticeAll(szTemp);
	// ----
	TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_WAIT2START;
	// ----
	boost::this_thread::sleep(boost::posix_time::minutes(minutesBeforeRun));
	// ----
	if (start(isManualStart)) {
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		} while (TRunEvent_RunState != RUNEVENT_STATE::RUNEVENT_STOPED);
		return true;
	}
	// ----
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

bool TRunEvent::LoadCords()
{
	bool bReturn = false;
	// ----
	if(TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_NULL || TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_CORDS_LOADED || TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_STOPED)
	{
		FILE * fileHandle = fopen(CORDS_FILE, "r");
		// ----
		if(fileHandle > 0)
		{
			TRunEvent_CordsMap.clear();
			// ----
			TRunEvent_CordsCount = 0;
			// ----
			char line[100] = {0};
			// ----
			while(fgets(line, sizeof line, fileHandle) != NULL)
			{
				tagCord Cord;
				// ----
				sscanf(line, "%d %d %d", & Cord.Map, & Cord.X, & Cord.Y);
				// ----
				TRunEvent_CordsMap[TRunEvent_CordsCount] = Cord;
				// ----
				++TRunEvent_CordsCount;
			}
			// ----
			fclose(fileHandle);
			// ----
			if(TRunEvent_CordsCount > 0)
			{
				bReturn = true;
				// ----
				TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_CORDS_LOADED;
			}
		}
		// ----
		if(bReturn == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "file %s loading error", CORDS_FILE);
		}
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to reload cords while event is running");
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------

void TRunEvent::stop()
{
	TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_STOPED;
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Green, "RunEvent is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

void TRunEvent::getWinner(std::string PlayerName, std::string AccountID)
{
	boost::mutex Guard;
	// ----
	if(TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_RUNNING)
	{
		Guard.lock();
		// ---- 
		std::string WHO_RUN = TEventManager::getEventOwner();
		// ----
		stop();
		// ----
		int Prize			= 0;
		int PrizeLog		= 0;
		int PrizeType		= 0;
		int	Random			= ObjectRandomize(1, 4);
		// ----
		TEventManager::increaseEventWins(AccountID, PlayerName);
		// ----
		switch(Random)
		{
			case 4:
			case PRIZE_TYPES::PRIZE_TYPE_SOULS:
			{
				Prize = ObjectRandomize(1, 30);
				// ----
				if(Prize <= 10)
				{
					Prize = 0;
					PrizeLog = 10;
				}
				else if(Prize <= 20)
				{
					Prize = 1;
					PrizeLog = 20;
				}
				else if(Prize <= 30)
				{
					Prize = 2;
					PrizeLog = 30;
				}
				// ----
				PrizeType = PRIZE_TYPE_SOULS;
				// ----
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Run", "Soul", PrizeLog);
			}
			break;

			case PRIZE_TYPES::PRIZE_TYPE_BLESS:
			{
				Prize = ObjectRandomize(1, 30);
				// ----
				if(Prize <= 10)
				{
					Prize = 0;
					PrizeLog = 10;
				}
				else if(Prize <= 20)
				{
					Prize = 1;
					PrizeLog = 20;
				}
				else if(Prize <= 30)
				{
					Prize = 2;
					PrizeLog = 30;
				}
				// ----
				PrizeType = PRIZE_TYPE_BLESS;
				// ----
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Run", "Bless", PrizeLog);
			}
			break;

			case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
			{
				Prize = ObjectRandomize(RUN_EVENT_PRIZE_RANGE);
				// ----
				ObjectIncraseCredits(AccountID, Prize);
				ObjectLogCreditAdd(PlayerName, AccountID, Prize, "RunEvent",4);
				// ----
				PrizeType = PRIZE_TYPE_CREDITS;
				// ----
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(),"Run", "Credits", Prize);
			}
			break;
		}
		// ----
		MSG_RUNEVENT_GIVEPRIZE pMsg = {0};
		// ----
		HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_RUNEVENT, RUNEVENT_SUBHEAD_GIVEPRIZE);
		// ---
		pMsg.Prize		= Prize;
		pMsg.PrizeType	= PrizeType;
		// ----
		memcpy(pMsg.szNick, PlayerName.c_str(), PlayerName.length());
		// ----
		Guard.unlock();
		// ----
		g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
		// ----
		g_MsgDisable.SendStartUpMsg();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

bool TRunEvent::start(bool isManualStart)
{
	bool bReturn = false;
	// ----
	if (TRunEvent_RunState == RUNEVENT_STATE::RUNEVENT_WAIT2START)
	{
		TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_STARTING;
		if (!isManualStart)
		{
			// ----
			ObjectSendNoticeAll("בעוד 5 דקות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 4 דקות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 3 דקות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 2 דקות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 1 דקות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 30 שניות יתחיל אוונט רוץ ילד רוץ");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 10 שניות יתחיל אוונט רוץ ילד רוץ");
			ObjectSendNoticeAll("תיהו מוכנים");
		}
		boost::this_thread::sleep(boost::posix_time::seconds(10));
		// ----
		TRunEvent_RoledCord = ObjectRandomize(0, TRunEvent_CordsCount);
		// ----
		MSG_RUNEVENT_START pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(pMsg), HEAD_RUNEVENT, RUNEVENT_SUBHEAD_START);
		// ----
		pMsg.Map = TRunEvent_CordsMap[TRunEvent_RoledCord].Map;
		pMsg.X = TRunEvent_CordsMap[TRunEvent_RoledCord].X;
		pMsg.Y = TRunEvent_CordsMap[TRunEvent_RoledCord].Y;
		// ----
		g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		// ----
		TRunEvent_RunState = RUNEVENT_STATE::RUNEVENT_RUNNING;
		// ----
		g_MsgDisable.SendStopMsgSystem();
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Green, "RunEvent is started !!!");
		// ----
		bReturn = true;
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to start RunEvent");
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------
