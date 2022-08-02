//-----------------------------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------------------------

#include "MyMain.h"
//-----------------------------------------------------------------------------------------------

class TMsgEmulator
{
private:
	_ProtocolCore m_protocolCore;
	CRITICAL_SECTION m_critical;
public:
	TMsgEmulator(DWORD ProtocolCore_OFFSET);
	~TMsgEmulator();

	void	Msg		(const char *Format, ...);

	// should be private;
	void __inline CS_Init()		{ InitializeCriticalSection(& this->m_critical); };
	void __inline CS_Lock()		{ EnterCriticalSection(& this->m_critical); };
	void __inline CS_Unlock()	{ LeaveCriticalSection(& this->m_critical); };
	void __inline CS_Delete()	{ DeleteCriticalSection(& this->m_critical); };


	void __inline protocolCore(_PROTOCOL_CORE_ARGS)
	{
		CS_Lock();

		_asm
		{
			//MOV EDI,6ACA18B0 // addons.dll::PrtocolCore
			MOV EDI, 0x4CDB60
			PUSH iIndex
			PUSH iLength
			PUSH lpReceived
			PUSH dwProtocolNumber
			call edi
			add esp, 0x10
		}

		CS_Unlock();

		//m_protocolCore(dwProtocolNumber, lpReceived, iLength, iIndex);
	}
};
//-----------------------------------------------------------------------------------------------

extern TMsgEmulator g_MsgEmulator;
//-----------------------------------------------------------------------------------------------

