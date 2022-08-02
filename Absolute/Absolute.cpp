#include "stdafx.h"
#include "define.h"
#include "MyMain.h"
#include "TEncoding.h"
#include "Core.h"
#include "bass.h"
#include "crc32.h"
#include "Console.h"
#include "TMsgEmulator.h"
#include "CFlamePList.h"
#include "FlameSocketSender.h"
#include <thread>
#include "Item.h"
#include "TAntiHack.h"
#include "TPacket.h"
#include <numeric>
#include "StreamPacketEngine_Client.h"

//-----------------------------------------------------------------------------------------------------------
// made by Leo123 (czf.leo123@gmail.com) Leonid Vinikov
//-----------------------------------------------------------------------------------------------------------

DWORD * Main_Serial = (DWORD*)0x0066FEF0;
DWORD * Main_Version = (DWORD*)0x0066FEE8;
DWORD * Main_WindowName = (DWORD*)0x0066FBB8;
DWORD * Main_SERIALV1 = (DWORD*)0x00411890;
DWORD * Main_SERIALV2 = (DWORD*)0x00604D2D;
//-----------------------------------------------------------------------------------------------------------

HHOOK		KeyboardHook;
HINSTANCE	hInstance;
bool		isConnectedToAnyGS;
//-----------------------------------------------------------------------------------------------------------

SOCKET	g_LAST_USED_SOCKET;
DWORD	g_LAST_USED_PORT;
//-----------------------------------------------------------------------------------------------------------

lptag_LAUNCHER_REQUEST g_launcherRequest;
//-----------------------------------------------------------------------------------------------------------
// # Server List

// # Hebrew :
const char * g_ABSOLUTE_HEBREW_SERVERS[] = {

	"שרת 1 - ניתן לרצוח ",
	"שרת 2 - לא ניתן לרצוח ",
	"שרת 3 - לא ניתן לרצוח ",
	"שרת 4 - לא ניתן לרצוח ",
	"שרת 5 - ויאיפי - לא ניתן לרצוח ",
	"שרת 6 - ויאיפי - לא ניתן לרצוח ",
	"שרת בדיקות",
	"שרת בדיקות",
	"שרת בדיקות",
	"שרת בדיקות",
	"שרת בדיקות",
};

// # English :
const char * g_ABSOLUTE_ENGLISH_SERVERS[] = {

	"Server1 PVP",
	"Server2 NONPVP",
	"Server3 NONPVP",
	"Server4 NONPVP",
	"Server5 VIP NONPVP",
	"Server6 VIP NONPVP",
	"Server Test",
	"Server Test",
	"Server Test",
	"Server Test",
	"Server Test",
};
//-----------------------------------------------------------------------------------------------------------

int (WINAPI *pConnect)	(SOCKET s, const struct sockaddr* name, int namelen) = connect;
int (WINAPI *pSend)		(SOCKET s, const char* buf, int len, int flags) = send;
//-----------------------------------------------------------------------------------------------------------

USHORT Absolute_GetPort(sockaddr * ClientSockAddr)
{
	sockaddr_in * ipv4 = (struct sockaddr_in *) ClientSockAddr;
	// ----
	return ntohs(ipv4->sin_port);
}
//-----------------------------------------------------------------------------------------------------------

int WINAPI Absolute_HOOKSend(SOCKET s, const char* buf, int len, int flags)
{
	BYTE xcode = (BYTE)buf[0];

#if(ABSOLUTE_CONSOLE == ON)

	char Buffer[1024 * 8] = { 0 };
	char key[1024] = { 0 };

	Console.Write("Absolute_HOOKSend() xcode : %2x, len : %d, flags : %d", xcode, len, flags);

	if (buf[0] == 0xC1)
	{
		char packetString[2048] = { 0 };

		sprintf(packetString, "%02X", buf[0]);

		for (DWORD i = 1; i < len; ++i)
		{
			sprintf(packetString, "%s %02X", packetString, buf[i]);
		}

		Console.Write(packetString);
	}

#endif

#if(ABSOLUTE_PACKET_ENCRYPTION == ON)

	if (isConnectedToAnyGS)
	{
		// # if MU packet.
		// ----
		if (xcode == 0xC1 ||
			xcode == 0xC2 ||
			xcode == 0xC3 ||
			xcode == 0xC4)
		{
			Console.Write("g_Encoder.CodeBuffer");
			g_Encoder.CodeBuffer((LPBYTE)buf, len);
		}
	}

#endif

	return pSend(s, buf, len, flags);
}
//-----------------------------------------------------------------------------------------------------------

