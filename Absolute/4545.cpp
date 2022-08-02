#include "Stdafx.h"
#include "Item.h"
//---------------------------------------------------------------------------
//char * ItemsFolder = "Data\\Flame\\Jewels\\";
//char * ItemsTexture = "Data\\Flame\\";

char * ItemsFolder = "Data\\Flame\\Items\\";
char * ItemsTexture = "Flame\\Items\\";

pLoadModel Model = (pLoadModel)(oLoadModel);
pLoadTexture Texture = (pLoadTexture)(oLoadTexture);

// -------------------------------------------------------------------

void cModelLoad()
{
	LoadModel();

	// ----
	Model(ITEM(1, 9), ItemsFolder, "Skill_Jewel", -1);
}
// --------------------------------------------------------------------

void cTextureLoad()
{
	LoadTexture();

	// ----
	Texture(ITEM(1, 9), ItemsTexture, GL_REPEAT, GL_NEAREST, GL_TRUE);
}

DWORD WriteMemory(const LPVOID lpAddress, const LPVOID lpBuf, const UINT uSize)
{
	memcpy(lpAddress, lpBuf, uSize);
	// ----
	DWORD dwBytes = 0;
	return 0x00;
}

DWORD SetHook(const LPVOID dwMyFuncOffset, const LPVOID dwJmpOffset, const BYTE cmd)
{
	BYTE btBuf[5];
	// ----
	DWORD dwShift = (ULONG_PTR)dwMyFuncOffset - ((ULONG_PTR)dwJmpOffset + 5);
	// ----
	btBuf[0] = cmd;
	// ----
	memcpy((LPVOID)& btBuf[1], (LPVOID)& dwShift, sizeof(ULONG_PTR));
	// ----
	return WriteMemory(dwJmpOffset, (LPVOID)btBuf, sizeof(btBuf));
}

void cBMDLoad()
{
	SetHook((LPVOID)cModelLoad, (LPVOID)oLoadModel_Call, ASM::CALL);
	SetHook((LPVOID)cTextureLoad, (LPVOID)oLoadTexture_Call, ASM::CALL);
}

