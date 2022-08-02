//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#define FAST_WROTE_WORDS_FILE		"./FastWrote_Words.txt"
#define FAST_WROTE_WORDS_MAP		std::map<int, tagFastWrote>

//-----------------------------------------------------------------------------------------------------------------------
#define FAST_WROTE_PRIZE_RANGE		1, 10
#define FAST_WROTE_MINUTES_RANGE	60 , 600
//-----------------------------------------------------------------------------------------------------------------------

struct tagFastWrote
{
	std::string	word1;
	std::string word2;
	std::string word3;
	std::string word4;
};
//-----------------------------------------------------------------------------------------------------------------------

enum FASTWROTE_STATE
{
	FASTWROTE_NULL,
	FASTWROTE_WORDS_LOADED,
	FASTWROTE_WAIT2START,
	FASTWROTE_STOPED,
	FASTWROTE_STARTING,
	FASTWROTE_RUNNING,
};
//-----------------------------------------------------------------------------------------------------------------------

class TFastWrote
{
public:
	static bool	run(UINT minutesBeforeRun, bool isManualStart = false);
	static bool	LoadWords	();
	static void stop		();
	static void getWinner	(std::string PlayerName, std::string AccountID);
protected:
	static bool start(bool isManualStart = false);
};
//-----------------------------------------------------------------------------------------------------------------------

extern FASTWROTE_STATE TFastWrote_State;
//-----------------------------------------------------------------------------------------------------------------------