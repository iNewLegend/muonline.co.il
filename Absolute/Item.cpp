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


void InitModel(int ItemID, char *ModelName, char *Folder, char *Form)
{
	_asm
	{
		push - 1;
		push ModelName;
		push Form;
		push ItemID;
		mov eax, 0x005E10E0;
		call eax;

		/*push 1;
		push 0x2600;
		push 0x2901;
		push Folder;
		push ItemID;
		mov eax, 0x005E0CA0;
		call eax;*/
	}
}
void InitTexture(int ItemID, char *ModelName, char *Folder, char *Form)
{
	_asm
	{

		push 1;
		push 0x2600;
		push 0x2901;
		push Folder;
		push ItemID;
		mov eax, 0x005E0CA0;
		call eax;
	}
}
void cModelLoad()
{
	LoadModel();

	// ----
	Model(ITEM2(1, 9), ItemsFolder, "HDKSword", -1);
}
// --------------------------------------------------------------------

void cTextureLoad()
{
	LoadTexture();

	// ----
	Texture(ITEM2(1, 9), ItemsTexture, GL_REPEAT, GL_NEAREST, GL_TRUE);
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

void SetNop(DWORD dwSrcOffset, int Size)
{
	for (int i = 0; i < Size; i++)
		*(BYTE*)(dwSrcOffset + i) = 0x90;
};


void __declspec(naked) PatchNewModel()
{
	InitModel(ITEM2(1, 9), "HDK_SWORD", ItemsTexture, ItemsFolder);
	_asm
	{
		push - 1;
		push 0x00673430; // PUSH "suho.bmd"
		push 0x0067365C; // PUSH "Data\Item"
		push 0x3D8; // PUSH Item2(14,31)
		mov eax, 0x005E10E0; // 
		call eax;
		mov eax, 0x005E43EB;
		jmp eax;
	}
}
void __declspec(naked) PatchNewTexture()
{
	InitTexture(ITEM2(1, 9), "HDK_SWORD", ItemsTexture, ItemsFolder);
	_asm
	{
		push 1; // PUSH GL_TRUE
		push 0x2600; // PUSH GL_NEAREST
		push 0x2901; // PUSH GL_REPEAT
		push 0x00673DD0; // PUSH "Item\"
		push 0x3D8; // PUSH Item2(14,31)
		mov eax, 0x005E0CA0; // 
		call eax;
		mov eax, 0x005E4B85;
		jmp eax;
	}
}

void cBMDLoad()
{
	SetNop(0x005E43D5, 22);
	SetHook((LPVOID)PatchNewModel, (LPVOID)0x005E43D5, ASM::JMP);

	SetNop(0x005E4B6A, 26);
	SetHook((LPVOID)PatchNewTexture, (LPVOID)0x005E4B6A, ASM::JMP);
	SetHook((LPVOID)cTextureLoad, (LPVOID)oLoadTexture_Call, ASM::CALL);

}