//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#define CONFUSED_WORDS_FILE		"./Confused_Words.txt"
#define CONFUSED_WORDS_MAP		std::map<int, tagConfusedWrote>
//-----------------------------------------------------------------------------------------------------------------------

#define CONFUSED_WROTE_PRIZE_RANGE		1, 10
#define CONFUSED_WROTE_MINUTES_RANGE	60 , 600
//-----------------------------------------------------------------------------------------------------------------------

struct tagConfusedWrote
{
	std::string	word1;
	std::string word2;
	std::string word3;
	std::string word4;
	std::string	word5;
	std::string word6;
	std::string word7;
	std::string word8;
};
//-----------------------------------------------------------------------------------------------------------------------

enum CONFUSED_STATE
{
	CONFUSED_NULL,
	CONFUSED_WORDS_LOADED,
	CONFUSED_WAIT2START,
	CONFUSED_STOPED,
	CONFUSED_STARTING,
	CONFUSED_RUNNING,
};
//-----------------------------------------------------------------------------------------------------------------------

class TConfusedEvent
{
public:
	static bool	run			(UINT minutesBeforeRun, bool isManualStart = false);
	static bool	LoadWords	();
	static void stop		();
	static void getWinner	(std::string PlayerName, std::string AccountID);
protected:
	static bool start		(bool isManualStart = false);
};
//-----------------------------------------------------------------------------------------------------------------------

extern CONFUSED_STATE TConfusedWrote_State;
//-----------------------------------------------------------------------------------------------------------------------