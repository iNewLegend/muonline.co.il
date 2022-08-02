//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "Protocol.h"
#include "SConfusedEvent.h"
#include "GLog.h"
#include "SExerciseEvent.h"
#include "Object.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TConfusedEvent"
//-----------------------------------------------------------------------------------------------------------------------

int TConfusedWrote_RoledWord  = 0;
int TConfusedWrote_WordsCount = 0;
//-----------------------------------------------------------------------------------------------------------------------

CONFUSED_WORDS_MAP TConfusedWrote_CordsMap;
//-----------------------------------------------------------------------------------------------------------------------

CONFUSED_STATE TConfusedWrote_State = CONFUSED_STATE::CONFUSED_NULL;
//-----------------------------------------------------------------------------------------------------------------------

bool TConfusedEvent::run(UINT minutesBeforeRun, bool isManualStart)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Olive, "randomzie new time : randomTime : %d minute(s)", minutesBeforeRun);
	// ----
	// Not used
	//char szTemp[1024] = { 0 };
	//sprintf(szTemp, "אוונט המילים המבולבלות נקבע לעוד %d דקות", minutesBeforeRun);
	//ObjectSendNoticeAll(szTemp);
	// ----
	TConfusedWrote_State = CONFUSED_STATE::CONFUSED_WAIT2START;
	// ----
	boost::this_thread::sleep(boost::posix_time::minutes(minutesBeforeRun));
	// ----
	if (start(isManualStart)) {
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		} while (TConfusedWrote_State != CONFUSED_STATE::CONFUSED_STOPED);
		return true;
	}
	// ----
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

bool TConfusedEvent::LoadWords()
{
	bool bReturn = false;
	// ----
	if(TConfusedWrote_State == CONFUSED_STATE::CONFUSED_NULL ||
		TConfusedWrote_State == CONFUSED_STATE::CONFUSED_WORDS_LOADED ||
		TConfusedWrote_State == CONFUSED_STATE::CONFUSED_STOPED)
	{
		FILE * fileHandle = fopen(CONFUSED_WORDS_FILE, "r");
		// ----
		if(fileHandle > 0)
		{
			TConfusedWrote_CordsMap.clear();
			// -----
			TConfusedWrote_WordsCount = 0;
			// ----
			char line[200] = {0};
			// ----
			while(fgets(line, sizeof line, fileHandle) != NULL)
			{
				tagConfusedWrote ConfWords;
				// ----
				char Temp1[100] = {0};
				char Temp2[100] = {0};
				char Temp3[100] = {0};
				char Temp4[100] = {0};
				char Temp5[100] = {0};
				char Temp6[100] = {0};
				char Temp7[100] = {0};
				char Temp8[100] = {0};

				// ----
				sscanf(line, "%s %s %s %s %s %s %s %s", & Temp1, & Temp2, & Temp3, &Temp4 ,& Temp5, & Temp6, & Temp7, Temp8);
				// ----
				ConfWords.word1 = Temp5;
				ConfWords.word2 = Temp6;
				ConfWords.word3 = Temp7;
				ConfWords.word4 = Temp8;
				ConfWords.word5 = Temp1;
				ConfWords.word6 = Temp2;
				ConfWords.word7 = Temp3;
				ConfWords.word8 = Temp4;
				// ----
				TConfusedWrote_CordsMap[TConfusedWrote_WordsCount] = ConfWords;
				// ----
				++TConfusedWrote_WordsCount;
			}
			// -----
			fclose(fileHandle);
			// -----
			if(TConfusedWrote_WordsCount > 0)
			{
				bReturn = true;
				// ----
				TConfusedWrote_State = CONFUSED_STATE::CONFUSED_WORDS_LOADED;
			}
		}
		if(bReturn == false)
		{
			g_Log.AddMSB(-1, g_ModuleName, __FUNCTION__, "file %s loading error", CONFUSED_WORDS_FILE);
		}
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to reload words while event is running");
	}
	// ----
	//#define DEBUGLOAD
	#ifdef DEBUGLOAD
	for(CONFUSED_WORDS_MAP::iterator it = TFastWrote_CordsMap.begin(); it != TFastWrote_CordsMap.end() ; ++it)
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

void TConfusedEvent::stop()
{
	TConfusedWrote_State = CONFUSED_STATE::CONFUSED_STOPED;
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Olive, "ConfusedEvent is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

void TConfusedEvent::getWinner(std::string PlayerName, std::string AccountID)
{
	boost::mutex Guard;
	// ----
	if(TConfusedWrote_State == CONFUSED_STATE::CONFUSED_RUNNING)
	{
		Guard.lock();
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
		std::string WHO_RUN = TEventManager::getEventOwner();
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "CunfusedWord", "Soul", PrizeLog);
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "CunfusedWord", "Bless", PrizeLog);
			}
			break;

			case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
			{
				Prize		= ObjectRandomize(CONFUSED_WROTE_PRIZE_RANGE);
				PrizeType	= PRIZE_TYPE_CREDITS;
				// ----
				ObjectIncraseCredits(AccountID, Prize);
				ObjectLogCreditAdd(PlayerName, AccountID, Prize, "ConfusedWrote",4);
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "CunfusedWord", "Credits", Prize);
			}
			break;
		}
		// ----
		MSG_CONFUSEEVENT_GIVEPRIZE pMsg = {0};
		// ----
		HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_CONFUSEEVENT, CONFUSEEVENT_SUBHEAD_GIVEPRIZE);
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

