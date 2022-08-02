#pragma once
// -------------------------------------------------------------------
#define ITEM_BMD		006175C2 //100% 
#define ITEM_START		508
#define ITEM(x, y)		((x * 32) + y) // 100%
#define ITEM2(x, y)		((x * 32) + y + ITEM_START)
//#define Naked(Function) void __declspec(naked) Function()
// -------------------------------------------------------------------

namespace ASM
{
	enum T
	{
		JMP = 0xE9,
		JE = 0x74,
		JNE = 0x75,
		JGE = 0x7D,
		NOP = 0x90,
		CALL = 0xE8,
	};
};
//---------------------------------------------------------------------------

enum ItemWeight
{
	Bold = 0x01,
	Normal = 0x00,
};
//---------------------------------------------------------------------------

namespace ItemColor
{
	enum T
	{
		White = 0x00,
		Blue = 0x01,
		Red = 0x02,
		Gold = 0x03,
		Green = 0x04,
		WhiteRed = 0x05,
		Violet = 0x06,
		WhiteBlue = 0x07,
		WhiteBeige = 0x08,
		GreenBlue = 0x09,
		Gray = 0x0A,
		DarkViolet = 0x0B,
	};
};
#define oLoadModel			0x005E10E0 // 101%
#define oLoadTexture		0x005E0CA0 // 101%
// ----
#define oLoadModel_Call		0x005F03EA // 101%
#define oLoadTexture_Call	0x005F03EF // 101%
// ----
#define oLoadModel_Void		0x005E3250 // 101%
#define oLoadTexture_Void	0x005E4A20 // 101%
// ----
#define GL_REPEAT                         0x2901
#define GL_NEAREST                        0x2600
#define GL_TRUE                           1
//---------------------------------------------------------------------------

#define LoadModel	( ( void(*) () ) oLoadModel_Void)
#define LoadTexture ( ( void(*) () ) oLoadTexture_Void)
// ----
typedef void(*pLoadTexture) (int TextureID, char * Folder, int GLREPEAT, int GLNEAREST, int GLTRUE);
extern pLoadTexture Texture;
// ----
typedef void(*pLoadModel) (int ModelID, char * Folder, char * Name, int ModelType);
extern pLoadModel Model;
//---------------------------------------------------------------------------


void cBMDLoad();
//---------------------------------------------------------------------------