//-----------------------------------------------------------------------------------------------------------------------
// # Made by RoyeGM (Roye Elmaz)
// # mail	 : elmazr@walla.com
// # skype	 : elmazr21
//-----------------------------------------------------------------------------------------------------------------------

#include "StdAfx.h"
#include "GMsgDisable.h"
#include "Object.h"
#include "Protocol.h"
#include "TDataBase.h"
//-----------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "TMsgDisable"
//-----------------------------------------------------------------------------------------------------------------------

TMsgDisable g_MsgDisable;
//-----------------------------------------------------------------------------------------------------------------------

void TMsgDisable::Worker()
{
	g_MsgDisable.m_bStatus = true;
	g_MsgDisable.SetUpMsgOnStartUp(); // sends to the gss reset
	// ---
	char line[100];
	// -----
	boost::posix_time::milliseconds milisecond(1);
	boost::posix_time::minutes		tenMinutes(10);
	// ----
	int rest = 0;
	// ----
	try {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Yellow, "START OK !");

		while (true)
		{
			if (MSG_CONTINUE == true)
			{
				MessagesWebState(true);
				// ----
				memset(line, 0x00, sizeof(line));
				// ----
				sprintf(line, "%s %d %s %s", "הודעות המסג' כבויות ל: ",
					g_MsgDisable.m_MsgTime, "דקות על ידי", g_MsgDisable.m_MsgName);
				// ----
				ObjectSendNoticeAll(line);
				// ----
				rest = g_MsgDisable.m_MsgTime % 10;
				// ----
				if (rest != 0)
				{
					boost::posix_time::minutes timerest(rest);
					boost::this_thread::sleep(timerest);
					// ---
					if (g_MsgDisable.m_MsgTime > 10)
					{
						g_MsgDisable.m_MsgTime -= rest;
					}
				}
				// ----
				for (int i = (g_MsgDisable.m_MsgTime / 10); i > 0; --i)
				{
					sprintf(line, "%s %d %s", "הודעות המסג' כבויות לעוד: ", g_MsgDisable.m_MsgTime, "דקות");
					ObjectSendNoticeAll(line);
					// ----
					boost::this_thread::sleep(tenMinutes);
					g_MsgDisable.m_MsgTime -= 10;
				}
				// ----
				MessagesWebState(false);
				// ----
				sprintf(line, "%s", "החסימה להודעות מסג' ירדה");
				ObjectSendNoticeAll(line);
				// ----
				g_MsgDisable.SendStartUpMsg();
				g_MsgDisable.m_MsgTime = 0;
				// ----
				MSG_CONTINUE = false;
				// ----
				memcpy(g_MsgDisable.m_MsgName, "0", sizeof("0"));
			}
			// ----
			boost::this_thread::sleep(milisecond);
		}
	}
	catch (boost::thread_interrupted const&) {
		g_Log.AddC(-1, g_ModuleName, __FUNCTION__, TColor::Red, "THREAD INTERRUPTED !");
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TMsgDisable::SendStopMsg()
{
	char line [1024] = {0};
	// ----
	MSG_MSG_STATUS_RE_SYS rpMsg = {0};
	// ----	
	HeadSet1(& rpMsg.Head, sizeof(rpMsg), HEAD_MSG_STATUS_SYS);
	// ----
	rpMsg.Status		= 0;
	// ----
	m_bStatus = false;
	// ----
	sprintf(line, "%s %s", "החסימה להודעות מסג' ירדה על ידי", g_MsgDisable.m_MsgName);
	ObjectSendNoticeAll(line);
	// ----
	g_IOCP->sendAll((LPBYTE) & rpMsg, sizeof(rpMsg));
	// ----
	m_MsgWorker->interrupt();
	// ----
	// # creates again the thead after killing it
	if (m_bStatus == false)
	{
		startWorker();
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TMsgDisable::SendStopMsgSystem()
{
	MSG_MSG_STATUS_RE_SYS rpMsg = {0};
	// ----	
	HeadSet1(& rpMsg.Head, sizeof(rpMsg), HEAD_MSG_STATUS_SYS);
	// ----
	rpMsg.Status		= 1;
	// ----
	m_bStatus = false;
	// ----
	m_MsgWorker->interrupt();
	// ----
	// # creates again the thead after killing it
	if (m_bStatus == false)
	{
		startWorker();
	}
	// ----
	g_IOCP->sendAll((LPBYTE) & rpMsg, sizeof(rpMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void TMsgDisable::SendStartUpMsg()
{
	MSG_CONTINUE = false;
	MSG_MSG_STATUS_RE_SYS rpMsg = {0};
	// ----
	HeadSet1(& rpMsg.Head, sizeof(rpMsg), HEAD_MSG_STATUS_SYS);
	// ----
	rpMsg.Status		= 0;
	// ----
	g_IOCP->sendAll((LPBYTE) & rpMsg, sizeof(rpMsg));
}
//-----------------------------------------------------------------------------------------------------------------------

void TMsgDisable::SetUpMsgOnStartUp()
{
	MessagesWebState(false);
	// ----
	MSG_MSG_STATUS_RE_SYS rpMsg = {0};
	// ----	
	HeadSet1(& rpMsg.Head, sizeof(rpMsg), HEAD_MSG_STATUS_SYS);
	// ----
	rpMsg.Status		= 0;
	// ----
	g_IOCP->sendAll((LPBYTE) & rpMsg, sizeof(rpMsg));
}
//-----------------------------------------------------------------------------------------------------------------------