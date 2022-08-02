#pragma once
//-----------------------------------------------------------------------------------------------------------

#define _PROTOCOL_CORE_ARGS DWORD dwProtocolNumber, LPBYTE lpReceived, int iLength, int iIndex
//-----------------------------------------------------------------------------------------------------------

typedef void(*_ProtocolCore) (_PROTOCOL_CORE_ARGS);
//-----------------------------------------------------------------------------------------------------------

#define sub_412560 ((int (__thiscall*) (int _this, __int16 a2, int a3, char a4, int a5, int a6, int a7, int a8, int a9, int a10)) 0x412560)
#define sub_412530 ((DWORD(*) (DWORD)) 0x412530)
#define sub_5E0BE0 ((DWORD(*) (DWORD)) 0x5E0BE0)
#define sub_4129A0 ((int (__thiscall*) (int _this, __int16 a2, int a3, int a4, int a5, int a6, int a7)) 0x412560)
#define sub_4CDB60 ((int (*) (int _this, __int16 a2, int a3, int a4, int a5, int a6, int a7)) 0x4CDB60)
#define main_strcmp /*sub_5540D0*/ ((char(*) (const char *, const char *, char )) 0x5540D0) // possible strcmp
#define sub_5E0EE0 ((int(*) (int a1, const char *a2, const char *a3)) 0x5E0EE0)
#define sub_5E0CA0 ((char(*) (int a1, const char *a2, int a3, int param, int height)) 0x5E0CA0)
#define sub_5E10E0 ((LRESULT(*) (int a1, int a2, const char *a3, signed int a4)) 0x5E10E0)
#define sub_649E83 ((int(*) (int)) 0x649E83)
#define sub_60F900 ((char(*) (int a1, int a2, int param, int a4, int a5, char a6)) 0x60F900)
#define sub_60FD90 ((char(*) (int a1, int a2, int param, int a4, int a5, int height)) 0x60FD90)
//-----------------------------------------------------------------------------------------------------------


struct unknown_struct_5540D0
{
	BYTE gap0[120];
	DWORD viewSkillState;
	BYTE gap7C[332];
	BYTE ctlcode;		
	const char playerName;
	BYTE gap1CA[398];
	BYTE byte358;
	DWORD dword35C;		
};
//-----------------------------------------------------------------------------------------------------------

class MyMain
{
public:
	static bool is_firstPacketRecvied;

	static void HookAll				();
	static void HookViewSkillState	(bool action);
	static int	ViewSkillState		(unknown_struct_5540D0 * msg);
	static void LoadSkills			();
	static int	ProtocolCore		(BYTE xcode, LPBYTE aRecv, unsigned int len, int a5);
};
//-----------------------------------------------------------------------------------------------------------

void inline HookJMP(DWORD dwMyFuncOffset, DWORD dwJmpOffset){*(DWORD*)(dwJmpOffset+1) = dwMyFuncOffset -(dwJmpOffset+5);};
void inline SetOffset(DWORD dwOffset, DWORD dwMyFunction){*(DWORD*)(dwOffset) = dwMyFunction;};
//-----------------------------------------------------------------------------------------------------------