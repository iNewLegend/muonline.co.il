//-----------------------------------------------------------------------------------------------------------------------
// # Made by Leo123 (Leonid Vinikov)
// # mail	 : czf.leo123@gmail.com
//-----------------------------------------------------------------------------------------------------------------------

#include "stdafx.h"
#include "GIOCPHandler.h"
#include "GLog.h"
#include "Object.h"
#include "Protocol.h"
#include "GMain.h"
//-----------------------------------------------------------------------------------------------------------------------

using namespace iocp;
//-----------------------------------------------------------------------------------------------------------------------

#define szModule "TIOCPHandler"
//-----------------------------------------------------------------------------------------------------------------------

boost::shared_ptr<TIOCPHandler> g_IOCP;

//-----------------------------------------------------------------------------------------------------------------------

TIOCPHandler::TIOCPHandler()
{

}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnNewConnection(uint64_t cid, ConnectionInformation const & c)
{
	g_Log.AddC(-1, szModule, __FUNCTION__, TColor::DeepSkyBlue, "new connection %d", cid);
	//g_Log.AddC(-1, szModule, __FUNCTION__, TColor::DeepSkyBlue, "IP ADDRESS %s", c.m_remoteIpAddress.c_str());
	// ----
	// # Criti
	// ----
	{
		mutex::scoped_lock l(m_mutex);
		// ----
		m_connectionsList.push_back(cid);
		// ----
		if(gObjSearchFree() != -1)
		{
			char temp[1024] = {0};
			// ----
			sprintf(temp, "%s (%d) StartUp: (%s)", MAIN_PROJECT_NAME, m_connectionsList.size(),
				TMain::autoStartup ? "on" : "off");
			// ----
			SetWindowText(gHwnd, temp);
			// ----
			gObjAdd(cid);
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnReceiveData(uint64_t cid, std::vector<uint8_t> const &data)
{
	m_protocolMutex.lock();

		protocolCore(this, cid, (UCHAR *) data.data(), data.size());
	
	m_protocolMutex.unlock();
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnSentData(uint64_t cid, uint64_t byteTransferred)
{
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnClientDisconnect(uint64_t cid, int32_t e)
{
	try
	{
		GetIocpServer().Shutdown(cid, SD_SEND);
		GetIocpServer().Disconnect(cid);
	}
	catch (CIocpException const &e)
	{
		//g_Log.AddC(0, szModule, __FUNCTION__, TColor::LightCyan, (char *)e.What().c_str());
		// ----
		GetIocpServer().Disconnect(cid);
	}
	catch (CWin32Exception const &e)
	{
		//g_Log.AddC(0, szModule, __FUNCTION__, TColor::LightCyan, (char *)e.What().c_str());
		// ----
		GetIocpServer().Disconnect(cid);
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnDisconnect(uint64_t cid, int32_t)
{
	char temp[1024] = { 0 };
	// ----
	g_Log.AddC(-1, szModule, __FUNCTION__, TColor::DeepSkyBlue, "%d disconnected", cid);
	// ----
	// # Criti
	// ----
	{
		mutex::scoped_lock l(m_mutex);
		// ----
		std::vector<uint64_t>::iterator it;
		std::vector<uint64_t> m_connectionsList2;
		// ----
		for (it = m_connectionsList.begin(); it != m_connectionsList.end(); ++it)
		{
			if (cid == (*it))
			{
				//g_Log.AddC(-1, szModule, __FUNCTION__, TColor::DeepSkyBlue, "%d  test1", (*it));
				m_connectionsList.erase(it);
				// ----
				break;
			}
		}
		// ----
		gObjDel(cid);
		// ----
		sprintf(temp, "%s (%d) StartUp: (%s)", MAIN_PROJECT_NAME, (UINT)m_connectionsList.size(),
			TMain::autoStartup ? "on" : "off");
		// ---
		SetWindowText(gHwnd, temp);
		// ----
		if (TMain::autoStartup) {
			int GSCode = -1;

			std::list<std::pair <int, int>>::iterator it;

			for (it = g_MainConnectionsListNum.begin(); it != g_MainConnectionsListNum.end(); ++it)
			{
				if (cid == (*it).first)
				{
					GSCode = (*it).second;

					g_MainConnectionsListNum.erase(it);
					break;
				}
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::OnServerClose(int32_t)
{
	g_Log.AddC(-1, szModule, __FUNCTION__, TColor::DeepSkyBlue, "Server closed");
}
//-----------------------------------------------------------------------------------------------------------------------

void TIOCPHandler::sendAll(LPBYTE buffer, int size)
{
	std::vector<uint64_t>::iterator it;
	// ----
	for(it = m_connectionsList.begin() ; it != m_connectionsList.end() ; ++it) {
			GetIocpServer().Send((*it), buffer, size);
	}
}
//-----------------------------------------------------------------------------------------------------------------------