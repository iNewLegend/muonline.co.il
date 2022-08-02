//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "SExerciseEvent.h"
#include "VoteSystem.h"
#include "Object.h"
#include "GLog.h"
#include "GIOCPHandler.h"
#include "GMsgDisable.h"
#include "SEventManager.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TExerciseEvent"
//-----------------------------------------------------------------------------------------------------------------------

TExerciseEvent_eRunState TExerciseEvent_runState	= TExerciseEvent_eRunState::STATE_STOPED;
//-----------------------------------------------------------------------------------------------------------------------

tagExercise										TExerciseEvent_Exercise	= {0};
boost::shared_ptr<boost::thread>				TExerciseEvent_EventWorker;
//-----------------------------------------------------------------------------------------------------------------------

bool TExerciseEvent::run(UINT minutesBeforeRun, bool isManualStart)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "randomzie new time : randomTime : %d minute(s)", minutesBeforeRun);
	// ----
	TExerciseEvent_runState = TExerciseEvent_eRunState::STATE_WAIT2START;
	// ----
	boost::this_thread::sleep(boost::posix_time::minutes(minutesBeforeRun));
	// ----
	if (start(isManualStart)) {
		do {
			boost::this_thread::sleep(boost::posix_time::milliseconds(1));
		} while (TExerciseEvent_runState != TExerciseEvent_eRunState::STATE_STOPED);
		return true;
	}
	// ----
	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

void TExerciseEvent::stop()
{
	TExerciseEvent_runState = TExerciseEvent_eRunState::STATE_STOPED;
	// ----
	TExerciseEvent_Exercise.Answer = 0;
	TExerciseEvent_Exercise.Num1	= 0;
	TExerciseEvent_Exercise.Num2	= 0;
	TExerciseEvent_Exercise.Num3	= 0;
	// ----
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "Exercise event is stoped");
}
//-----------------------------------------------------------------------------------------------------------------------

void TExerciseEvent::getAnswer(std::string PlayerName, std::string AccountID, int Answer)
{
	boost::mutex Guard;
	// ----
	if(TExerciseEvent_runState == TExerciseEvent_eRunState::STATE_WORKING)
	{
		if(Answer == TExerciseEvent_Exercise.Answer)
		{
			Guard.lock();
			// ---- 
			std::string WHO_RUN = TEventManager::getEventOwner();
			// ----
			int Ans = TExerciseEvent_Exercise.Answer;
			// ----
			TExerciseEvent_EventWorker->interrupt();
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
					ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Exercise", "Soul", PrizeLog);
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
					ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Exercise", "Bless", PrizeLog);

				}
				break;

				case PRIZE_TYPES::PRIZE_TYPE_CREDITS:
				{
					Prize = ObjectRandomize(EXERCISE_PRIZE_RANGE);
					// ----
					ObjectIncraseCredits(AccountID, Prize);
					ObjectLogCreditAdd(PlayerName, AccountID, Prize, "EventTargil",4);
					// ----
					PrizeType = PRIZE_TYPE_CREDITS;
					// ----
					ObjectLogEventAdd(PlayerName.c_str(), AccountID.c_str(), WHO_RUN.c_str(), "Exercise", "Credits", Prize);
				}
				break;
			}
			// ----
			MSG_EXERCISE_GIVEPRIZE pMsg = {0};
			// ----
			HeadSet2(& pMsg.Head, sizeof(pMsg), HEAD_EXERCISESYSTEM, EXERCISESYSTEM_SUBHEAD_GIVEPRIZE);
			// ---
			pMsg.An			= Ans;
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
		else
		{
			objectMsgToNick(PlayerName, "@[Targil] התשובה לא נכונה נסה , שוב");
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TExerciseEvent::eventWorker()
{
	try {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "START OK !");
		// ----
		boost::mutex Guard;
		// ----
		boost::posix_time::seconds workTime(EXERCISE_EVENT_TIME);
		boost::this_thread::sleep(workTime);
		// ----
		if (TExerciseEvent_runState == TExerciseEvent_eRunState::STATE_WORKING)
		{
			Guard.lock();
			// ----
			int Ans = TExerciseEvent_Exercise.Answer;
			// ----
			stop();
			// ----
			MSG_EXERCISE_GIVEPRIZE pMsg = { 0 };
			// ----
			HeadSet2(&pMsg.Head, sizeof(pMsg), HEAD_EXERCISESYSTEM, EXERCISESYSTEM_SUBHEAD_GIVEPRIZE);
			// ---
			pMsg.Prize = 0;
			pMsg.PrizeType = PRIZE_TYPE_NULL;
			pMsg.An = Ans;
			// ----
			Guard.unlock();
			// ----
			g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		}
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "DONE OK !");
	}
	catch (boost::thread_interrupted const&) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "THREAD INTERRUPTED !");
	}
}
//-----------------------------------------------------------------------------------------------------------------------

bool TExerciseEvent::start(bool isManualStart)
{
	bool bReturn = false;
	// ----
	if (TExerciseEvent_runState == TExerciseEvent_eRunState::STATE_WAIT2START)
	{
		TExerciseEvent_runState = TExerciseEvent_eRunState::STATE_STARTING;
		if (!isManualStart)
		{
			// ----
			ObjectSendNoticeAll("בעוד 5 דקות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 4 דקות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 3 דקות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 2 דקות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::minutes(1));
			// ----
			ObjectSendNoticeAll("בעוד 1 דקות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 30 שניות יתחיל אוונט התרגיל");
			boost::this_thread::sleep(boost::posix_time::seconds(30));
			// ----
			ObjectSendNoticeAll("בעוד 10 שניות אוונט התרגיל");
			ObjectSendNoticeAll("תיהו מוכנים");
			boost::this_thread::sleep(boost::posix_time::seconds(10));
			// ----
		}
		TExerciseEvent_Exercise.Num1 = ObjectRandomize(ExerciseRangeNUM1);
		TExerciseEvent_Exercise.Num2 = ObjectRandomize(ExerciseRangeNUM2);
		TExerciseEvent_Exercise.Num3 = ObjectRandomize(ExerciseRangeNUM3);
		// ----
		TExerciseEvent_Exercise.Answer = (TExerciseEvent_Exercise.Num1 + TExerciseEvent_Exercise.Num2 + TExerciseEvent_Exercise.Num3);
		// ----
		MSG_EXERCISE_START pMsg = { 0 };
		// ----
		HeadSet2(&pMsg.Head, sizeof(pMsg), HEAD_EXERCISESYSTEM, EXERCISESYSTEM_SUBHEAD_START);
		// ----
		pMsg.Num1 = TExerciseEvent_Exercise.Num1;
		pMsg.Num2 = TExerciseEvent_Exercise.Num2;
		pMsg.Num3 = TExerciseEvent_Exercise.Num3;
		// ----
		TExerciseEvent_EventWorker = boost::shared_ptr<boost::thread>(new boost::thread(eventWorker));
		// ----
		g_IOCP->sendAll((LPBYTE)& pMsg, sizeof(pMsg));
		// ----							    
		TExerciseEvent_runState = TExerciseEvent_eRunState::STATE_WORKING;
		// ----
		g_MsgDisable.SendStopMsgSystem();
		// ----
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "Exercise event is started");
		// ----
		bReturn = true;
	}
	else
	{
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to start Exercise event");
	}
	// ----
	return bReturn;

}
//-----------------------------------------------------------------------------------------------------------------------
