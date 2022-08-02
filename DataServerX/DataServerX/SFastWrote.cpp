//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"
#include "SFastWrote.h"
#include "GLog.h"
#include "Object.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TFastWrote"
//-----------------------------------------------------------------------------------------------------------------------

int TFastWrote_RoledWord  = 0;
int TFastWrote_WordsCount = 0;
//-----------------------------------------------------------------------------------------------------------------------

FAST_WROTE_WORDS_MAP TFastWrote_CordsMap;
//-----------------------------------------------------------------------------------------------------------------------

FASTWROTE_STATE TFastWrote_State = FASTWROTE_STATE::FASTWROTE_NULL;
//-----------------------------------------------------------------------------------------------------------------------

bool TFastWrote::run(UINT minutesBeforeRun, bool isManualStart)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Sienna, "randomzie new time : randomTime : %d minute(s)", minutesBeforeRun);
	// ----
	// ----
	TFastWrote_State = FASTWROTE_STATE::FASTWROTE_WAIT2START;
	// ----
	boost::this_thread::sleep(boost::posix_time::minutes(minutesBeforeRun));
	// ---
	if (start(isManualStart)) {
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		} while (TFastWrote_State != FASTWROTE_STATE::FASTWROTE_STOPED);
		return true;
	}
	// ----
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

bool TFastWrote::LoadWords()
{
	bool bReturn = false;
	// ----
	if(TFastWrote_State == FASTWROTE_STATE::FASTWROTE_NULL ||
		TFastWrote_State == FASTWROTE_STATE::FASTWROTE_WORDS_LOADED ||
		TFastWrote_State == FASTWROTE_STATE::FASTWROTE_STOPED)
	{
		FILE * fileHandle = fopen(FAST_WROTE_WORDS_FILE, "r");
		// ----
		if(fileHandle > 0)
		{
			TFastWrote_CordsMap.clear();
			// -----
			TFastWrote_WordsCount = 0;
			// ----
			char line[200] = {0};
			// ----
			while(fgets(line, sizeof line, fileHandle) != NULL)
			{
				tagFastWrote fastWords;
				// ----
				char Temp1[100] = {0};
				char Temp2[100] = {0};
				char Temp3[100] = {0};
				char Temp4[100] = {0};
				// ----
				sscanf(line, "%s %s %s %s", & Temp1, & Temp2, & Temp3, Temp4);
				// ----
				fastWords.word1 = Temp1;
				fastWords.word2 = Temp2;
				fastWords.word3 = Temp3;
				fastWords.word4 = Temp4;
				// ----
				TFastWrote_CordsMap[TFastWrote_WordsCount] = fastWords;
				// ----
				++TFastWrote_WordsCount;
			}
			// -----
			fclose(fileHandle);
			// -----
			if(TFastWrote_WordsCount > 0)
			{
				bReturn = true;
				// ----
				TFastWrote_State = FASTWROTE_STATE::FASTWROTE_WORDS_LOADED;
			}
		}
		if(bReturn == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "file %s loading error", FAST_WROTE_WORDS_FILE);
		}
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to reload words while event is running");
	}
	// ----
	//#define DEBUGLOAD
	#ifdef DEBUGLOAD
	for(WORDS_MAP::iterator it = TFastWrote_CordsMap.begin(); it != TFastWrote_CordsMap.end() ; ++it)
	{
		g_Log.AddC(-1, "NULL","NULL", TColor::Pink, "%s %s %s %s", 
			it->second.word1.c_str(),
			it->second.word2.c_str(),
			it->second.word3.c_str(),
			it->second.word4.c_str());
	}
	#endif
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------

void TFastWrote::stop()
{
	TFastWrote_State = FASTWROTE_STATE::FASTWROTE_STOPED;
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Sienna, "WroteEvent is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

void TFastWrote::getWinner(std::string PlayerName, std::string AccountID)
{
	boost::mutex Guard;
	// ----
	if(TFastWrote_State == FASTWROTE_STATE::FASTWROTE_RUNNING)
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "FastWord", "Soul", PrizeLog);
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "FastWord", "Bless", PrizeLog);
			}
			break;

			case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
			{
				Prize = ObjectRandomize(FAST_WROTE_PRIZE_RANGE);
				// ----
				ObjectIncraseCredits(AccountID, Prize);
				ObjectLogCreditAdd(PlayerName, AccountID, Prize, "FastWrote",4);
				// ----
				PrizeType = PRIZE_TYPE_CREDITS;
				// ----
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "FastWord", "Credits", Prize);
			}
			break;
		}
		// ----
		MSG_WROTEEVENT_GIVEPRIZE pMsg = {0};
		// ----
		HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_WROTEEVENT, WROTEEVENT_SUBHEAD_GIVEPRIZE);
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

bool TFastWrote::start(bool isManualStart)
{
	bool bReturn = false;
	// ----
	if (TFastWrote_State == FASTWROTE_STATE::FASTWROTE_WAIT2START)
	{
		TFastWrote_State = FASTWROTE_STATE::FASTWROTE_STARTING;
		if (!isManualStart) {
			// ----	
			ObjectSendNoticeAll("בעוד 5 דקות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 4 דקות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----			
			ObjectSendNoticeAll("בעוד 3 דקות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 2 דקות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 1 דקות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 30 שניות יתחיל אוונט זריזות");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 10 שניות יתחיל אוונט זריזות");
			ObjectSendNoticeAll("תיהו מוכנים");
			boost::this_thread::sleep(boost::posix_time::seconds(10));
			// ----	
		}
		TFastWrote_RoledWord = ObjectRandomize(0, TFastWrote_WordsCount);
		// ----
		MSG_WROTEEVENT_START pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(MSG_WROTEEVENT_START), HEAD_WROTEEVENT, WROTEEVENT_SUBHEAD_START);
		// ----
		memcpy(pMsg.Word1,
			TFastWrote_CordsMap[TFastWrote_RoledWord].word1.c_str(),
			TFastWrote_CordsMap[TFastWrote_RoledWord].word1.length());
		// ----
		memcpy(pMsg.Word2,
			TFastWrote_CordsMap[TFastWrote_RoledWord].word2.c_str(),
			TFastWrote_CordsMap[TFastWrote_RoledWord].word2.length());
		// ----
		memcpy(pMsg.Word3,
			TFastWrote_CordsMap[TFastWrote_RoledWord].word3.c_str(),
			TFastWrote_CordsMap[TFastWrote_RoledWord].word3.length());
		// ----
		memcpy(pMsg.Word4,
			TFastWrote_CordsMap[TFastWrote_RoledWord].word4.c_str(),
			TFastWrote_CordsMap[TFastWrote_RoledWord].word4.length());
		// ----
		g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		// ----
		TFastWrote_State = FASTWROTE_STATE::FASTWROTE_RUNNING;
		// ----
		g_MsgDisable.SendStopMsgSystem();
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Sienna, "WroteEvent is started !!!");
		// ----
		bReturn = true;
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to start WroteEvent");
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------