#include "FlameSocketSender.h"

CFlameSocketSender::CFlameSocketSender(char* serverAddr, unsigned int port)
{
	mSocket = INVALID_SOCKET;
	//Start up Winsock…

	WSADATA wsadata;

	int error = WSAStartup(0x0202, &wsadata);

	//Did something happen?

	if (error)
		throw std::exception("Winsock Init failed");

	//Did we get the right Winsock version?

	if(wsadata.wVersion != 0x0202)
	{
		WSACleanup(); //Clean up Winsock

		throw std::exception("Non suitable winsock version found");
	}

	//Fill out the information needed to initialize a socket…

	
	mTarget.sin_family = AF_INET; // address family Internet

	mTarget.sin_port = htons(port); //Port to connect on

	mTarget.sin_addr.s_addr = inet_addr(serverAddr); //Target IP




}

void CFlameSocketSender::InitSocket()
{
	if (mSocket != INVALID_SOCKET)
	{
		return;
	}

	mSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //Create socket

	if (mSocket == INVALID_SOCKET)
	{
		throw std::exception("Failed to init socket");
	}

	if (connect(mSocket, (SOCKADDR *)&mTarget, sizeof(mTarget)) == SOCKET_ERROR)
	{
		throw std::exception("Failed to connect to remote host");
	}
}

CFlameSocketSender::~CFlameSocketSender()
{
	//Close the socket if it exists

	if (mSocket)
		closesocket(mSocket);

	WSACleanup(); //Clean up Winsock
}



BOOL CFlameSocketSender::SendStringList(std::vector<std::string> sList)
{
	this->InitSocket();
	const char* const delim = ",";

	std::ostringstream imploded;
	std::copy(sList.begin(), sList.end(),
		std::ostream_iterator<std::string>(imploded, delim));

	const char* c_str = (imploded.str() + "<EOF>").c_str();

	BOOL result = send(mSocket, c_str, (int)strlen(c_str), 0);
	
	closesocket(mSocket);
	mSocket = INVALID_SOCKET;
	return result;
}
