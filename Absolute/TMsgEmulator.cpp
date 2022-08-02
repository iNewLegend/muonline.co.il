#include "Stdafx.h"
#include "TMsgEmulator.h"
//-----------------------------------------------------------------------------------------------

TMsgEmulator g_MsgEmulator(0x4CDB60);
//-----------------------------------------------------------------------------------------------

TMsgEmulator::TMsgEmulator(DWORD ProtocolCore_Offset)
{
	CS_Init();

	m_protocolCore = (_ProtocolCore)ProtocolCore_Offset;
}
//-----------------------------------------------------------------------------------------------

TMsgEmulator::~TMsgEmulator()
{
	CS_Delete();
}
//-----------------------------------------------------------------------------------------------

void TMsgEmulator::Msg(const char *Format, ...)
{
	static char Message[1024];
	// ----
	va_list pArguments;
	va_start(pArguments, Format);
	vsprintf(Message, Format, pArguments);
	va_end(pArguments);
	// ----
	BYTE *Packet;
	// ----
	Packet = (BYTE*)malloc(200);
	// ----
	memset(Packet, 0x00, 200);
	// ----
	*Packet = 0xC1;
	*(Packet + 2) = 0x00;
	// ----
	memcpy((Packet + 13), Message, strlen(Message));
	// ----
	int Len = (strlen(Message) + 0x13);
	*(Packet + 1) = Len;
	// ----
	protocolCore(Packet[2], Packet, Len, 0);
	//g_GS.DataSend(aIndex, Packet, Len);
	// ----
	free(Packet);
}
//-----------------------------------------------------------------------------------------------