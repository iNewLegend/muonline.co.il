//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"
#include "SGoldenEvent.h"
#include "GLog.h"
#include "Object.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TGoldenEvent"
//-----------------------------------------------------------------------------------------------------------------------

e_GOLDEN_STATE TGoldenEvent::eEventState = e_GOLDEN_STATE::e_GOLDEN_STATE_NULL;
//-----------------------------------------------------------------------------------------------------------------------

BYTE TGoldenEvent::PrizeAmount = 1;
//-----------------------------------------------------------------------------------------------------------------------

void TGoldenEvent::run()
{
	int randomtime = ObjectRandomize(0xFF, 0xEEEE);
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Plum, "randomzie new time : randomTime : %d minute(s)", randomtime);
	// ----
	boost::posix_time::minutes workTime(randomtime);

	boost::this_thread::sleep(workTime);
	// ----
	start();
}
//-----------------------------------------------------------------------------------------------------------------------

void TGoldenEvent::stop()
{
	TGoldenEvent::eEventState = e_GOLDEN_STATE::e_GOLDEN_STATE_STOPED;
	// ----
	// SEND INFO TO GS EVENT STOPED
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Plum, "GoldenEvent is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

/**
	goldenDie - Called When monster die and credit should be gived

	@param sAccountId std::string 
	@param sName std::string
	@return void
*/
void TGoldenEvent::goldenDie(TIOCPHandler * h, uint64_t cid, std::string sAccountId, std::string sName)
{
	if (TGoldenEvent::eEventState != e_GOLDEN_STATE::e_GOLDEN_STATE_RUNNING) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Event is not running !!!");
		return;
	}
	// ----
	boost::mutex Guard;
	char temp[1024] = { 0 };
	// ----
	Guard.lock();
	// ----
	TEventManager::increaseEventWins(sAccountId, sName);
	// ----
	ObjectIncraseCredits(sAccountId, TGoldenEvent::PrizeAmount);
	ObjectLogCreditAdd(sName, sAccountId, TGoldenEvent::PrizeAmount, "GoldenEvent", 4);
	ObjectLogEventAdd(sName, sAccountId, "No One", "GoldenEvent", "Credits", TGoldenEvent::PrizeAmount);
	// ----
	sprintf(temp, "[GoldenEvent] %s has killed golden monster", sName.c_str());
	ObjectSendNoticeAll(temp);
	// ----
	sprintf(temp, "[GoldenEvent] You killed golden and got %d credits", TGoldenEvent::PrizeAmount);
	objectMsgToNick(sName, temp);
	// ----
	
}
//-----------------------------------------------------------------------------------------------------------------------

bool TGoldenEvent::start()
{
	boost::mutex Guard;
	// ----
	if (TGoldenEvent::eEventState > e_GOLDEN_STATE::e_GOLDEN_STATE_STOPED) {
		stop();
	}
	// ----
	Guard.lock();
	// ----
	TGoldenEvent::eEventState = e_GOLDEN_STATE::e_GOLDEN_STATE_STARTING;
	// ----
	boost::posix_time::minutes oneMinute(1);
	boost::posix_time::seconds halfMinute(30);
	boost::posix_time::seconds tenSeconds(10);
	// ----
	ObjectSendNoticeAll("[GoldenEvent] Will start more 3 minutes");
	boost::this_thread::sleep(oneMinute);
	// ----
	ObjectSendNoticeAll("[GoldenEvent] Will start more 2 minutes");
	boost::this_thread::sleep(oneMinute);
	// ----
	ObjectSendNoticeAll("[GoldenEvent] Will start more 1 minute");
	boost::this_thread::sleep(halfMinute);
	// ----
	ObjectSendNoticeAll("[GoldenEvent] Will start more 30 seconds");
	boost::this_thread::sleep(halfMinute);
	// ----
	ObjectSendNoticeAll("[GoldenEvent] Is about to start in 10 seconds");
	boost::this_thread::sleep(tenSeconds);
	// ----
	MSG_RUNEVENT_START pMsg = { 0 };
	// ----
	HeadSet2(&pMsg.Head, sizeof(MSG_GOLDENEVENT_START), HEAD_GOLDEN_EVENT, GOLDEN_EVENT_SUBHEAD_START);
	// ----
	Guard.unlock();
	// ----
	g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Plum, "GoldenEvent is started !!!");
	// ----
	TGoldenEvent::eEventState = e_GOLDEN_STATE::e_GOLDEN_STATE_RUNNING;
	// ----
	return true;
}
//-----------------------------------------------------------------------------------------------------------------------