bool TConfusedEvent::start(bool isManualStart)
{
	bool bReturn = false;
	// ----
	if (TConfusedWrote_State == CONFUSED_STATE::CONFUSED_WAIT2START) {
		TConfusedWrote_State = CONFUSED_STATE::CONFUSED_STARTING;
		TConfusedWrote_RoledWord = ObjectRandomize(0, TConfusedWrote_WordsCount);
		
		if (!isManualStart)
		{
			// ----
			ObjectSendNoticeAll("בעוד 5 דקות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 4 דקות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 3 דקות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 2 דקות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 1 דקות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 30 שניות יתחיל אוונט המילים המבולבלות");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 10 שניות יתחיל אוונט המילים המבולבלות");
			ObjectSendNoticeAll("תהיו מוכנים");
			boost::this_thread::sleep(boost::posix_time::seconds(10));
		}
		// ----
		MSG_CONFUSEEVENT_START pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(MSG_CONFUSEEVENT_START), HEAD_CONFUSEEVENT, CONFUSEEVENT_SUBHEAD_START);
		// ----
		memcpy(pMsg.Word1,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word1.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word1.length());
		// ----
		memcpy(pMsg.Word2,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word2.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word2.length());
		// ----
		memcpy(pMsg.Word3,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word3.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word3.length());
		// ----
		memcpy(pMsg.Word4,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word4.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word4.length());
		// ----
		memcpy(pMsg.Word5,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word5.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word5.length());
		// ----
		memcpy(pMsg.Word6,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word6.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word6.length());
		// ----
		memcpy(pMsg.Word7,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word7.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word7.length());
		// ----
		memcpy(pMsg.Word8,
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word8.c_str(),
			TConfusedWrote_CordsMap[TConfusedWrote_RoledWord].word8.length());
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Olive, "ConfusedEvent is started %s %s %s %s %s %s %s %s", pMsg.Word1, pMsg.Word2, pMsg.Word3, pMsg.Word4, pMsg.Word5, pMsg.Word6, pMsg.Word7, pMsg.Word8);
		// ----
		g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		// ----
		TConfusedWrote_State = CONFUSED_STATE::CONFUSED_RUNNING;
		// ----
		g_MsgDisable.SendStopMsgSystem();
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Olive, "ConfusedEvent is started !!!");
		// ----
		bReturn = true;

	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to start ConfusedEvent");
	}

	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------
