//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

class TEventManager
{
protected:
	static bool run		(bool autoTime);
	static void worker	();

private:
	static boost::shared_ptr<boost::thread> workerThread;

public:
	static enum e_EVENT_OWNER
	{
		e_EVENT_OWNER_NULLED = 0,
		e_EVENT_OWNER_SYS,
		e_EVENT_OWNER_ADMIN,
		e_EVENT_OWNER_GM
	};

	static enum e_EVENT_TYPES
	{
		e_EVENT_TYPES_NULLED = 0,
		e_EVENT_TYPES_CONFUSED,
		e_EVENT_TYPES_EXERISE,
		e_EVENT_TYPES_FASTWROTE,
		e_EVENT_TYPES_LOTTERY,
		e_EVENT_TYPES_RUN,
		e_EVENT_TYPES_GOLDEN,
		_END, // simple hack reversed for uEVENTS_COUNT
	};

	static e_EVENT_OWNER eEVENT_OWNER;
	static e_EVENT_TYPES eEVENT_TYPE;
	static UINT uEVENTS_COUNT;
	static bool bEVENT_LOCK;

	static bool isEventRunning		();
	static bool start				(e_EVENT_TYPES eEventType, e_EVENT_OWNER eEventOwner);
	static bool startByGameMaster	(e_EVENT_TYPES eEventType, std::string sGMName);
	static void stop				();

	static UINT increaseEventWins	(std::string sAccountId, std::string sPlayerName);

	static std::string getEventOwner	();

	static void lock		() { bEVENT_LOCK = true; };
	static void unLock		() { bEVENT_LOCK = false; };
	static bool isLocked	() { return bEVENT_LOCK; };

	static void startWorker()
	{
		TEventManager::workerThread = boost::shared_ptr<boost::thread>(new boost::thread(TEventManager::worker));
	};

};
//-----------------------------------------------------------------------------------------------------------------------

extern std::string WHO_RUN_THE_EVENT;
//-----------------------------------------------------------------------------------------------------------------------
