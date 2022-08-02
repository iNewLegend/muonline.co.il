#include "StdAfx.h"
#include "Chat.h"
#include "TChatVote.h"
#include "TMessages.h"
#include "TDataServerSocket.h"
#include "TNotice.h"
#include <boost/thread.hpp>
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

A_MAP			AnswersMap;
std::string		AskedQuestion;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

boost::mutex	VoteLocker;
bool			VoteIsRunning;
std::string		VoteGameMaster;
int				VoteSeconds;
std::string		VoteQuestion;
A_MAP			VoteAnswersMap;

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::Core(int aIndex, char * Message)
{
	char Temp1[50] = {0};
	char Temp2[50] = {0};
	// ----
	g_Chatfunc.GetParam(1, Message, Temp1);
	g_Chatfunc.GetParam(2, Message, Temp2);
	// ----
	if(VoteIsRunning == true)
	{
		// STOP
	}
	else
	{
		if(_strcmpi(Temp1, "start") == 0)
		{
			if(_strcmpi(Message, "/vote start") == 0)
			{
				g_Msg.Msg(aIndex, "@[vote] You didnt put seconds");
			}
			else
			{
				if(isdigit(Temp2[0]) > 0)
				{
					start(aIndex, atoi(Temp2));
				}
				else
				{
					g_Msg.Msg(aIndex, "@[vote] You must use numbers only");
				}
			}
		}
		else if(_strcmpi(Temp1, "set") == 0)
		{
			if(*Temp2 != NULL)
			{
				g_Chatfunc.GetLongParam(& Message[9], Temp2);
				// ----
				setQuestion(aIndex, Temp2);
			}
		}
		else if((isdigit(Temp1[0]) > 0) && (atoi(Temp1) < 10))
		{
			if(*Temp2 != NULL)
			{
				g_Chatfunc.GetLongParam(& Message[6], Temp2);
				{
					setAnswer(aIndex, atoi(Temp1), Temp2);
				}
			}
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::setAnswer(int aIndex, int Number, std::string Answer)
{
	AnswersMap[Number] = Answer;
	// ----
	printDemo(aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::setQuestion(int aIndex, std::string Question)
{
	AskedQuestion = Question;
	// ----
	printDemo(aIndex);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::printDemo(int aIndex)
{
	
	if(AskedQuestion.size() > 0)
	{
		g_Msg.Msg(aIndex, "@-שאלה- ");
		g_Msg.Msg(aIndex, "@%s", AskedQuestion.c_str());
	}
	// ----
	if(AnswersMap.size() > 0)
	{
		g_Msg.Msg(aIndex, "@-תשובות-");
		// ----
		for(A_MAP::iterator it = AnswersMap.begin() ; it != AnswersMap.end() ; ++it)
		{
			g_Msg.Msg(aIndex, "@%d.%s", it->first, it->second.c_str());
		}
		
	}
	
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::start(int aIndex, int seconds)
{
	if(AskedQuestion.size() <= 0)
	{
		g_Msg.Msg(aIndex, "@[vote] You didn't put question");
	}
	else if(AnswersMap.size() < 2)
	{
		g_Msg.Msg(aIndex, "@[vote]You must have minimum 2 answers");
	}
	else if(seconds < 60)
	{
		g_Msg.Msg(aIndex, "@[vote]You must use more then 60 seconds");
	}
	else
	{
		MSG_VOTESYSTEM_START pMsg = {0};
		// ----
		HeadSet4(& pMsg.Head, sizeof(pMsg), HEAD_VOTESYSTEM, VOTESYSTEM_SUBHEAD_START);
		// ----
		pMsg.AnswersCount	= AnswersMap.size();
		pMsg.nSeconds		= seconds;
		pMsg.questionLen	= AskedQuestion.length();
		// ----
		memcpy(pMsg.szGameMaster,	gObj[aIndex].Name,		sizeof(pMsg.szGameMaster));
		memcpy(pMsg.Question,		AskedQuestion.c_str(),	AskedQuestion.length());
		// ----
		BYTE Count = 0;
		// ----
		for(A_MAP::iterator it = AnswersMap.begin() ; it != AnswersMap.end() ; ++it)
		{
			pMsg.Answers[Count].Len = it->second.length();
			pMsg.Answers[Count].Id	= it->first;
			// ----
			memcpy(pMsg.Answers[Count].Answer, it->second.c_str(), it->second.length());
			// ----
			++Count;
		}
		// ----
		g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
	}
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::onStart(std::string GMName, int Seconds, std::string Question, A_MAP Answers)
{
	setRunningState(true);
	// ----
	boost::mutex Guard;
	Guard.lock();
	// ----
	setGameMaster(GMName);
	setSeconds(Seconds);
	setVoteQuestion(Question);
	setVoteAnswers(Answers);
	// ----
	A_MAP::iterator it;
	// ----
	g_Msg.PMAll("-שאלת הסקר-");
	g_Msg.PMAll("%s", Question.c_str());
	g_Msg.PMAll("-אפשרויות הבחירה-");
	// ----
	for(it = Answers.begin() ; it != Answers.end() ; ++it)
	{
		g_Msg.PMAll("%d. %s", it->first, it->second.c_str());
	}
	// ----
	g_Msg.PMAll("בשביל להצביע בסקר יש לרשום בצאט רגיל את המספר תשובה");
	g_Msg.PMAll("לדוגמא: אם בחרתי בתשובה מספר 1 אני ארשום בצאט תמספר 1");
	g_Msg.PMAll("הסקר יסתיים בעוד %d שניות", Seconds);
	// ----
	g_Msg.NoticeAll("הריץ כעת סקר %s", GMName.c_str());
	g_Msg.NoticeAll("F4 עוד פרטים יתקבלו כעת בלחישה לחץ");
	// ----
	Guard.unlock();
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::sendVote(std::string PlayerName, std::string AccountID, int VoteNumber)
{
	MSG_VOTESYETEM_GETVOTE pMsg = {0};
	// ----
	HeadSet4(& pMsg.Head, sizeof(pMsg), HEAD_VOTESYSTEM, VOTESYSTEM_SUBHEAD_GETVOTE);
	// ----
	memcpy(pMsg.PlayerName, PlayerName.c_str(), PlayerName.length());
	memcpy(pMsg.AccountID,	AccountID.c_str(),	AccountID.length());
	// ----
	pMsg.VoteID = VoteNumber;
	// ----
	g_DataServer.DataSend((UCHAR *) & pMsg, sizeof(pMsg));
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CChatVote::voteStop(AD_MAP AnswersResult)
{
	VoteLocker.lock();
	// ----  
	g_Msg.PMAll("הסקר יסתיים להלן התוצאות");
	g_Msg.PMAll("-שאלת הסקר-");
	g_Msg.PMAll("%s", AskedQuestion.c_str());
	// ----
	for(AD_MAP::iterator it = AnswersResult.begin() ; it != AnswersResult.end() ; ++it)
	{
		g_Msg.PMAll("(%d%%) %s", it->second, VoteAnswersMap[it->first].c_str());
	}
	// ----
	setRunningState(false);
	// ----
	VoteLocker.unlock();
	// ----
	ClearGameMaster();
	ClearSeconds();
	ClearVoteQuestion();
	ClearVoteAnswers();
	// ----
	AnswersMap.clear();
	AskedQuestion.clear();
	// ----
	g_Msg.NoticeAll("הסקר הסתיים, התוצאות יתקבלו כעת בלחישה");
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------