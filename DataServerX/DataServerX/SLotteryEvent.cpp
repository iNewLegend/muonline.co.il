//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "SLotteryEvent.h"
#include "Protocol.h"
#include "Object.h"
#include "TDataBase.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TLotteryEvent"
//-----------------------------------------------------------------------------------------------------------------------
	
UINT					TLotteryEvent_RolledNumber = 0;
//-----------------------------------------------------------------------------------------------------------------------

LOTTERYEVENT_STATE		TLotteryEvent_STATE			= LOTTERYEVENT_STATE::LOTTERYEVENT_STOPED;
//-----------------------------------------------------------------------------------------------------------------------

LOTTERY_MEMBERS_LIST	TLotteryEvent_Members;
//-----------------------------------------------------------------------------------------------------------------------

std::string		LastName;
DWORD			dwLastTick;
//-----------------------------------------------------------------------------------------------------------------------

bool TLotteryEvent::run(UINT minutesBeforeRun, bool isManualStart)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Purple, "randomzie new time : randomTime : %d minute(s)", minutesBeforeRun);
	// ----
	// NOT USED
	//char szTemp[1024] = { 0 };
	//sprintf(szTemp, "אוונט נחש את המספר נקבע לעוד %d דקות", minutesBeforeRun);
	//ObjectSendNoticeAll(szTemp);
	// ----
	TLotteryEvent_STATE = LOTTERYEVENT_STATE::LOTTERYEVENT_WAIT2START;
	// ----
	boost::this_thread::sleep(boost::posix_time::minutes(minutesBeforeRun));
	// ----
	if (start(isManualStart)) {
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		} while (TLotteryEvent_STATE != LOTTERYEVENT_STATE::LOTTERYEVENT_STOPED);
		return true;
	}
	// ----
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

