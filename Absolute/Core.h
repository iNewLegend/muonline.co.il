//-----------------------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------------------

class CCore
{
public:
	bool m_IsRadio;

	CCore(void);
	// ----
	static void Hook();
	static void LocalChat(char * Input);
	static void RadioCore(void * param);
	static void InventoryOpend();
	//static void sendCrcPack(SOCKET s, CPacket recvPacket);
	//static void test2(void * param);
};
//-----------------------------------------------------------------------------------------------------------
// # [Notice] : find a common pleace to store it >

static void WriteBytes(DWORD Address, BYTE x[], int size) { DWORD *addr = (DWORD*)Address; memcpy(addr, x, size); };
//-----------------------------------------------------------------------------------------------------------
extern CCore g_Core;
//-----------------------------------------------------------------------------------------------------------