void Absolute_DataSend(LPBYTE packet, WORD packetSize)
{

#if(ABSOLUTE_CONSOLE == ON)

	char packetString[2048] = { 0 };

	sprintf(packetString, "%02X", (BYTE)packet[0]);

	for (DWORD i = 1; i < packetSize; ++i)
	{
		sprintf(packetString, "%s %02X", packetString, packet[i]);
	}

	Console.Write("[Absolute_DataSend] %s", packetString);


#endif

	CStreamPacketEngine_Client ps;
	ps.Clear();
	BYTE packetSend[7024];

	if (ps.AddData(packet, packetSize) == 0)
	{
		Console.Write("[Absolute_DataSend] ps.addData faield");
		return;
	}
	if (ps.ExtractPacket(packetSend) != 0)
	{
		Console.Write("[Absolute_DataSend] ps.ExtractPacket faield");
		return;
	}

	Absolute_HOOKSend(g_LAST_USED_SOCKET, (const char *)packetSend, packetSize, 0);
}
//-----------------------------------------------------------------------------------------------------------

int WINAPI Absolute_HOOKConnect(SOCKET s, const struct sockaddr* name, int namelen)
{
	g_LAST_USED_PORT = Absolute_GetPort((sockaddr*)name);
	g_LAST_USED_SOCKET = s;

	if (g_LAST_USED_PORT >= 20000 && g_LAST_USED_PORT < 30000) {
		switch (g_LAST_USED_PORT)
		{
		case 20000:
		case 20020:
			isConnectedToAnyGS = false;
			// unhook
			//MyMain::HookViewSkillState(false);
		default:
			isConnectedToAnyGS = true;
			// hook
			//MyMain::HookViewSkillState(true);
		}
	}
	else {
		isConnectedToAnyGS = false;
		// unhook
		//MyMain::HookViewSkillState(false);
	}


	// ----
#if(ABSOLUTE_CONSOLE == ON)

	Console.Write("Absolute_HOOKConnect() socket : %d, port : %d, isConnectedToAnyGS : %d", s, g_LAST_USED_PORT, isConnectedToAnyGS);

#endif
	// ----
	return pConnect(s, name, namelen);
}
//-----------------------------------------------------------------------------------------------------------

