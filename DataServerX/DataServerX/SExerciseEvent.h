//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include <boost\thread.hpp>
//-----------------------------------------------------------------------------------------------------------------------

#define ExerciseRangeNUM1		1, 999
#define ExerciseRangeNUM2		1, 999
#define ExerciseRangeNUM3		1, 999
#define EXERCISE_PRIZE_RANGE	1, 10
#define EXERCISE_TIMER_RANGE	30, 90
//-----------------------------------------------------------------------------------------------------------------------

#define EXERCISE_EVENT_TIME		60
//-----------------------------------------------------------------------------------------------------------------------

struct tagExercise
{
	int Num1;
	int Num2;
	int	Num3;
	int Answer;
};
//-----------------------------------------------------------------------------------------------------------------------

enum TExerciseEvent_eRunState
{
	STATE_WAIT2START,
	STATE_STOPED,
	STATE_STARTING,
	STATE_WORKING,
};
//-----------------------------------------------------------------------------------------------------------------------

class TExerciseEvent
{
public:
	static bool run(UINT minutesBeforeRun, bool isManualStart = false);
	static void stop			();
	static void getAnswer		(std::string PlayerName, std::string AccountID, int Answer);
protected:
	static void eventWorker();
	static bool start(bool isManualStart = false);
};
//-----------------------------------------------------------------------------------------------------------------------

extern TExerciseEvent_eRunState TExerciseEvent_runState;
//-----------------------------------------------------------------------------------------------------------------------

