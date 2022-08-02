#pragma once
#define WIN32_LEAN_AND_MEAN


#include "Stdafx.h"
#include <windows.h>
#include <winsock2.h>
#include <mstcpip.h>
#include <ws2tcpip.h>
#include <rpc.h>
#include <ntdsapi.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <ostream>
#include <string>
#include <sstream>
#include <iterator>

#define RECV_DATA_BUF_SIZE 256

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

// link with fwpuclnt.lib for Winsock secure socket extensions
#pragma comment(lib, "fwpuclnt.lib")

// link with ntdsapi.lib for DsMakeSpn function
#pragma comment(lib, "ntdsapi.lib")
class CFlameSocketSender
{
public:
	CFlameSocketSender(char* serverAddr, unsigned int port);
	
	BOOL SendStringList(std::vector<std::string> sList);
	~CFlameSocketSender();
private:
	void InitSocket();
	SOCKET mSocket;
	SOCKADDR_IN mTarget;
};

