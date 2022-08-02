//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma once
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include <map>
#include <list>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define A_MAP		std::map<int, std::string>
#define AD_MAP		std::map<int , int>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern bool				VoteIsRunning;
extern std::string		VoteGameMaster;
extern int				VoteSeconds;
extern std::string		VoteQuestion;
extern A_MAP			VoteAnswersMap;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CChatVote
{
public:
	static void		Core			(int aIndex, char * Message);
	static void		setAnswer		(int aIndex, int Number, std::string Answer);
	static void		setQuestion		(int aIndex, std::string Question);
	static void		printDemo		(int aIndex);
	static void		start			(int aIndex, int seconds);
	static void		onStart			(std::string GMName, int Seconds, std::string Question, A_MAP Answers);
	static void		sendVote		(std::string PlayerName, std::string AccountID, int VoteNumber);
	static void		voteStop		(AD_MAP AnswersResult);
	// ----
	static void		setRunningState	(bool State)		{ VoteIsRunning = State;	};
	static void		setGameMaster	(std::string GM)	{ VoteGameMaster = GM;		};
	static void		setSeconds		(int seconds)		{ VoteSeconds = seconds;	};
	static void		setVoteQuestion	(std:: string Q)	{ VoteQuestion = Q;			};
	static void		setVoteAnswers	(A_MAP A)			{ VoteAnswersMap = A;		};
	// -----
	static void		ClearGameMaster		()	{ VoteGameMaster.clear();		};
	static void		ClearSeconds		()	{ VoteSeconds = 0;				};
	static void		ClearVoteQuestion	()	{ VoteQuestion.clear();			};
	static void		ClearVoteAnswers	()	{ VoteAnswersMap.clear();		};
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------