#include "stdafx.h"
#include "TSetup.h"
#include "TConfig.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
// # Made By Leo123[BoR] -> GS 99.60T -> Only for MuOnline.co.il

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

extern "C" __declspec (dllexport) void __cdecl Loaded()
{
	DWORD Temp;

	if(VirtualProtect(LPVOID(0x00401000) ,0x0060AFFF, PAGE_EXECUTE_READWRITE, & Temp) == TRUE)  {
		g_Config.readFiles();
		g_Setup.Parse();
		g_Setup.Run();

		return;
	} 
	
	g_Setup.MsgBox("[dllmain.cpp][Loaded] :: VirtualProtect() fail with error : %d;", GetLastError());
	// ----
	ExitProcess(0);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		{
			// ----
		}
		break;

		case DLL_THREAD_ATTACH:
		{
			// ----
		}
		break;

		case DLL_THREAD_DETACH:
		{
			// ----
		}
		break;

		case DLL_PROCESS_DETACH:
		{
			// ----
		}
		break;
	}
	// ----
	return TRUE;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------