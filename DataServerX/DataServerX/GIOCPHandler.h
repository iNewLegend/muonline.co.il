//-----------------------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------------------

#include <conio.h>
#include <fstream>
#include <boost/thread.hpp>
#include <string>

#include <windows.h>
#include <atlstr.h>
#include <stdio.h>
#include <stdlib.h>
//-----------------------------------------------------------------------------------------------------------------------

#include "IOCP/ExternalLibraries.h"
#include "IOCP/IocpServer.h"

class TIOCPHandler : public iocp::CIocpHandler
{
private:
	boost::mutex		m_mutex;
	boost::mutex		m_globalMutex;
	boost::mutex		m_protocolMutex;
	// ----
	std::vector<uint64_t> m_connectionsList;
	
public:
	TIOCPHandler();
	// ----
	virtual void OnNewConnection	(uint64_t cid, iocp::ConnectionInformation const & c);
	virtual void OnReceiveData		(uint64_t cid, std::vector<uint8_t> const & data);
	virtual void OnSentData			(uint64_t cid, uint64_t byteTransferred);
	virtual void OnClientDisconnect	(uint64_t cid, int32_t e);
	virtual void OnDisconnect		(uint64_t cid, int32_t);
	virtual void OnServerClose		(int32_t);
	// ----
	void		sendAll				(LPBYTE buffer, int size);
};
//-----------------------------------------------------------------------------------------------------------------------

extern boost::shared_ptr<TIOCPHandler> g_IOCP;
//-----------------------------------------------------------------------------------------------------------------------