bool Absolute_CheckFiles()
{

#if(ABSOLUTE_CHECKFILES == ON) 
	// ----
	//		std::string s = std::to_string(Hash);
	//		MessageBoxA(0, s.c_str(), "MuGuard Injected", MB_ICONERROR);
	// ----
	CCRC32 MyCRC32;
	MyCRC32.Initialize();
	/*_ULonglong*/ unsigned __int64 Hash = MyCRC32.FileCRC("main.exe");
	if (std::to_string(Hash) != "1525298620")
	{
		MessageBoxA(0, "CheckFiles() :: main.exe", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Launcher.exe");
	if (std::to_string(Hash) != "2702044491")
	{
		MessageBoxA(0, "CheckFiles() :: Launcher.exe", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("MuIsrael.dll");
	if (std::to_string(Hash) != "1428613427")
	{
		MessageBoxA(0, "CheckFiles() :: MuIsrael Drivers", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/Local/item.bmd");
	if (std::to_string(Hash) != "3848229074" && std::to_string(Hash) != "2235403501")
	{
		MessageBoxA(0, "CheckFiles() :: item.bmd", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/Player/player.bmd");
	if (std::to_string(Hash) != "1564119972") // && std::to_string(Hash) != "1724314553"
	{
		MessageBoxA(0, "CheckFiles() :: player.bmd", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World1/EncTerrain1.att");
	if (std::to_string(Hash) != "1396282974")//3661891204
	{
		MessageBoxA(0,"CheckFiles() :: Map 1","MuGuard Injected",MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World1/EncTerrain1.obj");
	
	if (std::to_string(Hash) != "702382676")//3731660491
	{
		MessageBoxA(0,"CheckFiles() :: Map 1","MuGuard Injected",MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World3/EncTerrain3.att");
	if (std::to_string(Hash) != "1616476456")//1616476456
	{
		MessageBoxA(0, "CheckFiles() :: Map 3", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World3/EncTerrain3.obj");
	if (std::to_string(Hash) != "3274143518")//3274143518
	{
		MessageBoxA(0, "CheckFiles() :: Map 3", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World4/EncTerrain4.att");
	if (std::to_string(Hash) != "2092968316")//4149751958
	{
		MessageBoxA(0, "CheckFiles() :: Map 4", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/World4/EncTerrain4.obj");
	if (std::to_string(Hash) != "2298410695")//488557806
	{
		MessageBoxA(0, "CheckFiles() :: Map 4", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/Skill/skill.bmd");
	if (std::to_string(Hash) != "2842775613")
	{
		MessageBoxA(0, "CheckFiles() :: skill.bmd", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("3DCamera.dll");
	if (std::to_string(Hash) != "212008990")
	{
		MessageBoxA(0, "CheckFiles() :: 3DCamera Dll", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("AutoClicker.dll");
	if (std::to_string(Hash) != "2855806474")
	{
		MessageBoxA(0, "CheckFiles() :: AutoClicker Dll", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Glow.dll");
	if (std::to_string(Hash) != "2928660245")
	{
		MessageBoxA(0, "CheckFiles() :: Glow Dll", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Data/glow.gld");
	if (std::to_string(Hash) != "2029662564")
	{
		MessageBoxA(0, "CheckFiles() :: Glow DB", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	Hash = MyCRC32.FileCRC("Addons.dll");
	if (std::to_string(Hash) != "3273110644")
	{
		MessageBoxA(0, "CheckFiles() :: Addons Dll", "MuGuard Injected", MB_ICONERROR);
		return false;
	}
	// ----
#endif
	// ----
	return true;
}
//-----------------------------------------------------------------------------------------------------------

lptag_LAUNCHER_REQUEST Absolute_ProcessLauncherRequest()
{
	std::string lpCmdLine = GetCommandLineA();
	// ----
	static tag_LAUNCHER_REQUEST launcherRequest;
	// ----
	memset(&launcherRequest, 0x00, sizeof(tag_LAUNCHER_REQUEST));
	// ----
	if (lpCmdLine.back() == 'N')
	{
		lpCmdLine.pop_back();
		if (lpCmdLine.back() == 'E')
			launcherRequest.eLang = EN;
		else
		{
			MessageBoxA(0, "Please Use Launcher. Thanks!", 0, 0);
			// ----
			ExitProcess(0);
		}
	}
	else if (lpCmdLine.back() == 'E')
	{
		lpCmdLine.pop_back();
		if (lpCmdLine.back() == 'H')
			launcherRequest.eLang = HE;
		else
		{
			MessageBoxA(0, "Please Use Launcher. Thanks!", 0, 0);
			// ----
			ExitProcess(0);
		}
	}
	else
	{
		MessageBoxA(0, "Please Use Launcher. Thanks!", 0, 0);
		// ----
		ExitProcess(0);
	}
	// ----
	lpCmdLine.pop_back();
	lpCmdLine.pop_back();
	// ----
	if (lpCmdLine.back() == '1') {
		launcherRequest.isLoadCamera = true;
	}
	// ----
	return &launcherRequest;
}
//-----------------------------------------------------------------------------------------------------------

char * Absolute_GetServerName()
{
	int Num = 0;
	// ----
	_asm
	{
		Mov Eax, DWORD PTR DS : [0x660FB8]
		Mov Num, Eax
	}
	// ----
	Num -= 2;
	// ----
	if (g_launcherRequest->eLang == EN) {
		return (char *)g_ABSOLUTE_ENGLISH_SERVERS[Num];
	}
	// ----
	return (char *)g_ABSOLUTE_HEBREW_SERVERS[Num];
}
//-----------------------------------------------------------------------------------------------------------

void Absolute_SetVersionSerial(char * version, char serialWord)
{
	memset(&Main_Version[0], 0x00, strlen(version));
	memcpy(&Main_Version[0], version, strlen(version));
	// ----
	memset(&Main_SERIALV1[0], serialWord, 1);
	memset(&Main_SERIALV2[0], serialWord, 1);
}
//-----------------------------------------------------------------------------------------------------------

void Absolute_HookALL()
{
	_asm
	{
		Mov Dword Ptr Ds : [00660FBDH], Offset Absolute_GetServerName
	}

	g_Core.Hook();
	//cBMDLoad();
	MyMain::HookAll();
}
//-----------------------------------------------------------------------------------------------------------

LRESULT CALLBACK Absolute_KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (((lParam >> 31) & 1) && (nCode == HC_ACTION))
	{
		if (wParam == VK_ESCAPE)
		{
			BYTE PACKET[3] = { 0xC1 , 0x3 , 0xFF };
			// ----
			send(g_LAST_USED_SOCKET, (LPCSTR)PACKET, 3, 0);
		}

#if(ABSOLUTE_RADIO == ON)

		else if (wParam == VK_F5)
		{
			// # TODO : it should be like that g_Radio.Stop(); 
			// # Optimize msg printing;
			// ----

			// toggle radio state;
			g_Core.m_IsRadio = !g_Core.m_IsRadio;

			if (!g_Core.m_IsRadio) {
				if (g_launcherRequest->eLang == HE)
				{
					g_MsgEmulator.Msg("@[Radio] רדיו כבוי");
				}
				else {
					g_MsgEmulator.Msg("@[Radio] Off");
				}
				// TODO :
				// g_Radio.Stop();
				// ----
				BASS_ChannelStop(StreamUrl);
				BASS_StreamFree(StreamUrl);
			}
			else {
				if (g_launcherRequest->eLang == HE)
				{
					g_MsgEmulator.Msg("@[Radio] רדיו פעיל");
				}
				else {
					g_MsgEmulator.Msg("@[Radio] On");
				}
			}
		}

#endif
	}
	// ----
	return CallNextHookEx(KeyboardHook, nCode, wParam, lParam);
}
//-----------------------------------------------------------------------------------------------------------

DWORD WINAPI RunServerSideAntiHack(LPVOID lpParam) 
{
	do {
		Console.WriteDT("[AntiHack] getting process list");
		PROCESSES_LIST processes = g_AntiHack.GetProcesses();
		Console.WriteDT("[AntiHack]  there are %d processes", processes.size());

		do {
			Sleep(1000);
			Console.WriteDT("[AntiHack] checking if connected to any gameserver");
		} while (!isConnectedToAnyGS);

		Console.WriteDT("[AntiHack] connected to gameserver, starting check.");

		// clean and sort.
		processes.sort();
		processes.unique();

		Console.WriteDT("[AntiHack] after cleaning there are %d processes", processes.size());

		for (auto const& i : processes) {
			Console.Write("[AntiHack] sending process check: `%s` with crc32: `%u`", i.name.c_str(), i.uChecksum);

			if (!isConnectedToAnyGS) {
				Console.WriteDT("[AntiHack]: no connection to gameserver, retry ...");
				break;
			}
			// ---
			CPacket packet(0xC2);

			packet.writeByte(0xFE);
			packet.writeString(i.name);
			packet.writeLong(i.uChecksum);
			packet.writeSize(packet.getLength());
			// ---
			Absolute_DataSend((LPBYTE)packet.getBuffer().c_str(), packet.getLength());

			Sleep(3500);
		}
		Sleep(15000);
	} while (true);
}
//-----------------------------------------------------------------------------------------------

extern "C" __declspec (dllexport) void __cdecl Absolute()
{
	DWORD OldProtect = 0x00;
	if (!VirtualProtect(LPVOID(0x401000), 0x00805FF6, PAGE_EXECUTE_READWRITE, &OldProtect))
	{
		MessageBoxA(0, "Unable to initialize the Absolute.dll", "Absolute DLL", 0);
		ExitProcess(0);
	}
	// ----
	if (Absolute_CheckFiles() == false)
	{
		MessageBoxA(0, "CheckFiles() :: ERROR \nבדיקת קבצים נשכלה", "MuGuard Injected", MB_ICONERROR);
		ExitProcess(0);
	}
	// ----
	Absolute_SetVersionSerial(ABSOLUTE_MAIN_VERSION, ABSOLUTE_MAIN_SERIAL_WORD);
	Absolute_HookALL();
	// ----
	g_launcherRequest = Absolute_ProcessLauncherRequest();
	// ----
#if(ABSOLUTE_RADIO == ON) 
	{
		BASS_Init(-1, 44100, 0, 0, 0);
		BASS_SetVolume(0x100);
	}
#endif
	// ----
	_beginthread(g_Core.RadioCore, 0, 0);
	// ----
	LoadLibraryA("Glow.dll");
	LoadLibraryA("AutoClicker.dll");
	LoadLibraryA("Addons.dll");
	LoadLibraryA("MuIsrael.dll");
	// ----
#if(ABSOLUTE_CONSOLE == ON)
	Console.Init();
#endif
	// ----
	if (g_launcherRequest->isLoadCamera)
	{
		LoadLibraryA("3DCamera.dll");
	}
	// ----
	CreateThread(NULL, 0, RunServerSideAntiHack, 0, 0, NULL);
}
//-----------------------------------------------------------------------------------------------

BOOL APIENTRY DllMain(HANDLE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{		
		KeyboardHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)Absolute_KeyboardProc, hInstance, GetCurrentThreadId());
		// ----
		// # hook connect
		// ----
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pConnect, Absolute_HOOKConnect);
		DetourTransactionCommit();
		// ----
		// # hook sendqwd
		// ----
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)pSend, Absolute_HOOKSend);
		DetourTransactionCommit();
	}

	break;

	case DLL_PROCESS_DETACH:
	{
		/*// ----
		// # unhook connect
		// ----
		UnhookWindowsHookEx(KeyboardHook);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pConnect, Absolute_HOOKConnect);
		DetourTransactionCommit();
		// ----
		// # unhook sendLts le
		// ----
		UnhookWindowsHookEx(KeyboardHook);
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pSend, Absolute_HOOKSend);
		DetourTransactionCommit();*/
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
	}
	// ----
	return TRUE;
}
//-----------------------------------------------------------------------------------------------






