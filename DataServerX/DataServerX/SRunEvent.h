//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include <map>
#include <boost\thread.hpp>
//-----------------------------------------------------------------------------------------------------------------------

#define RUN_EVENT_PRIZE_RANGE			1, 10
#define RUN_EVENT_TIME_MINUTES_RANGE	60, 300
//-----------------------------------------------------------------------------------------------------------------------

#define CORDS_FILE	"./RunEvent_Cords.txt"
#define CORDS_MAP	std::map<int, tagCord>
//-----------------------------------------------------------------------------------------------------------------------

struct tagCord
{
	int Map;
	int X;
	int Y;
};
//-----------------------------------------------------------------------------------------------------------------------

enum RUNEVENT_STATE
{
	RUNEVENT_NULL,
	RUNEVENT_CORDS_LOADED,
	RUNEVENT_WAIT2START,
	RUNEVENT_STOPED,
	RUNEVENT_STARTING,
	RUNEVENT_RUNNING,
};
//-----------------------------------------------------------------------------------------------------------------------

class TRunEvent
{
public:
	static bool	run(UINT minutesBeforeRun, bool isManualStart = false);
	static bool LoadCords();
	static void stop();
	static void getWinner(std::string PlayerName, std::string AccountID);
protected:
	static bool start(bool isManualStart = false);
};
//-----------------------------------------------------------------------------------------------------------------------

extern RUNEVENT_STATE	TRunEvent_RunState;
extern CORDS_MAP		TRunEvent_CordsMap;
extern int				TRunEvent_RoledCord;
//-----------------------------------------------------------------------------------------------------------------------