
#include "Stdafx.h"
#include "Core.h"
#include "define.h"
#include "BASS.h"
#include "crc32.h"
#include "MyMain.h"
#include "Console.h"
#include "TMsgEmulator.h"
//-----------------------------------------------------------------------------------------------------------
// made by Leo123 (czf.leo123@gmail.com) Leonid Vinikov
//-----------------------------------------------------------------------------------------------------------

CCore g_Core;
//-----------------------------------------------------------------------------------------------------------

CCore::CCore(void)
{
	m_IsRadio = true;

	HANDLE hMutex = CreateMutex(NULL, FALSE, "ABSOLULTE_MAIN_MUTEX");

	// if there is mutex then main process is already exist;
	if (GetLastError() == 0xB7)
	{
		CloseHandle(hMutex);

		m_IsRadio = false;

	}
}
//-----------------------------------------------------------------------------------------------------------

void CCore::Hook()
{
	/* Hook Local Chat START*/
	// # this is hook only by dll
	BYTE Temp[] = {0x90, 0x57 , 0xFF , 0x15 , 0x56 , 0x0F , 0x66 , 0x00 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90 , 0x90};
	WriteBytes(0x554AFE, Temp, sizeof(Temp));
	SetOffset(0x660F56, (DWORD) & g_Core.LocalChat);
	/* Hook Local Chat END*/
	// ---
	/* Hook WHEN INVETORY OPEND START*/
	// # this is castoum hook (main side too)
	SetOffset(0x660EA3, (DWORD) & g_Core.InventoryOpend);
	/* Hook WHEN INVETORY OPEND END*/
	//SetOffset(0x004010F1, (DWORD) & g_Core.LoadSings);
}
//-----------------------------------------------------------------------------------------------------------

void CCore::LocalChat(char * Input)
{
	if(strcmpi(Input, "/radio on") == 0)
	{
		g_Core.m_IsRadio = true;
	}
	else if(strcmpi(Input, "/radio off") == 0)
	{
		g_Core.m_IsRadio = false;
		BASS_ChannelStop(StreamUrl);
		BASS_StreamFree(StreamUrl);
	}
}
//-----------------------------------------------------------------------------------------------------------

void CCore::RadioCore(void * param)
{
	while(true)
	{
		Console.Write("CCore::RadioCore() Looping");

		if(StreamUrl != 0)
		{
			if(g_Core.m_IsRadio) {
				if(BASS_ChannelIsActive(StreamUrl) == BASS_ACTIVE_PLAYING || 
					BASS_ChannelIsActive(StreamUrl) == BASS_ACTIVE_STALLED)
				{
					Sleep(1); continue;
				}
				else
				{
					BASS_StreamFree(StreamUrl);
					// ----
					StreamUrl = BASS_StreamCreateURL(StreamBuffUrl, 0 , 0 ,0 , 0);
					// ----
					if (StreamUrl != 0) {
						BASS_ChannelPlay(StreamUrl, true);

						if(MyMain::is_firstPacketRecvied) {
							// # bad practice
							if (g_launcherRequest->eLang == HE) {
								g_MsgEmulator.Msg("@[Radio] ! הרדיו פעיל כעת, הנא הדליקו את הרמקולים");
								g_MsgEmulator.Msg("@[Radio] F5 לכיבוי או הלדקה הנא לחץ");
							}
							else {
								g_MsgEmulator.Msg("@[Radio] is now playing.");
								g_MsgEmulator.Msg("@[Radio] to switch on/off please press F5");
							}
						}
					}
				}
			}
		}
		else if(g_Core.m_IsRadio)
		{
			// # no stram URL create new one
			// ----
			StreamUrl = BASS_StreamCreateURL(StreamBuffUrl, 0 ,0 ,0 , 0);
			// ----
			if(StreamUrl != 0)
			{
				BASS_ChannelPlay(StreamUrl, true);
			
				if (MyMain::is_firstPacketRecvied) {
					// # bad practice
					if (g_launcherRequest->eLang == HE) {
						g_MsgEmulator.Msg("@[Radio] ! הרדיו פעיל כעת, אנא הדליקו את הרמקולים");
						g_MsgEmulator.Msg("@[Radio] F5 לכיבוי או הלדקה אנא לחץ");
					}
					else {
						g_MsgEmulator.Msg("@[Radio] is now playing.");
						g_MsgEmulator.Msg("@[Radio] to switch on/off please press F5");
					}
				}
			}
		}
		// ----
		Sleep(ABSOLUTE_WAIT_RADIO);
	}
}
//-----------------------------------------------------------------------------------------------------------

void CCore::InventoryOpend()
{
	static int Counter = 0;
	// ----
	if(Counter >= 10)
	{
		BYTE PACKET[3] = {0xC1 , 0x3 , 0xFF}; // ESC PACKET
		// ----
		send(g_LAST_USED_SOCKET, (LPCSTR)PACKET , 3 , 0);
		// ----
		Counter = 0;
	}
	else Counter++;
	// ----
	_asm
	{
		Mov Edi,005F2400H
		MOV ECX,DWORD PTR SS:[EBP-4H]
		MOV EDX,DWORD PTR SS:[EBP-8H]
		PUSH 1H
		PUSH 1H
		PUSH 3F400000H
		PUSH 3F400000H
		PUSH 0H
		PUSH 0H
		PUSH 41C00000H
		PUSH 41C00000H
		PUSH ECX
		PUSH EDX
		PUSH 658
		CALL EDI

		ADD Esp,2CH

		FILD DWORD PTR DS:[7CC0D44H]

		Mov Edi,005C8224H
		JMP Edi
	}
}
//-----------------------------------------------------------------------------------------------------------

