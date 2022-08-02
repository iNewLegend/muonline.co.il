//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

class TMsgDisable
{
private:
	bool											m_bStatus;
	// ----
	boost::shared_ptr<boost::thread>				m_MsgWorker;
	// ----
	static void Worker();
public:
	int												m_MsgTime;
	char											m_MsgName[11];
	// ----
	void		SendStopMsg();
	void		SendStopMsgSystem();
	void		SendStartUpMsg();
	void		SetUpMsgOnStartUp();
	// ----
	void		startWorker()
	{
		m_MsgWorker = boost::shared_ptr<boost::thread>(new boost::thread(TMsgDisable::Worker));
	}
};
//-----------------------------------------------------------------------------------------------------------------------

extern TMsgDisable g_MsgDisable;
//-----------------------------------------------------------------------------------------------------------------------