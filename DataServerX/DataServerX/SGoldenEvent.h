//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include "GIOCPHandler.h"
//-----------------------------------------------------------------------------------------------------------------------

enum e_GOLDEN_STATE
{
	e_GOLDEN_STATE_NULL,
	e_GOLDEN_STATE_STOPED,
	e_GOLDEN_STATE_STARTING,
	e_GOLDEN_STATE_RUNNING,
};
//-----------------------------------------------------------------------------------------------------------------------

class TGoldenEvent
{
public:
	static e_GOLDEN_STATE eEventState;
	static BYTE PrizeAmount;
	
	static void	run();
	static bool start();
	static void stop();
	static void goldenDie(TIOCPHandler * h, uint64_t cid, std::string sAccountId, std::string sName);
};
//-----------------------------------------------------------------------------------------------------------------------