void TLotteryEvent::stop()
{
	TLotteryEvent_STATE = LOTTERYEVENT_STOPED;
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Purple, "LotteryEvent is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

void TLotteryEvent::getWinner(std::string PlayerName, std::string AccountID)
{
	boost::mutex Guard;
	// ----
	if(TLotteryEvent_STATE == LOTTERYEVENT_STATE::LOTTERYEVENT_RUNNING)
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Lottery", "Soul", PrizeLog);
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
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Lottery", "Bless", PrizeLog);
			}
			break;

			case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
			{
				Prize = ObjectRandomize(LOTTERY_EVENT_PRIZE_RANGE);
				// ----
				ObjectIncraseCredits(AccountID, Prize);
				ObjectLogCreditAdd(PlayerName, AccountID, Prize, "LotteryEvent",4);
				// ----
				PrizeType = PRIZE_TYPE_CREDITS;
				// ----
				ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Lottery", "Credits", Prize);
			}
			break;
		}
		// ----
		MSG_LOTTERYEVENT_GIVEPRIZE pMsg = {0};
		// ----
		HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_LOTTERYEVENT, LOTTERYEVENT_SUBHEAD_GIVEPRIZE);
		// ---
		pMsg.Prize		= Prize;
		pMsg.PrizeType	= PrizeType;
		// ----
		memcpy(pMsg.szNick, PlayerName.c_str(), PlayerName.length());
		// ----
		Guard.unlock();
		// ----
		g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
		g_MsgDisable.SendStartUpMsg();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TLotteryEvent::getSender(std::string PlayerName, UINT Number)
{
	bool isOK = false;
	bool isTimeOk = false;
	// ----
	POINT p = {LOTTERY_EVENT_ROLLED_RANGE};
	// ----
	if(Number > p.y)
	{
		objectMsgToNick(PlayerName, "@ הניחוש שלך לא בטווח המספרים");
		// ----
		return;
	}
	if(Number < p.x)
	{
		objectMsgToNick(PlayerName, "@ המספר מתחת לטווח");
		// ----
		return;
	}
	// ----
	if(dwLastTick != 0)
	{
		if((GetTickCount() - dwLastTick) < LOTTERY_EVENT_MILISECONDS_ANSWER_TICK)
		{
			static char Temp[100] ; memset(Temp, 0, sizeof(Temp));
			// ----
			static int tickcalc = abs(tickcalc);
			// -----
			tickcalc = dwLastTick - GetTickCount();
			// ----
			tickcalc = abs(tickcalc);
			// -----
			if(tickcalc == 0)
			{
				tickcalc = 1;
			}
			else
			{
				tickcalc = tickcalc / 10;
			}
			// ----
			sprintf(Temp, "@ תפסו לך תתור ,נסה שוב");
			objectMsgToNick(PlayerName, Temp);
			//	sprintf(Temp, "@נותרו 0.%d שניות עד שתוכל לבחור מספר", tickcalc);
			//	objectMsgToNick(PlayerName, Temp);
			// ----
			return;
		}
	}
	// ---
	if(LastName == PlayerName)
	{
		objectMsgToNick(PlayerName, "@ אלייך לחכות לעוד מתמודד לפני הניחוש הבא");
		// ----
		return;
	}
	// ----
	if(TLotteryEvent_Members.empty() == true)
	{
		tagMembers Member;
		// ----
		Member.dwLastTryTick	= GetTickCount();
		Member.TryCount			= 1;
		Member.Name				= PlayerName;
		// ----
		dwLastTick				= GetTickCount();
		// ----
		TLotteryEvent_Members.push_back(Member);
		// ----
		isOK = true;
		// ----
		LastName = PlayerName;
	}
	else
	{
		bool isFound = false;
		// -----
		for(LOTTERY_MEMBERS_LIST::iterator it = TLotteryEvent_Members.begin() ; it != TLotteryEvent_Members.end(); ++it)
		{
			if(PlayerName == it->Name)
			{
				/*if((GetTickCount() - it->dwLastTryTick) < 425286357)
				{

				}*/
				if(LOTTERY_EVENT_TRY_COUNT == 0)
				{
					dwLastTick				= GetTickCount();
					LastName				= PlayerName;
					isOK					= true;
					// ----
					it->dwLastTryTick = GetTickCount();
				}
				else if(it->TryCount >= LOTTERY_EVENT_TRY_COUNT)
				{
					isOK = false;
				}
				else
				{
					LastName			= PlayerName;
					isOK				= true;
					dwLastTick			= GetTickCount();
					// ----
					++it->TryCount;
					// ----
					it->dwLastTryTick = GetTickCount();
				}
				// ----
				isFound = true;
				// ----
				break;
			}
		}
		// ----
		if(isFound == false)
		{
			tagMembers Member;
			// ----
			Member.dwLastTryTick	= GetTickCount();
			Member.TryCount			= 1;
			Member.Name				= PlayerName;
			// ----
			TLotteryEvent_Members.push_back(Member);
			// ----
			LastName		= PlayerName;
			isOK			= true;
			dwLastTick		= GetTickCount();
		}
	}
	// ----
	MSG_LOTTERYEVENT_GETSENDER pMsg = {0};
	// ----
	HeadSet2( & pMsg.Head, sizeof(pMsg), HEAD_LOTTERYEVENT, VDS_SUBPACKET_LOTTERYEVENT_HEADERS::LOTTERYEVENT_SUBHEAD_SENDERGET);
	// ----
	pMsg.bISOK		= isOK;
	pMsg.Number		= Number;
	// ----
	memcpy(pMsg.szNick, PlayerName.c_str(), PlayerName.length());
	// ----
	g_IOCP->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

bool TLotteryEvent::start(bool isManualStart)
{
	boost::posix_time::seconds seconds4(4);
	// ----
	bool bReturn = false;
	// ----
	if (TLotteryEvent_STATE == LOTTERYEVENT_STATE::LOTTERYEVENT_WAIT2START)
	{
		TLotteryEvent_Members.clear();
		// ----
		LastName.clear();
		// ----
		dwLastTick = 0;
		// ----
		TLotteryEvent_STATE = LOTTERYEVENT_STATE::LOTTERYEVENT_STARTING;
		if (!isManualStart) {
			// ----
			ObjectSendNoticeAll("בעוד 5 דקות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 4 דקות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 3 דקות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 2 דקות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 1 דקות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 30 שניות יתחיל אוונט נחש את המספר");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 10 שניות יתחיל אוונט נחש את המספר");
			ObjectSendNoticeAll("תיהו מוכנים");
		}
		boost::this_thread::sleep(boost::posix_time::seconds(10));
		// ----
		TLotteryEvent_RolledNumber = ObjectRandomize(LOTTERY_EVENT_ROLLED_RANGE);
		// ----
		MSG_LOTTERYEVENT_START pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(MSG_LOTTERYEVENT_START), HEAD_LOTTERYEVENT, LOTTERYEVENT_SUBHEAD_START);
		// ----
		pMsg.RolledNumber = TLotteryEvent_RolledNumber;
		// ----
		g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		// ----
		TLotteryEvent_STATE = LOTTERYEVENT_STATE::LOTTERYEVENT_RUNNING;
		// ----
		g_MsgDisable.SendStopMsgSystem();
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Purple, "LotteryEvent is started !!!");
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Purple, "LotteryEvent Numer: %d", TLotteryEvent_RolledNumber);
		// ----
		boost::this_thread::sleep(seconds4);
		// ----
		MSG_LOTTERYEVENT_START SecpMsg = { 0 };
		// ----
		HeadSet2(&SecpMsg.Head, sizeof(MSG_LOTTERYEVENT_START), HEAD_LOTTERYEVENT, LOTTERYEVENT_SUBHEAD_START_GO);
		// ----
		g_IOCP->sendAll((LPBYTE)& SecpMsg, sizeof(pMsg));
		// ----
		bReturn = true;
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to start LotteryEvent");
	}
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------