/*FILE* pRecvLogFile;

void CCore::sendCrcPack(SOCKET s, CPacket recvPacket)
{
	fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
	fprintf(pRecvLogFile, "start send packet\n"); // 8192 
	fclose(pRecvLogFile); // i loged it here - and its getting in only one time on the request packet...
	
	recvPacket.setLength(4); // Get to the first Data pos. Byte[0] - Head. Byte[1]+Byte[2] = Word size. Byte[3] = sub head
	// ----
	CCRC32 MyCRC32;
	MyCRC32.Initialize();
	// ----
	unsigned long crcFile;
	std::string filePath;
	// ----
	CPacket sendPacket;
	// ----
	sendPacket.writeByte(0xFB);
	//sendPacket.writeByte((BYTE)e_PROTECTION_SUB_PRTOROCOL_HEADER::e_HEAD_RESPONSE_HASH_LIST);
	// ----
	BYTE Count = recvPacket.readByte(); // count
	// ----
	sendPacket.writeByte(Count);
	// ----
	_ULonglong Hash = 0;
	char temp [1000] = {0};
	for(BYTE i = 0 ; i != Count ; ++i) 
	{
		memset(temp, 0, sizeof(temp));

		filePath = recvPacket.readString();
		
		//MessageBoxA(0,temp,temp,0);
		
		// ----
		crcFile = MyCRC32.FileCRC(filePath.c_str());
		// h----
		
		Hash = crcFile;

		//sprintf(temp, "%s %s", filePath.c_str(), std::to_string(Hash).c_str()); //2975386022
		sendPacket.writeString(filePath);
		sendPacket.writeString(std::to_string(Hash));
	}
	// ----
	TAG_HEADER header(0xC2, sendPacket.getLength());
	sendPacket.writeHeader(header);	
	// ----
	// what ? the repeat sending packet is on this section... i loged the call of this function and its getting in
	// only once on the request from server..

	/*if (g_LAST_USED_SOCKET != 0)
	{ 
		fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
		fprintf(pRecvLogFile, "send packet\n"); // 8192 
		fclose(pRecvLogFile); // i loged it here - and its getting in only one time on the request packet...
		send(Socket_Connected, sendPacket.getBuffer().c_str(), sendPacket.getLength() + 1 ,0); // sending again here stuck...
//		_beginthread(g_Core.test, 4, (LPVOID) & sendPacket);

		fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
		fprintf(pRecvLogFile, "end send packet\n"); // 8192 
		fclose(pRecvLogFile); // i loged it here - and its getting in only one time on the request packet...
	}
	*/


	/*fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
	fprintf(pRecvLogFile, "sent packet"); // 8192 
	fclose(pRecvLogFile);
}

void CCore::test2(void * param)
{
	CCRC32 MyCRC32;
	MyCRC32.Initialize();
	// ----
	unsigned long crcFile;
	std::string filePath;
	// ----
	CPacket sendPacket;
	// ----
	sendPacket.writeByte((BYTE)e_PROTECTION_SUB_PRTOROCOL_HEADER::e_HEAD_RESPONSE_HASH_LIST);
	// ----
	sendPacket.writeByte(0x01);
	// ----
	_ULonglong Hash = 0;
	char temp [1000] = {0};
	memset(temp, 0, sizeof(temp));

		
	//MessageBoxA(0,temp,temp,0);
		
	// ----
	crcFile = MyCRC32.FileCRC("main.exe");
	// h----
		
	Hash = crcFile;

	//sprintf(temp, "%s %s", filePath.c_str(), std::to_string(Hash).c_str()); //2975386022
	sendPacket.writeString("main.exe");
	sendPacket.writeString(std::to_string(Hash));
	
	// ----
	TAG_HEADER header(0xC5, sendPacket.getLength());
	sendPacket.writeHeader(header);

	while(true)
	{

		/*if (Socket_Connected != 0)
		{ 
			fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
			fprintf(pRecvLogFile, "send packet\n"); // 8192 
			fclose(pRecvLogFile); // i loged it here - and its getting in only one time on the request packet...
			send(Socket_Connected, sendPacket.getBuffer().c_str(), sendPacket.getLength()+1 ,0); // sending again here stuck...
			/*BYTE PACKET[3] = {0xC3 , 0x18};
			// ----
			send(Socket_Connected, (LPCSTR)PACKET , 2 , 0);
			fopen_s(&pRecvLogFile, "C:\\RecvLog.txt", "a+");
			fprintf(pRecvLogFile, "end send packet\n"); // 8192 
			fclose(pRecvLogFile); // i loged it here - and its getting in only one time on the request packet...
		}*
		// ----
		//send(Socket_Connected, recv->getBuffer().c_str(), recv->getLength() + 1 ,0);
		Sleep(30000);
	}
}*/