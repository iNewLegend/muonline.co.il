//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "SEventManager.h"
#include "VoteSystem.h"
#include "Object.h"
//-----------------------------------------------------------------------------------------------------------------------

bool		isVoteRunning = false;
std::string VoteQuestion;
std::string VoteGameMaster;
int			VoteSeconds;
//-----------------------------------------------------------------------------------------------------------------------

A_MAP		AnswersMap;
AD_MAP		AnsweredMap;
VOTERS_LIST	VoterList;
//-----------------------------------------------------------------------------------------------------------------------

void voteSystemCore(TIOCPHandler * h, uint64_t cid, LPBYTE Packet)
{
	MSG_HEADER4 * lpHead = (MSG_HEADER4 *) Packet;
	// ----
	switch((VDS_SUBPACKET_VOTESYSTEM_HEADERS)lpHead->SubProtocolId)
	{
		case VDS_SUBPACKET_VOTESYSTEM_HEADERS::VOTESYSTEM_SUBHEAD_START:
		{
			voteSystemStart_R(h, cid, (MSG_VOTESYSTEM_START *) Packet);
		}
		break;

		case VDS_SUBPACKET_VOTESYSTEM_HEADERS::VOTESYSTEM_SUBHEAD_GETVOTE:
		{
			voteSystemGetVote_R(h, cid, (MSG_VOTESYETEM_GETVOTE *) Packet);
		}
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void voteSystemStart_R(TIOCPHandler * h, uint64_t cid, MSG_VOTESYSTEM_START * lpMsg)
{
	char szGMName[11] = { 0 };
	// ----
	memcpy(szGMName, lpMsg->szGameMaster, sizeof(lpMsg->szGameMaster));
	// ----
	// # fix here to new eventmanager
	// ----
	if (TEventManager::isEventRunning() || isVoteRunning)
	{
		objectMsgToNick(h, cid, szGMName, (char*)"The VoteSystem or an Event is running, please try again later");
	}
	else if (isVoteRunning == false)
	{
		VoteGameMaster = szGMName;
		VoteQuestion = lpMsg->Question;
		VoteSeconds = lpMsg->nSeconds;
		// ----
		AnswersMap.clear();
		AnsweredMap.clear();
		// ----
		char Temp[100] = { 0 };
		// ----
		for (BYTE i = 0; i != lpMsg->AnswersCount; ++i)
		{
			memcpy(Temp, lpMsg->Answers[i].Answer, lpMsg->Answers[i].Len);
			// ----
			AnswersMap[lpMsg->Answers[i].Id] = Temp;
		}
		// ----
		h->sendAll((LPBYTE)lpMsg, sizeof(MSG_VOTESYSTEM_START));
		// ----
		for (A_MAP::iterator it = AnswersMap.begin(); it != AnswersMap.end(); ++it)
		{
			AnsweredMap[it->first] = 0;
		}
		// ----
		boost::thread workerThread(voteSystemThread, h);
	}
	else
	{
		objectMsgToNick(h, szGMName, "@[vote] is already running");
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void voteSystemGetVote_R(TIOCPHandler * h, uint64_t cid, MSG_VOTESYETEM_GETVOTE * lpMsg)
{
	char TempNick[11] = {0};
	char TempAccount[11] = {0};
	// ----
	memcpy(TempNick,	lpMsg->PlayerName,	sizeof(lpMsg->PlayerName));
	memcpy(TempAccount, lpMsg->AccountID,	sizeof(lpMsg->AccountID));
	// ----
	if((lpMsg->VoteID == 0) || (lpMsg->VoteID < 0) || (lpMsg->VoteID > AnswersMap.size()))
	{
		objectMsgToNick(h, TempNick, "@[vote] מספר התשובה לסקר שגוי");
	}
	else if(VoterList.empty() == true)
	{
		VoterList.push_back(TempAccount);
		// ----
		++AnsweredMap[lpMsg->VoteID];
		// ----
		objectMsgToNick(h, TempNick, "@[vote] ההצבעה התקבלה ,תודה");
	}
	else
	{
		for(VOTERS_LIST::iterator it = VoterList.begin() ; it != VoterList.end() ; ++it)
		{
			if(_strcmpi(TempAccount, (*it).c_str()) == 0)
			{
				objectMsgToNick(h, TempNick, "@[vote] המערכת מזהה שכבר הצבעת בסקר זה");
				// ----
				return;
			}
		}
		// ---
		VoterList.push_back(TempAccount);
		// ----
		++AnsweredMap[lpMsg->VoteID];
		// ----
		objectMsgToNick(h, TempNick, "@[vote] ההצבעה התקבלה ,תודה");
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void voteSystemThread(TIOCPHandler * h)
{
	boost::posix_time::seconds workTime(VoteSeconds);
	boost::this_thread::sleep(workTime);
	boost::mutex Lock;
	// ----
	Lock.lock();
	// ----
	MSG_VOTESYSTEM_STOP pMsg = {0};
	// ----
	HeadSet4(& pMsg.Head, sizeof(pMsg), HEAD_VOTESYSTEM, VOTESYSTEM_SUBHEAD_STOP);
	// ----
	pMsg.AnswersCount = (BYTE)AnswersMap.size();
	// ----
	BYTE Count = 0;
	// ----
	int sumVoters = 0;
	// ---
	for(AD_MAP::iterator it = AnsweredMap.begin() ; it != AnsweredMap.end() ; ++it)
	{
		sumVoters += it->second;
	}
	for(AD_MAP::iterator it = AnsweredMap.begin() ; it != AnsweredMap.end() ; ++it)
	{
		if(sumVoters > 0)
		{
			it->second = (it->second * 100) / sumVoters;
		}
		else
		{
			it->second = 0;
		}
		// ----
		pMsg.Answered[Count].Id				= it->first;
		pMsg.Answered[Count].AnswerdFor		= it->second;
		// ----
		++Count;
	}
	// ----
	isVoteRunning = false;
	// ----
	Lock.unlock();
	// ----
	pMsg.SumVoters = sumVoters;
	// ----
	h->sendAll((LPBYTE) & pMsg, sizeof(pMsg));
	// ----
	VoteQuestion.clear();
	VoteGameMaster.clear();
	VoteQuestion.clear();
	AnsweredMap.clear();
	VoterList.clear();
}
//-----------------------------------------------------------------------------------------------------------------------