//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "GLog.h"
#include "SEventManager.h"
#include "SExerciseEvent.h"
#include "SConfusedEvent.h"
#include "SFastWrote.h"
#include "SRunEvent.h"
#include "SLotteryEvent.h"
#include "SGoldenEvent.h"
#include "VoteSystem.h"
#include "Object.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TEventManager"
//-----------------------------------------------------------------------------------------------------------------------

TEventManager::e_EVENT_OWNER TEventManager::eEVENT_OWNER		= TEventManager::e_EVENT_OWNER::e_EVENT_OWNER_NULLED;
TEventManager::e_EVENT_TYPES TEventManager::eEVENT_TYPE			= TEventManager::e_EVENT_TYPES::e_EVENT_TYPES_NULLED;
//-----------------------------------------------------------------------------------------------------------------------

bool TEventManager::bEVENT_LOCK = false;
UINT TEventManager::uEVENTS_COUNT = e_EVENT_TYPES::_END - 1;
//-----------------------------------------------------------------------------------------------------------------------

boost::shared_ptr<boost::thread> TEventManager::workerThread;
//-----------------------------------------------------------------------------------------------------------------------

std::string sGMEventOwnerName;
//-----------------------------------------------------------------------------------------------------------------------

bool TEventManager::isEventRunning()
{
	if (! isLocked()) return false;

	if (TConfusedWrote_State >= CONFUSED_STATE::CONFUSED_STARTING) {
		return true;
	}

	if (TExerciseEvent_runState >= TExerciseEvent_eRunState::STATE_STARTING) {
		return true;
	}

	if (TFastWrote_State >= FASTWROTE_STATE::FASTWROTE_STARTING) {
		return true;
	}

	if (TLotteryEvent_STATE >= LOTTERYEVENT_STATE::LOTTERYEVENT_STARTING) {
		return true;
	}

	if (TRunEvent_RunState >= RUNEVENT_STATE::RUNEVENT_STARTING) {
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

bool TEventManager::run(bool autoTime = true)
{
	if (TEventManager::bEVENT_LOCK == true || isVoteRunning) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Unable to Run Event Lock: %d, VoteSystem: %d",
			TEventManager::bEVENT_LOCK, isVoteRunning);
		return false;

	}
	bool bReturn = true;
	// ----
	lock();
	// ----
	auto minutesBeforeRun = 0;
	bool isManualStart = !autoTime;
	// ----
	switch (TEventManager::eEVENT_TYPE)
	{
	case e_EVENT_TYPES::e_EVENT_TYPES_EXERISE:
		if (autoTime) {
			minutesBeforeRun = ObjectRandomize(EXERCISE_TIMER_RANGE);
		}
		TExerciseEvent::run(minutesBeforeRun, isManualStart);
		break;

	case e_EVENT_TYPES::e_EVENT_TYPES_CONFUSED:
		if (autoTime) {
			minutesBeforeRun = ObjectRandomize(CONFUSED_WROTE_MINUTES_RANGE);
		}
		TConfusedEvent::run(minutesBeforeRun, isManualStart);
		break;

	case e_EVENT_TYPES::e_EVENT_TYPES_FASTWROTE:
		if (autoTime) {
			minutesBeforeRun = ObjectRandomize(FAST_WROTE_MINUTES_RANGE);
		}
		TFastWrote::run(minutesBeforeRun, isManualStart);
		break;

	case e_EVENT_TYPES::e_EVENT_TYPES_LOTTERY:
		if (autoTime) {
			minutesBeforeRun = ObjectRandomize(LOTTERY_EVENT_MINUTES_RANGE);
		}
		TLotteryEvent::run(minutesBeforeRun, isManualStart);
		break;

	case e_EVENT_TYPES::e_EVENT_TYPES_RUN:
		if (autoTime) {
			minutesBeforeRun = ObjectRandomize(LOTTERY_EVENT_MINUTES_RANGE);
		}
		TRunEvent::run(minutesBeforeRun, isManualStart);
		break;

	default:
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Event not found");
		// ----
		bReturn = false;
	}
	// ----
	unLock();
	// ----
	return bReturn;
}
//-----------------------------------------------------------------------------------------------------------------------

