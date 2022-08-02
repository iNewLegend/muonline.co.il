//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef GAMESERVER_H
#define GAMESERVER_H
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "..\..\include\DSX_protocol.h"
#include "User.h"
#include "DSXProtocol.h"
#include "Item.h"
#include "TShop.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef GS_99_60T
	#define OBJECT_START_INDEX	6400
	#define OBJECT_MAX_INDEX	7400
	#define OBJECT_BASE			0x0653DBF8
	#define OBJECT_SIZE			0x1570
#else
	#define OBJECT_START_INDEX	2500
	#define OBJECT_MAX_INDEX	4000
	#define OBJECT_BASE			0x3CCEF10
	#define OBJECT_SIZE			0x158C
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define	INTERNATIONAL_KOREA		0x00
#define INTERNATIONAL_JAPAN		0x01
#define	INTERNATIONAL_TAIWAN	0x03
#define	INTERNATIONAL_CHINA		0x04
#define INTERNATIONAL_INFO		INTERNATIONAL_CHINA
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if(INTERNATIONAL_INFO == INTERNATIONAL_JAPAN)
	#define MOVE_PROTOCOL		0x1D
	#define SETPOS_PROTOCOL		0xD6
	#define ATTACK_PROTOCOL		0xDC
	#define BEATTACK_PROTOCOL	0xD7
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if(INTERNATIONAL_INFO == INTERNATIONAL_CHINA)
	#define MOVE_PROTOCOL		0xD7
	#define SETPOS_PROTOCOL		0xD2
	#define ATTACK_PROTOCOL		0xD9
	#define BEATTACK_PROTOCOL	0x1D
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#if(INTERNATIONAL_INFO == INTERNATIONAL_KOREA)
	#define MOVE_PROTOCOL		0xD3
	#define SETPOS_PROTOCOL		0xDF
	#define ATTACK_PROTOCOL		0xD7
	#define BEATTACK_PROTOCOL	0x10
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define OBJECT_POINTER(aIndex) ((aIndex * OBJECT_SIZE) + OBJECT_BASE)
#define OBJECT_TABINDEX(lpObj) ((lpObj - OBJECT_BASE) / OBJECT_SIZE)
#define MAX_OBJECT				OBJECT_MAX_INDEX - OBJECT_START_INDEX
#define FIXINDEX				aIndex - OBJECT_START_INDEX
#define NINDEX(aIndex)			(aIndex - OBJECT_START_INDEX)
#define OBJMAX_RANGE(aIndex)	(((aIndex) < 0 )?FALSE:( (aIndex) > OBJECT_MAX_INDEX-1 )?FALSE:TRUE)
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct _NEW_OBJECT
{
	int		Resets;
	int		VipLevel;
	// ----
	bool	canUseMove;
	bool	canUseDisconnect;
	// ----
	bool	isVip;
	bool	isGoAllow;
	bool	isInfoAllow;
	bool	isLogKillerAllow;
	bool	isLogHackAllow;
	bool	isImmortal;
	bool	isAllowToSellPlusAll;
	bool	isAgreeShopping;
	// ----
	DWORD	dwPostTick;
	DWORD	dwHelpTick;
	DWORD	dwReportTick;
	DWORD	dwMarry;
	// ----
	char	LastChat[200];
	// ----
	DWORD	 dwFrames;
	DWORD	 dwCurrentTime;
	DWORD	 dwLastUpdateTime;
	DWORD	 dwElapsedTime;
	TCHAR	 szFPS[32];
	UINT	 FPS;	
	// ----
	DWORD	 dwDL_Horse_Tick;
	//Marriage 
	int		IsMarried;
	char	MarryName[10];
	int		MarryType;
	bool	isMarryAllow;
	bool	isMarryChat;
	#ifdef GS_99_60T
	UINT	nBuyItemCode;
	CShop * buyShop;
	BYTE	bBuyProductPos;
	#endif
	#ifdef SEASAON3
	// ----
	char	CharSet[CHAR_SET_SIZE];
	// ----
	#endif
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CGameServer
{
public:
	_NEW_OBJECT	nObject[MAX_OBJECT];
	// ----
	#ifdef GS_99_60T
	// ----
	DWORD		ofResponErrorCloseClientFunc()	{return 0x475CA0;};
	DWORD		ofResponErrorCloseClientJmp()	{return 0x403ACB;};
	// ----
	DWORD		ofGJPUserCloseFunc()			{return 0x425210;};
	DWORD		ofGJPUserCloseJmp()				{return 0x402950;};
	// ----
	DWORD		ofgObjAddSearchFunc()			{return 0x4B8D90;};
	DWORD		ofgObjAddSearchJmp()			{return 0x404570;};
	// ----
	DWORD		ofgObjSetCharacterFunc()		{return 0x4B4DC0;};
	DWORD		ofgObjSetCharacterJmp()			{return 0x4020F9;};
	// ----
	DWORD		ofItemSerialCreateSendFunc()	{return 0x421750;};
	DWORD		ofItemSerialCreateSendJmp()		{return 0x403698;};
	// ----
	DWORD		ofPMoveProcFunc()				{return 0x43D140;};
	DWORD		ofPMoveProcJmp()				{return 0x4048AE;}; 
	// ----
	DWORD		ofgObjSetPositionFunc()			{return 0x4DD120;};
	DWORD		ofgObjSetPositionJmp()			{return 0x40196A;};
	// ----
	DWORD		ofCGPCharDelFunc()				{return 0x42B300;};
	DWORD		ofCGPCharDelJmp()				{return 0x402DBF;};
	// ----	
	DWORD		ofgObjSetAccountLoginFunc()		{return 0x4BB360;};
	DWORD		ofgObjSetAccountLoginJmp()		{return 0x4031BB;};
	// ----	
	DWORD		ofMsgSendV2Func()				{return 0x4284C0;};
	DWORD		ofMsgSendV2Jmp()				{return 0x401DF2;};
	// ----
	DWORD		ofgObjAddFunc()					{return 0x4B8EC0;};
	DWORD		ofgObjAddJmp()					{return 0x401352;};
	// ----
	DWORD		ofRecvDataParseFunc()			{return 0x473E80;};
	DWORD		ofRecvDataParseJmp()			{return 0x402FD1;};
	// ----
	DWORD		ofgObjDelFunc()					{return 0x4BA570;};
	DWORD		ofgObjDelJmp()					{return 0x403689;};
	// ----
	DWORD		ofPrtocolCoreFunc()				{return 0x426D40;};
	DWORD		ofPrtocolCoreJmp()				{return 0x4033E6;};
	// ----
	DWORD		ofgObjGameCloseFunc()			{return 0x4BA020;};
	DWORD		ofgObjGameCloseJmp()			{return 0x402F77;};
	// ----
	DWORD		ofgObjIsConnectedFunc()			{return 0x4BAB10;};
	DWORD		ofgObjIsConnectedJmp()			{return 0x403139;};
	// ----
	DWORD		ofDataSendFunc()				{return 0x474F40;};
	DWORD		ofDataSendJmp()					{return 0x401A7D;};
	// ----
	DWORD		ofGCTeleportSendFunc()			{return 0x43FD10;};
	DWORD		ofGCTeleportSendJmp()			{return 0x402E50;};
	// ----
	DWORD		ofGCItemListSendFunc()			{return 0x403ECC;};
	DWORD		ofGCItemListSendJmp()			{return 0x403ECC;};
	// ----
	DWORD		ofGCEquipmentSendFunc()			{return 0x42BEC0;};
	DWORD		ofGCEquipmentSendJmp()			{return 0x403C88;};
	// ----
	DWORD		ofCloseClientFunc()				{return 0x475BB0;};
	DWORD		ofCloseCliseJmp()				{return 0x401032;};
	// ----
	DWORD		ofCloseClien2tFunc()			{return 0x475B00;};
	DWORD		ofCloseClient2Jmp()				{return 0x401CA8;};
	// ----
	DWORD		ofgObjTradeCancelFunc()			{return 0x4CC4A0;};
	DWORD		ofgObjTradeCancelJmp()			{return 0x401fA0;};
	// ----
	DWORD		ofgObjTeleportFunc()			{return 0x4D8200;};
	DWORD		ofgObjTeleportJmp()				{return 0x402DE7;};
	// ----
	DWORD		ofgObjAddMonsterFunc()			{return 0x4B9140;};
	DWORD		ofgObjAddMonsterJmp()			{return 0x4040A2;};
	// ----
	DWORD		ofgObjSetMonsterFunc()			{return 0x4B7BF0;};
	DWORD		ofgObjSetMonsterJmp()			{return 0x4026FD;};
	// ----
	DWORD		ofGCServerMsgStringSendFunc()	{return 0x429D60;};
	DWORD		ofGCServerMsgStringSendJmp()	{return 0x402C84;};
	// ----
	DWORD		ofgObjLevelUpPointAddFunc()		{return 0x4BD2C0;};
	DWORD		ofgObjLevelUpPointAddJmp()		{return 0x404633;};
	// ----
	DWORD		ofgObjAttackFunc()				{return 0x4C2960;};
	DWORD		ofgObjAttackJmp()				{return 0x402919;};
	// ----
	DWORD		ofJGPGetCharListFunc()			{return 0x41E660;};
	DWORD		ofJGPGetCharListJmp()			{return 0x403A4E;};
	// ----
	DWORD		ofgObjMoveGateFunc()			{return 0x4D6C60;};
	DWORD		ofgObjMoveGateJmp()				{return 0x40221B;};
	// ----
	DWORD		ofgObjClearViewportFunc()		{return 0x4B28A0;};
	DWORD		ofgObjClearViewportJmp()		{return 0x4029F5;};
	// ----
	DWORD		ofgObjUserDieFunc()				{return 0x4BEE90;};
	DWORD		ofgObjUserDieJmp()				{return 0x403071;};
	// ----
	DWORD		ofCGInventoryItemMoveFunc()		{return 0x42F680;};
	DWORD		ofCGInventoryItemMoveJmp()		{return 0x402162;};
	// ----
	DWORD		ofGCMoneySendFunc()				{return 0x42C270;};
	DWORD		ofGCMoneySendJmp()				{return 0x403D7D;};
	// ----
	DWORD		ofGCJoinResultFunc()			{return 0x42AAD0;};
	DWORD		ofGCJoinResultJmp()				{return 0x401564;};
	// ----
	DWORD		ofCGPCharacterCreateFunc()		{return 0x42AFC0;};
	DWORD		ofCGPCharacterCreateJmp()		{return 0x403215;};
	// ----
	DWORD		ofFriendMemoSendFunc()			{return 0x450FD0;};
	DWORD		ofFriendMemoSendJmp()			{return 0x402414;};
	// ----
	DWORD		ofJGCharacterCreateFailSendFunc(){return 0x41FB40;};
	DWORD		ofJGCharacterCreateFailSendJum(){return 0x4026A3;};
	// ----
	DWORD		ofgObjCloseSetFunc()			{return 0x4B2950;};
	DWORD		ofgObjCloseSetJum()				{return 0x401681;};
	// ----
	DWORD		ofFriendMemoDelReqFunc()		{return 0x451D30;};
	DWORD		ofFriendMemoDelReqJmp()			{return 0x401677;};	
	// ----
	DWORD		ofFriendMemoListFunc()			{return 0x451800;};
	DWORD		ofFriendMemoListJmp()			{return 0x40367F;};	
	// ----
	DWORD		ofDGGuildMemberInfoRequestFunc()					{return 0x44CEE0;};
	DWORD		ofDGGuildMemberInfoRequestJmp()						{return 0x403148;};
	// ----
	DWORD		ofGDGuildMemberDelResultFunc()						{return 0x44CAA0;};
	DWORD		ofGDGuildMemberDelResultJmp()						{return 0x403C42;};
	// ----
	DWORD		ofGDGuildMemberAddResultFunc()						{return 0x44C810;};
	DWORD		ofGDGuildMemberAddResultJmp()						{return 0x40248C;};
	// ----
	DWORD		ofgObjClearViewportofMineFunc()						{return 0x4B2820;};
	DWORD		ofgObjClearViewportofMineJmp()						{return 0x4035B2;};
	// ----
	DWORD		ofgObjViewportListProtocolCreateFunc()				{return 0x4D37E0;};
	DWORD		ofgObjViewportListProtocolCreateJmp()				{return 0x401D3E;};
	// ----
	DWORD		ofDGGetWarehouseListFunc()							{return 0x4209E0;};
	DWORD		ofDGGetWarehouseListJmp()							{return 0x4048C7;};	
	// ----
	DWORD		ofGCUserWarehouseSendFunc()							{return 0x431030;};
	DWORD		ofGCUserWarehouseSendJmp()							{return 0x402A86;};	
	// ----
	DWORD		ofgObjInventoryDeleteItemFunc()						{return 0x4C57B0;};
	DWORD		ofgObjInventoryDeleteItemJum()						{return 0x401D39;};
	// ----
	DWORD		ofGCInventoryItemDeleteSendFunc()					{return 0x442CB0;};
	DWORD		ofGCInventoryItemDeleteSendJum()					{return 0x403693;};
	// ----
	DWORD		ofGCTradeResponseSendFunc()							{return 0x4340A0;};
	DWORD		ofGCTradeResponseSendJmp()							{return 0x401406;};
	// ----	
	DWORD		ofCGPShopAnsSoldItemFunc()							{return 0x437350;};
	DWORD		ofCGPShopAnsSoldItemJmp()							{return 0x402C39;};
	// ----		
	DWORD		ofCGPShopAnsOpenFunc()								{return 0x435560;};
	DWORD		ofCGPShopAnsOpenJmp()								{return 0x401794;};
	// ----	
	DWORD		ofCGPShopAnsCloseFunc()								{return 0x4356B0;};
	DWORD		ofCGPShopAnsCloseJmp()								{return 0x403DE1;};
	// ----	
	DWORD		ofCGTradeRequestSendFunc()							{return 0x432DB0;};
	DWORD		ofCGTradeRequestSendJmp()							{return 0x401BAE;};
	// ----
	DWORD		ofGDGuildReqAssignStatusFunc()						{return 0x44DDD0;};
	DWORD		ofGDGuildReqAssignStatusJmp()						{return 0x4048FE;};
	// ----
	DWORD		ofGDGuildMemberDelFunc()							{return 0x44CA10;};
	DWORD		ofGDGuildMemberDelJmp()								{return 0x40277A;};
	// ---- 
	DWORD		ofGCStateInfoSendFunc()								{return 0x43F350;};
	DWORD		ofGCStateInfoSendJmp()								{return 0x403E9A;};
	// ----
	DWORD		ofCGGuildRequestResultRecvFunc()					{return 0x4392A0;};
	DWORD		ofCGGuildRequestResultRecvJmp()						{return 0x402F95;};
	// ----
	DWORD		ofCGPShopReqBuyItemFunc()							{return 0x4361B0;};
	DWORD		ofCGPShopReqBuyItemJmp()							{return 0x402DFB;};
	// ----
	DWORD		ofCGPShopAnsBuyItemFunc()							{return 0x437210;};
	DWORD		ofCGPShopAnsBuyItemJmp()							{return 0x402BF8;};
	// ----
	DWORD		ofCGPShopReqSetItemPriceFunc()						{return 0x434950;};
	DWORD		ofCGPShopReqSetItemPriceJmp()						{return 0x40198D;};
	// ----
	DWORD		ofCGPShopAnsSetItemPriceFunc()						{return 0x434F00;};
	DWORD		ofCGPShopAnsSetItemPriceJmp()						{return 0x4029CD;};
	// ----
	DWORD		ofCGLiveClientFunc()								{return 0x428560;};
	DWORD		ofCGLiveClientJmp()									{return 0x401D9D;};
	// ----
	DWORD		ofgObjPlayerKillerFunc()							{return 0x4BE870;};
	DWORD		ofgObjPlayerKillerJmp()								{return 0x40285B;};

	// ----
	DWORD		ofGCItemDurSendFunc()								{return 0x442D80;};
	DWORD		ofGCItemDurSendJmp()								{return 0x4049A3;};
	// ----
	DWORD		ofGCReFillSendFunc()								{return 0x442B40;};
	DWORD		ofGCReFillSendJmp()									{return 0x404313;};
	// ----
	DWORD		ofgObjMonsterDieGiveItemFunc()						{ return 0x415880; };
	DWORD		ofgObjMonsterDieGiveItemJmp()						{ return 0x40107D; };
	// ----
	DWORD		ofgObjMonsterTopHitDamageUserFunc()					{ return 0x40F9B0; };
	DWORD		ofgObjMonsterTopHitDamageUserJmp()					{ return 0x403A58; };
	// ----
	DWORD		ofGCManaSendFunc()									{ return 0x442BC0; };
	DWORD		ofGCManaSendJmp()									{ return 0x40299B; };
	// ----
	DWORD		ofGCDamageSendFunc()								{ return 0x43E710; };
	DWORD		ofGCDamageSendJmp()									{ return 0x401FB9; };
	// ----
	DWORD		ofGCKillPlayerExpSendFunc()							{ return 0x43E8E0; };
	DWORD		ofGCKillPlayerExpSendJmp()							{ return 0x403364; };
	// ----
	DWORD		ofItemGetDurabilityFunc()							{ return 0x4EC700; };
	DWORD		ofItemGetDurabilityJmp()							{ return 0x40251D; };
	// ----
	DWORD		ofItemByteConvertFunc()								{ return 0x4EC2C0; };
	DWORD		ofItemByteConvertJmp()								{ return 0x403C47; };
	// ----
	DWORD		ofCGBuyRequestRecvFunc()							{ return 0x4312A0; };
	DWORD		ofCGBuyRequestRecvJmp()								{ return 0x403D28; };
	// ----
	DWORD		ofLogAddFunc()										{ return 0x488C30; };
	DWORD		ofLogAddJmp()										{ return 0x4037DD; };
	// ----
	DWORD		ofgObjOnlyInventoryRectCheckFunc()					{ return 0x4C7410; };
	DWORD		ofgObjOnlyInventoryRectCheckJmp()					{ return 0x4043D1; };
	// ----
	DWORD		ofgGetItemNumberFunc()								{ return 0x4C5C60; };
	DWORD		ofgGetItemNumberJmp()								{ return 0x401262; };
	// ----
	DWORD		ofgPlusItemNumberFunc()								{ return 0x4C5C80; };
	DWORD		ofgPlusItemNumberJmp()								{ return 0x4013CA; };
	// ----
	DWORD		ofgObjInventoryItemSetFunc()						{ return 0x4C51F0; };
	DWORD		ofgObjInventoryItemSetJmp()							{ return 0x403DF0; };
	// ----
	DWORD		ofShopDataLoadFunc()								{ return 0x4EFFA0; };
	DWORD		ofShopDataLoadJmp()									{ return 0x4031DE; };
	// ----
	DWORD		ofCSPJoinIdPassRequestFunc()						{ return 0x42A3B0; };
	DWORD		ofCSPJoinIdPassRequestJmp()							{ return 0x4022A2; };
	// ----
	DWORD		ofgObjSecondProcFunc()								{ return 0x4D2070; };
	DWORD		ofgObjSecondProcJmp()								{ return 0x404985; };
	// ----
	DWORD		ofResponseErrorCloseClientFunc()					{ return 0x475CA0; };
	DWORD		ofResponseErrorCloseClientJmp()						{ return 0x403ACB; };
	// ----
	DWORD		ofgObjSavePetItemInfoFunc()							{ return 0x423040; };
	DWORD		ofgObjSavePetItemInfoJmp()							{ return 0x403FAD; };
	//
	#else /* GS CS */
	// ----
	DWORD		ofItemSerialCreateSendFunc()	{return 0x423AF0;};
	DWORD		ofItemSerialCreateSendJmp()		{return 0x403A2B;};
	// ----
	DWORD		ofCGPCharDelFunc()				{return 0x42EC40;};
	DWORD		ofCGPCharDelJmp()				{return 0x402F09;};
	// ----
	DWORD		ofgObjSetAccountLoginFunc()		{return 0x4CE6A0;};
	DWORD		ofgObjSetAccountLoginJmp()		{return 0x40340E;};
	// ----
	DWORD		ofMsgSendV2Func()				{return 0x42BE00;};
	DWORD		ofMsgSendV2Jmp()				{return 0x405551;};
	// ----
	DWORD		ofgObjAddFunc()					{return 0x4CC220;};
	DWORD		ofgObjAddJmp()					{return 0x40141F;};
	// ----
	DWORD		ofRecvDataParseFunc()			{return 0x486810;};
	DWORD		ofRecvDataParseJmp()			{return 0x4031B1;};
	// ----
	DWORD		ofPrtocolCoreFunc()				{return 0x42A660;};
	DWORD		ofPrtocolCoreJmp()				{return 0x4036D4;};
	// ----
	DWORD		ofgObjGameCloseFunc()			{return 0x4CD360;};
	DWORD		ofgObjGameCloseJmp()			{return 0x403143;};
	// ----
	DWORD		ofgObjIsConnectedFunc()			{return 0x4CDE50;};
	DWORD		ofgObjIsConnectedJmp()			{return 0x40335A;};
	// ----
	DWORD		ofDataSendFunc()				{return 0x4878D0;};
	DWORD		ofDataSendJmp()					{return 0x4052F9;};
	// ----
	DWORD		ofGCTeleportSendFunc()			{return 0x442E70;};
	DWORD		ofGCTeleportSendJmp()			{return 0x402FB8;};
	// ----
	DWORD		ofGCItemListSendFunc()			{return 0x422720;};
	DWORD		ofGCItemListSendJmp()			{return 0x40445D;};
	// ----
	DWORD		ofGCEquipmentSendFunc()			{return 0x42F800;};
	DWORD		ofGCEquipmentSendJmp()			{return 0x40417E;};
	// ----
	DWORD		ofgObjDelFunc()					{return 0x4CD8B0;};
	DWORD		ofgObjDelJmp()					{return 0x403A1C;};
	// ----
	DWORD		ofCloseClientFunc()				{return 0x488540;};
	// ----
	DWORD		ofgObjTradeCancelFunc()			{return 0x4DFF70;};
	DWORD		ofgObjTradeCancelJmp()			{return 0x40566E;};
	// ----
	DWORD		ofgObjTeleportFunc()			{return 0x4ECB30;};
	DWORD		ofgObjTeleportJmp()				{return 0x402F36;};
	// ----
	DWORD		ofgObjAddMonsterFunc()			{return 0x4CC480;};
	DWORD		ofgObjAddMonsterJmp()			{return 0x4046B5;};
	// ----
	DWORD		ofgObjSetMonsterFunc()			{return 0x4CAF30;};
	DWORD		ofgObjSetMonsterJmp()			{return 0x40263A;};
	// ----
	DWORD		ofGCServerMsgStringSendFunc()	{return 0x42D6A0;};
	DWORD		ofGCServerMsgStringSendJmp()	{return 0x402D6F;};
	// ----
	DWORD		ofgObjLevelUpPointAddFunc()		{return 0x4D0830;};
	DWORD		ofgObjLevelUpPointAddJmp()		{return 0x404D9A;};
	// ----
	DWORD		ofgObjAttackFunc()				{return 0x4D6050;};
	DWORD		ofgObjAttackJmp()				{return 0x4028E2;};
	// ----
	DWORD		ofgObjMoveGateFunc()			{return 0x4EAFD0;};
	DWORD		ofgObjMoveGateJmp()				{return 0x40580D;};
	// ----
	DWORD		ofgObjUserDieFunc()				{return 0x4D2550;};
	DWORD		ofgObjUserDieJmp()				{return 0x40326A;};
	// ----
	DWORD		ofgObjClearViewportFunc()		{return 0x4C5940;};
	DWORD		ofgObjClearViewportJmp()		{return 0x4029FA;};
	// ----
	DWORD		ofCGInventoryItemMoveFunc()		{return 0x432FF0;};
	DWORD		ofCGInventoryItemMoveJmp()		{return 0x40578B;};
	// ----
	DWORD		ofResponErrorCloseClientFunc()	{return 0x488630;};
	DWORD		ofResponErrorCloseClientJmp()	{return 0x403F6C;};
	// ----
	DWORD		ofGCMoneySendFunc()				{return 0x42FBB0;};
	DWORD		ofGCMoneySendJmp()				{return 0x4042CD;};
	// ----
	DWORD		ofJGPGetCharListFunc()			{return 0x427150;}; 
	DWORD		ofJGPGetCharListJmp()			{return 0x403C0B;};
	// ----
	/*DWORD		ofGCJoinResultFunc()			{return 0x436AB0;}; // 0x436AB0
	DWORD		ofGCJoinResultJmp()				{return 0x4018F2;};*/ // 0x4018F2
	// ----
	DWORD		ofCGPCharacterCreateFunc()		{return 0x42E900;};
	DWORD		ofCGPCharacterCreateJmp()		{return 0x40346D;};
	// ----
	DWORD		ofgObjCloseSetFunc()			{return 0x4C59F0;};
	DWORD		ofgObjCloseSetJmp()				{return 0x401843;};
	// ----
	DWORD		ofFriendMemoSendFunc()			{return 0x457070;};
	DWORD		ofFriendMemoSendJmp()			{return 0x402301;};
	// ----
	DWORD		ofFriendMemoDelReqFunc()		{return 0x457DD0;};
	DWORD		ofFriendMemoDelReqJmp()			{return 0x40182F;};	
	// ----
	DWORD		ofFriendMemoListFunc()			{return 0x4578A0;};
	DWORD		ofFriendMemoListJmp()			{return 0x403A0D;};	
	// ----
	DWORD		ofJGCharacterCreateFailSendFunc(){return 0x421EE0;};
	DWORD		ofJGCharacterCreateFailSendJum(){return 0x4025C7;};
	// ----
	DWORD		ofgObjClearViewportofMineFunc()						{return 0x04C58C0;};
	DWORD		ofgObjClearViewportofMineJmp()						{return 0x0403909;};
	// ----
	DWORD		ofgObjViewportListProtocolCreateFunc()				{return 0x4E7870;};
	DWORD		ofgObjViewportListProtocolCreateJmp()				{return 0x4054E8;};
	// ----
	DWORD		ofgObjSetCharacterFunc()							{return 0x4C7EE0;};
	DWORD		ofgObjSetCharacterJmp()								{return 0x40573B;};	
	// ----
	DWORD		ofDGGetWarehouseListFunc()							{return 0x422d00;};
	DWORD		ofDGGetWarehouseListJmp()							{return 0x40321a;};	
	// ----
	DWORD		ofGCUserWarehouseSendFunc()							{return 0x4349A0;};
	DWORD		ofGCUserWarehouseSendJmp()							{return 0x402AC2;};	
	// ----
	DWORD		ofgObjInventoryDeleteItemFunc()						{return 0x4D9250;};//0x4C57B0
	DWORD		ofgObjInventoryDeleteItemJum()						{return 0x401E8D;};//0x401D39
	// ----
	DWORD		ofGCInventoryItemDeleteSendFunc()					{return 0x445EF0;};//0x442CB0
	DWORD		ofGCInventoryItemDeleteSendJum()					{return 0x403A26;};//0x403693
	// ----
	DWORD		ofGCTradeResponseSendFunc()							{return 0x437A10;};
	DWORD		ofGCTradeResponseSendJmp()							{return 0x401514;};
	// ----	
	DWORD		ofCGPShopAnsSoldItemFunc()							{return 0x43ACC0;};
	DWORD		ofCGPShopAnsSoldItemJmp()							{return 0x402D1A;};
	// ----		
	DWORD		ofCGPShopAnsOpenFunc()								{return 0x438ED0;};
	DWORD		ofCGPShopAnsOpenJmp()								{return 0x401992;};
	// ----	
	DWORD		ofCGPShopAnsCloseFunc()								{return 0x439020;};
	DWORD		ofCGPShopAnsCloseJmp()								{return 0x40435E;};
	// ----
	DWORD		ofCGTradeRequestSendFunc()							{return 0x436720;};
	DWORD		ofCGTradeRequestSendJmp()							{return 0x4053C6;};
	// ----
	DWORD		ofGDGuildMemberDelFunc()							{return 0x452300;};
	DWORD		ofGDGuildMemberDelJmp()								{return 0x4010FA;};
	// ----
	DWORD		ofGDGuildReqAssignStatusFunc()						{return 0x453E70;};
	DWORD		ofGDGuildReqAssignStatusJmp()						{return 0x405123;};
	// ----
	DWORD		ofCGLiveClientFunc()								{return 0x42BEA0;};
	DWORD		ofCGLiveClientJmp()									{return 0x40551A;};
	// ----
	DWORD		ofCSPJoinIdPassRequestFunc()						{ return 0x42A3B0; };
	DWORD		ofCSPJoinIdPassRequestJmp()							{ return 0x4022A2; };
	#endif
	// ----------------------------------------------------------------------------

	#ifdef GS_99_60T
	// ----------------------------------------------------------------------------
	void gObjSecondProc()
	{
		#define defgObjSecondProc ((void(*) ()) ofgObjSecondProcFunc())
		defgObjSecondProc();
	}
	// ----------------------------------------------------------------------------
	void GJPUserClose(char *szAccountID)
	{
		#define defGJPUserClose ((void(*) (char*)) ofGJPUserCloseFunc())
		// ----
		defGJPUserClose(szAccountID);
	}
	// ----------------------------------------------------------------------------
	void GDGuildMemberAddResult(DWORD lpMsg)
	{
		#define defGDGuildMemberAddResult ((void(*) (DWORD)) ofGDGuildMemberAddResultFunc())
		// ----
		defGDGuildMemberAddResult((DWORD)lpMsg);
	}
	// ----------------------------------------------------------------------------

	void GDGuildMemberDelResult(DWORD lpMsg)
	{
		#define defofGDGuildMemberDelResult ((void(*) (DWORD)) ofGDGuildMemberDelResultFunc())
		// ----
		defofGDGuildMemberDelResult((DWORD)lpMsg);
	}
	// ----------------------------------------------------------------------------

	void DGGuildMemberInfoRequest(int aIndex)
	{
		#define defDGGuildMemberInfoRequest ((void(*) (int)) ofDGGuildMemberInfoRequestFunc())
		// ----
		defDGGuildMemberInfoRequest(aIndex);
	}
	// ----------------------------------------------------------------------------

	void PMoveProc(DWORD unk,  int aIndex)
	{

		#define defPMoveProc ((void(*) (DWORD, int)) ofPMoveProcFunc())
		// ----
		defPMoveProc(unk, aIndex);
	}
	// ----------------------------------------------------------------------------

	void gObjSetPosition(int aIndex, int x, int y)
	{
		#define defgObjSetPosition ((void(*) (int, int , int)) ofgObjSetPositionFunc())
		// ----
		//defgObjSetPosition(aIndex, x, y); 
	}
	// ----------------------------------------------------------------------------

	short gObjAddSearch(SOCKET aSocket, char* ip)
	{
		#define defgObjAddSearch ((short(*) (DWORD, char *)) ofgObjAddSearchFunc())
		// ----
		return defgObjAddSearch(aSocket, ip);
	}
	// ----------------------------------------------------------------------------
		
	void ResponErrorCloseClient(int index)
	{
		#define defResponErrorCloseClient ((void(*) (int)) ofResponseErrorCloseClientFunc())
		// -----
		defResponErrorCloseClient(index);
	}
	// ----------------------------------------------------------------------------

	void GCJoinResult(BYTE result, int aIndex)
	{
		#define defGCJoinResult ((void(*) (BYTE, int)) ofGCJoinResultFunc())
		// -----
		defGCJoinResult(result, aIndex);
	}
	// ----------------------------------------------------------------------------

	void CGGuildRequestResultRecv(DWORD lpMsg, int aIndex)
	{
		#define defCGGuildRequestResultRecv ((void(*) (DWORD, int)) ofCGGuildRequestResultRecvFunc())
		// -----
		defCGGuildRequestResultRecv((DWORD)lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void CGPShopReqBuyItem(DWORD lpMsg, int aSourceIndex)
	{
		#define defCGPShopReqBuyItem ((void(*) (DWORD, int)) ofCGPShopReqBuyItemFunc())
		// -----
		defCGPShopReqBuyItem((DWORD)lpMsg, aSourceIndex);
	}
	// ----------------------------------------------------------------------------

	void CGPShopAnsBuyItem(int aSourceIndex, int aTargetIndex, int iItemPos, BYTE btResult)
	{
		#define defCGPShopAnsBuyItem ((void(*) (int, int, int, BYTE)) ofCGPShopAnsBuyItemFunc())
		// -----
		defCGPShopAnsBuyItem(aSourceIndex, aTargetIndex, iItemPos, btResult);
	}
	// ----------------------------------------------------------------------------

	void CGPShopReqSetItemPrice(DWORD lpMsg, int aIndex)
	{
		#define defCGPShopReqSetItemPrice ((void(*) (DWORD, int)) ofCGPShopReqSetItemPriceFunc())
		// -----
		defCGPShopReqSetItemPrice((DWORD) lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void CGPShopAnsSetItemPrice(int aIndex, BYTE btResult, BYTE btItemPos)
	{
		#define defCGPShopAnsSetItemPrice ((void(*) (int, BYTE, BYTE)) ofCGPShopAnsSetItemPriceFunc())
		// -----
		defCGPShopAnsSetItemPrice(aIndex, btResult, btItemPos);
	}
	// ----------------------------------------------------------------------------
	
	void gObjPlayerKiller (DWORD lpObj, DWORD lpTargetObj)
	{
		#define defgObjPlayerKiller ((void(*) (DWORD,DWORD)) ofgObjPlayerKillerFunc())
		// ----
		defgObjPlayerKiller(lpObj, lpTargetObj);
	}
	// ----------------------------------------------------------------------------
	
	void gObjMonsterDieGiveItem(DWORD lpObj, DWORD lpTargetObj)
	{
		#define defgObjMonsterDieGiveItem ((void(*) (DWORD,DWORD)) ofgObjMonsterDieGiveItemFunc())
		// ----
		defgObjMonsterDieGiveItem(lpObj, lpTargetObj);
	}
	// ----------------------------------------------------------------------------

	void GCItemDurSend (int aIndex, BYTE pos, BYTE dur, unsigned char flag)
	{
		#define defGCItemDurSend ((void(*) (int, BYTE, BYTE, unsigned char)) ofGCItemDurSendFunc())
		// ----
		defGCItemDurSend(aIndex, pos, dur, flag);
	}
	// ----------------------------------------------------------------------------

	int gObjMonsterTopHitDamageUser(DWORD lpMonObj)
	{
		#define defgObjMonsterTopHitDamageUser ((int(*) (DWORD)) ofgObjMonsterTopHitDamageUserFunc())
		// ----
		return defgObjMonsterTopHitDamageUser(lpMonObj);
	}
	// ----------------------------------------------------------------------------

	void GCKillPlayerExpSend(int aIndex, int TargetIndex, int exp, int AttackDamage, int MSBFlag)
	{
		#define defCGCKillPlayerExpSend ((void(*) (int, int, int, int, int)) ofGCKillPlayerExpSendFunc())
		// -----
		defCGCKillPlayerExpSend(aIndex, TargetIndex, exp, AttackDamage, MSBFlag);
	}

	// ----------------------------------------------------------------------------

	int ItemGetDurability(int index, int itemLevel, int ExcellentItem, int SetItem)
	{
		#define defItemGetDurability ((int(*) (int, int, int, int)) ofItemGetDurabilityFunc())
		// -----
		return defItemGetDurability(index, itemLevel, ExcellentItem, SetItem);
	}
	// ----------------------------------------------------------------------------

	void CGBuyRequestRecv(DWORD lpMsg, int aIndex)
	{
		#define defCGBuyRequestRecv ((void(*) (DWORD, int)) ofCGBuyRequestRecvFunc())
		// -----
		return defCGBuyRequestRecv((DWORD)lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------
	
	void LogAdd(const char * szLog, ...)
	{
		char szBuffer[1024] = { 0 };
		va_list pArguments;
		// ----
		va_start(pArguments, szLog);
		vsprintf(szBuffer, szLog, pArguments);
		va_end(pArguments);
		// ----
		#define defLogAdd ((void(*) (char *)) ofLogAddFunc())
		// ----
		defLogAdd(szBuffer);
	}
	// ----------------------------------------------------------------------------

	BYTE gObjOnlyInventoryRectCheck(int aIndex, int sx, int sy, int width, int height)
	{
		#define defgObjOnlyInventoryRectCheck ((BYTE(*) (int, int, int, int, int)) ofgObjOnlyInventoryRectCheckFunc())
		// -----
		return defgObjOnlyInventoryRectCheck(aIndex, sx, sy, width, height);
	}
	// ----------------------------------------------------------------------------

	UINT gGetItemNumber()
	{
		#define defgGetItemNumber ((DWORD(*) ()) ofgGetItemNumberFunc())
		// -----
		return defgGetItemNumber();
	}
	// ----------------------------------------------------------------------------

	void gPlusItemNumber()
	{
		#define defgPlusItemNumber ((void(*) ()) ofgPlusItemNumberFunc())
		// -----
		defgPlusItemNumber();
	}
	// ----------------------------------------------------------------------------

	void gObjInventoryItemSet(int aIndex, int itempos, BYTE set_byte)
	{
		#define defgObjInventoryItemSet ((void(*) (int, int, BYTE)) ofgObjInventoryItemSetFunc())
		// -----
		defgObjInventoryItemSet(aIndex, itempos, set_byte);
	}
	// ----------------------------------------------------------------------------

	bool ShopDataLoad()
	{
		#define defShopDataLoad ((bool(*) ()) ofShopDataLoadFunc())
		// -----
		return defShopDataLoad();
	}
	// ----------------------------------------------------------------------------
	// ----------------------------------------------------------------------------
	#endif /* ONLY FOR GS NORMAL */
	// ----------------------------------------------------------------------------

	void MsgSendV2(DWORD lpObj, LPBYTE msg, int size)
	{
		#define defMsgSendV2 ((void(*) (DWORD, LPBYTE, int)) ofMsgSendV2Func())
		// ----
		defMsgSendV2(lpObj, msg, size);
	}
	// ----------------------------------------------------------------------------
	
	void RecvDataParse(_PER_IO_CONTEXT * lpIO, int uIndex)
	{
		#define defRecvDataParse ((bool(*) (_PER_IO_CONTEXT *,int)) ofRecvDataParseFunc())
		// ----
		defRecvDataParse(lpIO, uIndex);
	}
	// ----------------------------------------------------------------------------

	void ProtocolCore(DWORD protoNum,LPBYTE aRecv,int aLen,int aIndex,DWORD Encrypt,DWORD Serial)
	{
		#define defProtocolCore ((void(*) (DWORD, LPBYTE, int, int, DWORD, DWORD)) ofPrtocolCoreFunc())
		// ----
		defProtocolCore(protoNum, aRecv, aLen, aIndex, Encrypt, Serial);
	}
	// ----------------------------------------------------------------------------

	void gObjDel(int aIndex)
	{
		#define defGobjDel ((void(*) (int)) ofgObjDelFunc())
		// ----
		defGobjDel(aIndex);
	}
	// ----------------------------------------------------------------------------

	void gObjGameClose(int aIndex)
	{
		#define defGameClose ((void(*) (int)) ofgObjGameCloseFunc())
		// ----
		defGameClose(aIndex);
	}
	// ----------------------------------------------------------------------------

	bool DataSend(int aIndex, unsigned char* lpMsg, DWORD dwSize)
	{
		#define defDataSend ((bool(*) (int, unsigned char*, DWORD)) ofDataSendFunc())
		// ----
		return defDataSend(aIndex, lpMsg, dwSize);
	}
	// ----------------------------------------------------------------------------

	void GCTeleportSend(OBJECTSTRUCT * lpObj, BYTE MoveNumber, BYTE MapNumber, BYTE MapX, BYTE MapY, BYTE Dir)
	{
		#define defGCTeleportSend ((bool(*) (int, BYTE , BYTE , BYTE, BYTE , BYTE)) ofGCTeleportSendFunc())
		// ----
		defGCTeleportSend(OBJECT_POINTER(lpObj->m_Index), MoveNumber, MapNumber, MapX, MapY , Dir);
	}
	// ----------------------------------------------------------------------------

	void GCItemListSend(int aIndex)
	{
		#define defGCItemListSend ((void(*) (int)) ofGCItemListSendFunc())
		// ----
		defGCItemListSend(aIndex);
	}
	// ----------------------------------------------------------------------------

	void GCEquipmentSend(int aIndex)
	{
		#define defGCEquipmentSend ((void(*) (int)) ofGCEquipmentSendFunc())
		// ----
		defGCEquipmentSend(aIndex);
	}
	// ----------------------------------------------------------------------------

	void CloseClient(int aIndex)
	{
		#define defCloseClient ((void(*) (int)) ofCloseClientFunc())
		// ----
		if(TRUE == gObjIsConnected(aIndex))
		{
			defCloseClient(aIndex);
		}
	}
	// ----------------------------------------------------------------------------

	void gObjTradeCancel(int aIndex)
	{
		#define defgObjTradeCancel ((void(*) (int)) ofgObjTradeCancelFunc())
		// ----
		defgObjTradeCancel(aIndex);
	}
	// ----------------------------------------------------------------------------

	void gObjTeleport(int aIndex, int map, int x, int y)
	{
		#define defgObjTeleport ((void(*) (int, int, int, int)) ofgObjTeleportFunc())
		// ----
		defgObjTeleport(aIndex, map, x, y);
	}
	// ----------------------------------------------------------------------------

	short gObjAddMonster(int iMapNumber)
	{
		#define defgObjAddMonster ((short(*) (int)) ofgObjAddMonsterFunc())
		// ----
		return defgObjAddMonster(iMapNumber);
	}
	// ----------------------------------------------------------------------------

	bool gObjSetMonster(int aIndex, int MonsterClass)
	{
		#define defgObjSetMonster ((bool(*) (int, int)) ofgObjSetMonsterFunc())
		// ----
		return defgObjSetMonster(aIndex, MonsterClass);
	}
	// ----------------------------------------------------------------------------

	void GCServerMsgStringSend(LPSTR  szMsg, int aIndex, BYTE type)
	{
		#define defGCServerMsgStringSend ((void(*) (LPSTR, int, BYTE)) ofGCServerMsgStringSendFunc())
		// ----
		defGCServerMsgStringSend(szMsg, aIndex, type);
	}
	// ----------------------------------------------------------------------------

	BOOL gObjLevelUpPointAdd(BYTE type, OBJECTSTRUCT * lpObj)
	{
		#define defgObjLevelUpPointAdd ((BOOL(*) (BYTE, OBJECTSTRUCT *)) ofgObjLevelUpPointAddFunc())
		// ----
		return defgObjLevelUpPointAdd(type, lpObj);
	}
	// ----------------------------------------------------------------------------
	
	BOOL gObjAttack(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj, DWORD  lpMagic, BOOL magicsend, BYTE MSBFlag, int AttackDamage, BOOL bCombo)
	{
		#define defgObjAttack ((BOOL(*) (OBJECTSTRUCT * , OBJECTSTRUCT *, DWORD , BOOL, BYTE , int , BOOL)) ofgObjAttackFunc())
		// ----
		return defgObjAttack(lpObj, lpTargetObj, lpMagic, magicsend, MSBFlag, AttackDamage, bCombo);
	}
	// ----------------------------------------------------------------------------

	void JGPGetCharList(UCHAR * lpRecv)
	{
		#define defJGPGetCharList ((void(*) (UCHAR *)) ofJGPGetCharListFunc())
		// ----
		defJGPGetCharList(lpRecv);
	}
	// ----------------------------------------------------------------------------

	BOOL gObjMoveGate(int aIndex, int gt)
	{
		#define defgObjMoveGate ((BOOL(*) (int, int)) ofgObjMoveGateFunc())
		// ----
		return defgObjMoveGate(aIndex, gt);
	}
	// ----------------------------------------------------------------------------

	void gObjClearViewport(OBJECTSTRUCT * lpObj)
	{
		#define defgObjClearViewport ((void(*) (OBJECTSTRUCT *)) ofgObjClearViewportFunc())
		// ----
		return defgObjClearViewport(lpObj);
	}
	// ----------------------------------------------------------------------------
	
	void gObjClearViewportofMine(OBJECTSTRUCT * lpObj)
	{
		#define defgObjClearViewportofMine ((void(*) (OBJECTSTRUCT *)) ofgObjClearViewportofMineFunc())
		// ----
		return defgObjClearViewportofMine(lpObj);
	}
	// ----------------------------------------------------------------------------
	
	void gObjViewportListProtocolCreate(OBJECTSTRUCT * lpObj)
	{
		#define defgObjViewportListProtocolCreate ((void(*) (OBJECTSTRUCT *)) ofgObjViewportListProtocolCreateFunc())
		// ----
		return defgObjViewportListProtocolCreate(lpObj);
	}
	// ----------------------------------------------------------------------------

	void gObjUserDie(OBJECTSTRUCT * lpObj, OBJECTSTRUCT * lpTargetObj)
	{
		#define defgObjUserDie ((void(*) (OBJECTSTRUCT * , OBJECTSTRUCT *)) ofgObjUserDieFunc());
		// ----
		defgObjUserDie(lpObj, lpTargetObj);
	}
	// ----------------------------------------------------------------------------
	
	BOOL gObjAdd(SOCKET aSocket, char * ip, int aIndex)
	{
		#define defgObjAdd ((BOOL(*) (SOCKET, char *, int)) ofgObjAddFunc())
		// ----
		return defgObjAdd(aSocket, ip, aIndex);
	}
	// ----------------------------------------------------------------------------
	
	BOOL gObjSetAccountLogin(DWORD lpObj, char * szId, int aUserNumber, int aDBNumber)
	{
		#define defgObjSetAccountLogin ((BOOL(*) (DWORD, char *, int, int)) ofgObjSetAccountLoginFunc())
		// ----
		return gObjSetAccountLogin(lpObj, szId, aUserNumber, aDBNumber);
	}
	// ----------------------------------------------------------------------------
	
	void CGPCharDel(PMSG_CHARDELETE * lpMsg,int aIndex)
	{
		#define ofCGPCharDel ((void(*) (DWORD, int)) ofCGPCharDelFunc())
		// ----
		ofCGPCharDel((DWORD)lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	BOOL gObjSetCharacter(DWORD Data ,int aIndex)
	{
		#define defgObjSetCharacter ((BOOL(*) (DWORD, int)) ofgObjSetCharacterFunc())
		// ----
		return defgObjSetCharacter(Data, aIndex);
	}
	// ----------------------------------------------------------------------------

	void ItemSerialCreateSend(int aIndex, BYTE MapNumber, BYTE x, BYTE y, int type, BYTE level, BYTE dur, BYTE Op1, BYTE Op2, BYTE Op3, int LootIndex, BYTE NewOption, BYTE SetOption)
	{
		#define defItemSerialCreateSend ((void(*) (int, BYTE, BYTE, BYTE, int, BYTE, BYTE , BYTE , BYTE , BYTE , int , BYTE , BYTE )) ofItemSerialCreateSendFunc())
		// ----
		defItemSerialCreateSend(aIndex, MapNumber, x, y, type, level, dur, Op1, Op2, Op3, LootIndex, NewOption, SetOption);
	}
	// ----------------------------------------------------------------------------

	void DGGetWarehouseList(DWORD lpMsg)
	{
		#define defDGGetWarehouseList ((void(*) (DWORD)) ofDGGetWarehouseListFunc())
		// -----
		defDGGetWarehouseList(lpMsg);
	}
	// ----------------------------------------------------------------------------

	void GCUserWarehouseSend(OBJECTSTRUCT * lpObj)
	{
		#define defGCUserWarehouseSend ((void(*) (DWORD)) ofGCUserWarehouseSendFunc())
		// ----
		defGCUserWarehouseSend((DWORD)lpObj);
	}
	// ----------------------------------------------------------------------------

	void GCMoneySend(int index, int amount)
	{

		#define defGCMoneySend ((void(*) (int, int)) ofGCMoneySendFunc())
		// -----
		defGCMoneySend(index, amount);
	}
	// ----------------------------------------------------------------------------

	void CGPCharacterCreate(DWORD lpMsg, int aIndex)
	{
		#define defCGPCharacterCreate ((void(*) (DWORD, int)) ofCGPCharacterCreateFunc())
		// -----
		defCGPCharacterCreate(lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void JGCharacterCreateFailSend(int aIndex, DWORD lpMsg)
	{
		#define defJGCharacterCreateFailSend ((void(*) (int, DWORD)) ofJGCharacterCreateFailSendFunc())
		// -----
		defJGCharacterCreateFailSend(aIndex, lpMsg);
	}
	// ----------------------------------------------------------------------------

	void FriendMemoSend(int aIndex, DWORD lpMsg)
	{
		#define defFriendMemoSend ((void(*) (int, DWORD)) ofFriendMemoSendFunc())
		// -----
		defFriendMemoSend(aIndex, lpMsg);
	}
	// ----------------------------------------------------------------------------

	void FriendMemoDelReq(DWORD lpMsg, int aIndex)
	{
		#define defFriendMemoDelReq ((void(*) (DWORD, int)) ofFriendMemoDelReqFunc())
		// -----
		defFriendMemoDelReq(lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void FriendMemoList(DWORD lpMsg)
	{
		#define defFriendMemoList ((void(*) (DWORD)) ofFriendMemoListFunc())
		// -----
		defFriendMemoList(lpMsg);
	}
	// ----------------------------------------------------------------------------*/

	void GCTradeResponseSend(BYTE response, int aIndex, LPSTR id, WORD level, int GuildNumber)
	{
		#define defGCTradeResponseSend ((void(*) (BYTE, int, LPSTR, WORD, int)) ofGCTradeResponseSendFunc())
		// -----
		defGCTradeResponseSend(response, aIndex, id, level, GuildNumber);
	}
	// ----------------------------------------------------------------------------*/

	void CGPShopAnsSoldItem(int aSourceIndex, int aTargetIndex, int iItemPos)
	{
		#define defCGPShopAnsSoldItem ((void(*) (int, int, int)) ofCGPShopAnsSoldItemFunc())
		// -----
		defCGPShopAnsSoldItem(aSourceIndex, aTargetIndex, iItemPos);
	}
	// ----------------------------------------------------------------------------

	void CGPShopAnsOpen(int aIndex, BYTE btResult)
	{
		#define defCGPShopAnsOpen ((void(*) (int, BYTE)) ofCGPShopAnsOpenFunc())
		// -----
		defCGPShopAnsOpen(aIndex, btResult);
	}
	// ----------------------------------------------------------------------------

	void CGPShopAnsClose(int aIndex, BYTE btResult)
	{
		#define defCGPShopAnsClose ((void(*) (int, BYTE)) ofCGPShopAnsCloseFunc())
		// -----
		defCGPShopAnsClose(aIndex, btResult);
	}
	// ----------------------------------------------------------------------------

	void CGTradeRequestSend(DWORD lpMsg, int aIndex)
	{
		#define defCGTradeRequestSend ((void(*) (DWORD, int)) ofCGTradeRequestSendFunc())
		// -----
		defCGTradeRequestSend(lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void gObjInventoryDeleteItem(int aIndex, int itempos)
	{
		#define defgObjInventoryDeleteItem ((void(*) (int, int)) ofgObjInventoryDeleteItemFunc())
		// -----
		defgObjInventoryDeleteItem(aIndex, itempos);
	}
	// ----------------------------------------------------------------------------

	void GCInventoryItemDeleteSend(int aIndex, BYTE pos, unsigned char flag)
	{
		#define defGCInventoryItemDeleteSend ((void(*) (int, BYTE, unsigned char)) ofGCInventoryItemDeleteSendFunc())
		// -----
		defGCInventoryItemDeleteSend(aIndex, pos, flag);
	}
	// ----------------------------------------------------------------------------

	void gObjCloseSet(int aIndex, int Flag)
	{
		#define defgObjCloseSet ((void(*) (int, int)) ofgObjCloseSetFunc())
		// -----
		defgObjCloseSet(aIndex, Flag);
	}
	// ----------------------------------------------------------------------------

	void GDGuildReqAssignStatus(int aIndex, int iAssignType, char* szTagetName, int iGuildStatus)
	{
		#define defGDGuildReqAssignStatus ((void(*) (int, int, char* , int)) ofGDGuildReqAssignStatusFunc())
		// -----
		defGDGuildReqAssignStatus(aIndex, iAssignType, szTagetName, iGuildStatus);
	}
	// ----------------------------------------------------------------------------

	void GDGuildMemberDel(int aIndex, char* Name, char* MemberId)
	{
		#define defGDGuildMemberDel ((void(*) (int, char* , char*)) ofGDGuildMemberDelFunc())
		// -----
		defGDGuildMemberDel(aIndex, Name, MemberId);
	}
	// ----------------------------------------------------------------------------

	void CGLiveClient(DWORD lpClientTime, int aIndex)
	{
		#define defCGLiveClient ((void(*) (DWORD, int)) ofCGLiveClientFunc())
		// -----
		defCGLiveClient((DWORD)lpClientTime, aIndex);
	}
	// ----------------------------------------------------------------------------

	void CSPJoinIdPassRequest(DWORD lpMsg, int aIndex)
	{
		#define defCSPJoinIdPassRequest ((void(*) (DWORD , int)) ofCSPJoinIdPassRequestFunc())
		// -----
		defCSPJoinIdPassRequest(lpMsg, aIndex);
	}
	// ----------------------------------------------------------------------------

	void gObjSavePetItemInfo(int aIndex, int inventype)
	{
		#ifdef GS_99_60T
		{
			#define defgObjSavePetItemInfo ((void(*) (int , int)) ofgObjSavePetItemInfoFunc())
			// ----
			defgObjSavePetItemInfo(aIndex, inventype);
		}
		#endif
	}
	// ----------------------------------------------------------------------------

	void CGInventoryItemMove(DWORD lpMsg, int aIndex)
	{
		ofCGInventoryItemMoveFunc();
		// ----
		_asm
		{
			  MOV EDI, Eax // = ofCGInventoryItemMoveFunc
			  // ----
			  MOV ECX, aIndex
			  PUSH ECX
			  MOV EDX, lpMsg
			  PUSH EDX
			  CALL Edi

		}
	}
	// ----------------------------------------------------------------------------
	
	DWORD SearchGuild(char * guildname)
	{
		DWORD dwReturn = 0x00;
		// ----
		#ifdef GS_99_60T
		_asm
		{
			Mov Edi,00402D15H 
			// ----
			Mov Eax,guildname
			Push Eax
			MOV ECX,94E4CA0H
			// ----
			Call Edi
			// ----
			Mov dwReturn,Eax
		}
		#else
		_asm
		{
			Mov Edi,00402E3CH
			// ----
			Mov Eax,guildname
			Push Eax
			MOV ECX,572F760H
			// ----
			Call Edi
			// ----
			Mov dwReturn,Eax
		}
		#endif
		// ----
		return dwReturn;
	}
	// ----------------------------------------------------------------------------
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#pragma pack()
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_INVENTORYITEMMOVE
{
	PBMSG_HEAD	h;
	BYTE		sFlag;
	BYTE		source_item_num;
	BYTE		sItemInfo[5];
	BYTE		tFlag;
	BYTE		target_item_num;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_INVENTORYITEMMOVE_RESULT
{
    PBMSG_HEAD	h;
    BYTE		result;
    BYTE		Pos;
    BYTE		ItemInfo[0x5];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CHATDATA_WHISPER
{
	PBMSG_HEAD	h;
	char		id[10];
	char		chatmsg[60];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_FRIEND_MEMO_DEL_REQ
{
	PBMSG_HEAD h;	//
	USHORT MemoIndex;	//	4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct SDHP_GUILDMEMBERDEL_RESULT
{
    PBMSG_HEAD	h;
    UCHAR		Result;
    UCHAR		Flag;
    UCHAR		NumberH;
    UCHAR		NumberL;
    char		GuildName[9];
    char		MemberID[11];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct SDHP_GUILDMEMBERADD_RESULT
{
    PBMSG_HEAD	h;
    UCHAR		Result;
    UCHAR		Flag;
    UCHAR		NumberH;
    UCHAR		NumberL;
    char		GuildName[9];
    char		MemberID[11];
    short		pServer;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct SDHP_CHARLISTCOUNT
{
	PWMSG_HEAD	h;
	short		Number;
	BYTE		Count;
	int			DbNumber;
	BYTE		Magumsa;
	char		AccountId[11];
	BYTE		MoveCnt;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_RESULT
{
	PBMSG_HEAD	h;
	UCHAR		subcode;
	UCHAR		result;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CHATDATA_NUMBER
{
	PBMSG_HEAD	h;
	BYTE		NumberH;
	BYTE		NumberL;
	char		chatmsg[60];
};
//------------------------------------------------------------------------------------------------------------------------------

struct PMSG_TRADE_REQUEST
{
	PBMSG_HEAD h;
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_FRIEND_MEMO
{
    PWMSG_HEAD h;	//
    ULONG WindowGuid;	//	4
    char Name[10];	//	8
    char Subject[32];	//	12
    UCHAR Dir;	//	32
    UCHAR Action;	//	33
    short MemoSize;	//	34
    char Memo[1000];	//	36
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CHARCREATE
{
	PBMSG_HEAD	h;
	BYTE		subcode;	// 3
	char		Name[10];	// 4
	BYTE		ClassSkin;	// E
};
//------------------------------------------------------------------------------------------------------------------------------

struct PMSG_SERVERCMD
{
	PBMSG_HEAD h;
	BYTE subcode;	// 3
	BYTE CmdType;	// 4
	BYTE X;	// 5
	BYTE Y;	// 6
};	 
//------------------------------------------------------------------------------------------------------------------------------

struct FHP_FRIEND_MEMO_DEL_RESULT
{
    PBMSG_HEAD h;	//
    UCHAR Result;	//	3
    USHORT MemoIndex;	//	4
    short Number;	//	6 // AINDEX
    char Name[10];	//	8
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct FHP_FRIEND_MEMO_LIST
{
    PWMSG_HEAD h;	//
    USHORT Number;	//	4
    USHORT MemoIndex;	//	6
    char SendName[10];	//	8
    char RecvName[10];	//	12
    char Date[30];	//	1C
    char Subject[32];	//	3A
    UCHAR read;	//	5A
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_GUILDQUESTSEND
{
	PBMSG_HEAD h;	// C1:50
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_GUILDQRESULT
{
	PBMSG_HEAD h;
	BYTE Result;	// 3
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_REQ_BUYITEM_FROM_PSHOP
{
	PBMSG_HEAD2 h;
	BYTE NumberH;	// 4
	BYTE NumberL;	// 5
	BYTE btName[10];	// 6
	BYTE btItemPos;	// 10
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_REQ_PSHOP_SETITEMPRICE
{
	PBMSG_HEAD2 h;
	BYTE btItemPos;	// 4
	BYTE sItemPrice1;	// 5
	BYTE sItemPrice2;	// 6
	BYTE sItemPrice3;	// 7
	BYTE sItemPrice4;	// 8
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_CLIENTTIME
{
	PBMSG_HEAD h;
	DWORD Time;	// 4
	WORD AttackSpeed;	// 8
	WORD MagicSpeed;	// A
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_BUYREQUEST
{
	PBMSG_HEAD	h;
	BYTE		Pos;	// 3
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_BUYRESULT
{
	PBMSG_HEAD	 h;	// C1:32
	BYTE		Result;	// 3
	BYTE		ItemInfo[MAX_ITEM_INFO];	// 4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_TALKRESULT
{
	PBMSG_HEAD		h;
	unsigned char	result;	// 3
	BYTE			level1;	// 4
	BYTE			level2;	// 5
	BYTE			level3;	// 6
	BYTE			level4;	// 7
	BYTE			level5;	// 8
	BYTE			level6;	// 9
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_SHOPITEMCOUNT
{
	PWMSG_HEAD h;	// C2:31
	BYTE		Type;	// 4
	BYTE		count;	// 5
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_REFILL // Visual Fix 
{
	PBMSG_HEAD h;	// C1:26
	BYTE IPos;	// 3
	BYTE LifeH;	// 4
	BYTE LifeL;	// 5
	BYTE Flag;	// 6
	int Life;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_MANASEND // Visual Fix
{
	PBMSG_HEAD h;	// C1:27
	BYTE IPos;	// 3
	BYTE ManaH;	// 4
	BYTE ManaL;	// 5
	BYTE BPH;	// 6
	BYTE BPL;	// 7
	int Mana;
	int BP;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_ATTACKRESULT // visual fix
{
	PBMSG_HEAD h;	// C1:DC
	BYTE NumberH;	// 3
	BYTE NumberL;	// 4
	BYTE DamageH;	// 5
	BYTE DamageL;	// 6
	BYTE DamageType;	// 7
	int Damage;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_ADDON_LASTDAMAGERESULT // visaul fix
{
	PBMSG_HEAD h;
	BYTE subcode;
	int Damage;
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct PMSG_IDPASS
{
	PBMSG_HEAD h;
	BYTE subcode;
	char Id[10];
	char Pass[10];
	DWORD TickCount;
	BYTE CliVersion[5];
	BYTE CliSerial[16];
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct SDHP_SAVE_PETITEM_INFO
{
	PWMSG_HEAD h;
	BYTE nCount;	// 4
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct Save_PetItem_Info
{
	int nSerial;	// 0
	BYTE Level;	// 3
	int Exp;	// 8
};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif /* GAMESERVER_H */
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------