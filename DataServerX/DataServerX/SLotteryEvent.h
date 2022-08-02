//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#define LOTTERY_EVENT_PRIZE_RANGE				1,	 10
#define LOTTERY_EVENT_MINUTES_RANGE				60,  600
#define LOTTERY_EVENT_MILISECONDS_ANSWER_TICK	1000//3000
//-----------------------------------------------------------------------------------------------------------------------

struct tagMembers
{
	std::string		Name;
	BYTE			TryCount;
	DWORD			dwLastTryTick;
}
;
//-----------------------------------------------------------------------------------------------------------------------

enum LOTTERYEVENT_STATE
{
	LOTTERYEVENT_NULL,
	LOTTERYEVENT_WAIT2START,
	LOTTERYEVENT_STOPED,
	LOTTERYEVENT_STARTING,
	LOTTERYEVENT_RUNNING,
};
//-----------------------------------------------------------------------------------------------------------------------

struct tagParms
{
	int first;
	int second;
};
//-----------------------------------------------------------------------------------------------------------------------

#define LOTTERY_MEMBERS_LIST std::list<tagMembers>
//-----------------------------------------------------------------------------------------------------------------------

class TLotteryEvent
{
public:
	static bool	run(UINT minutesBeforeRun, bool isManualStart = false);
	static void	stop		();
	static void getWinner	(std::string PlayerName, std::string AccountID);
	static void getSender	(std::string PlayerName, UINT Number);

protected:
	static bool	start(bool isManualStart = false);
	static tagParms * getParam(int a, int b)
	{
		tagParms p;
		p.first = a;
		
	};

};
//-----------------------------------------------------------------------------------------------------------------------
extern LOTTERYEVENT_STATE TLotteryEvent_STATE;
//-----------------------------------------------------------------------------------------------------------------------