void TEventManager::worker()
{
	do {
		try {
			g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "START OK !");

			boost::this_thread::sleep(boost::posix_time::seconds(30));

			if (TEventManager::eEVENT_OWNER == e_EVENT_OWNER::e_EVENT_OWNER_GM || TEventManager::eEVENT_OWNER == e_EVENT_OWNER::e_EVENT_OWNER_ADMIN) {
				run(false);
			}

			e_EVENT_TYPES eEventType = (e_EVENT_TYPES)ObjectRandomize(e_EVENT_TYPES::e_EVENT_TYPES_NULLED, e_EVENT_TYPES::_END);

			if (TEventManager::start(eEventType, e_EVENT_OWNER::e_EVENT_OWNER_SYS)) {
				run(true);
			}

			g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "END OK !");
		}
		catch (boost::thread_interrupted const&) {
			g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "THREAD INTERRUPTED !");

			return;
		}
	} while (true);
}
//-----------------------------------------------------------------------------------------------------------------------

bool TEventManager::start(e_EVENT_TYPES eEventType, e_EVENT_OWNER eEventOwner)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::LightSlateGray, "Requested eventType: %d, eEventOwner: %d",
		eEventType, eEventOwner);

	if (eEventOwner == e_EVENT_OWNER::e_EVENT_OWNER_GM || eEventOwner == e_EVENT_OWNER::e_EVENT_OWNER_ADMIN) {
		stop();

		TEventManager::eEVENT_TYPE = eEventType;
		TEventManager::eEVENT_OWNER = eEventOwner;

		startWorker();

		return true;
	}

	if (false == isLocked() && false == isVoteRunning) {
		TEventManager::eEVENT_TYPE = eEventType;
		TEventManager::eEVENT_OWNER = eEventOwner;

		return true;
	}

	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Event already running eventType: %d, eEventOwner: %d",
		TEventManager::eEVENT_TYPE, TEventManager::eEVENT_OWNER);


	return false;
}
//-----------------------------------------------------------------------------------------------------------------------

bool TEventManager::startByGameMaster(e_EVENT_TYPES eEventType, std::string sGMName)
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "eventType: %d, GMName: %s",
		eEventType, sGMName.c_str());
	// ----
	sGMEventOwnerName = sGMName;
	// ----
	return start(eEventType, e_EVENT_OWNER::e_EVENT_OWNER_GM);
}
//-----------------------------------------------------------------------------------------------------------------------

void TEventManager::stop()
{
	g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "Attempting to stop events");
	// ----
	TExerciseEvent::stop();
	TConfusedEvent::stop();
	TFastWrote::stop();
	TLotteryEvent::stop();
	TRunEvent::stop();
	// ----
	TEventManager::workerThread->interrupt();
	// ----
	unLock();
}
//-----------------------------------------------------------------------------------------------------------------------

UINT TEventManager::increaseEventWins(std::string sAccountId, std::string sPlayerName)
{
	UINT uWinCount = 0;
	// ----
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "Select EventWins from Character where Name = '%s' and AccountID='%s'", sPlayerName.c_str(), sAccountId.c_str());
	g_DB.Fetch();
	// ---
	uWinCount = g_DB.GetInt("EventWins") + 1;
	// ---
	g_DB.Clear();
	// ----
	g_DB.ExecFormat(-1, g_ModuleName, __FUNCTION__, "Update Character Set EventWins=%d where Name = '%s' and AccountID='%s'", uWinCount, sPlayerName.c_str(), sAccountId.c_str());
	g_DB.Fetch();
	g_DB.Clear();
	// ----
	return uWinCount; 
}
//-----------------------------------------------------------------------------------------------------------------------

std::string TEventManager::getEventOwner()
{
	switch (TEventManager::eEVENT_OWNER)
	{
		case e_EVENT_OWNER::e_EVENT_OWNER_ADMIN:
			return "Admin";

		case e_EVENT_OWNER::e_EVENT_OWNER_GM:
			return sGMEventOwnerName;

		case e_EVENT_OWNER::e_EVENT_OWNER_SYS:
			return "System";
	}
	// ----
	return "Nulled";
}
//-----------------------------------------------------------------------------------------------------------------------