#include "stdafx.H"
#include "TShop.H"
#include "TSetup.h"
#include "../../include/ReadScript.h"
#include "TMessages.h"
#include "DSXProtocol.h"
#include "TLogToFile.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef GS_99_60T
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define g_ModuleName "CShop"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

BYTE CShop::bShopsCount = 0;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

CShop * CShop::Shops;
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CShop::Init()
{
	this->SendItemDataLen = 0;
	this->ItemCount = 0;
	// -----
	memset(this->ShopInventoryMap, 0, sizeof(this->ShopInventoryMap));
	// -----
	g_CoinShopLog.Output("[%s][%s][%d]: done", g_ModuleName, __FUNCTION__, this->ShopId);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CShop::InsertItem(int type, int index, int level, int dur, int op1, int op2, int op3, int exc, int ancient, int price)
{
	int itemp;
	int width;
	int height;
	int x;
	int y;
	int blank;

	blank = -1;
	itemp = type * MAX_SUBTYPE_ITEMS + index;

	if (itemp < 0) {
		g_Setup.MsgBox("Error() Insert Item in Shop %s %d", __FILE__, __LINE__);
		return false;
	}

	ItemGetSize(itemp, width, height);

	if (width < 0 || height < 0) {
		g_Setup.MsgBox("Error() Insert Item Size in Shop %s %d", __FILE__, __LINE__);
		return false;
	}

	for (y = 0; y < 15; y++) {
		for (x = 0; x < 8; x++) {
			if (this->ShopInventoryMap[x + y * 8] == 0) {
				blank = this->InentoryMapCheck(x, y, width, height);

				if (blank >= 0) {
					goto skiploop;
				}
			}
		}
	}

	if (blank < 0)
	{
		g_Setup.MsgBox("Error() %s %d", __FILE__, __LINE__);
		return false;
	}

skiploop:

	this->Items[blank].m_Level = level;

	if (dur == 0) {
		dur = g_GS.ItemGetDurability(ITEMGET(type, index), level, 0, 0);
	}

	this->Prices[blank] = price;

	this->Items[blank].m_Durability = dur;
	this->Items[blank].Convert(itemp, op1, op2, op3, exc, ancient, 1);
	this->Items[blank].Value();
	

	this->SendItemData[this->SendItemDataLen] = blank;
	this->SendItemDataLen++;

	ItemByteConvert((LPBYTE)&this->SendItemData[this->SendItemDataLen], this->Items[blank]);
	this->SendItemDataLen += 5;

	this->ItemCount++;

	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

int CShop::InentoryMapCheck(int CordX, int CordY, int Width, int Height)
{
	int X;
	int Y;
	int Blank = 0;

	if ((CordX + Width) > 8)
		return -1;

	if ((CordY + Height) > 15)
		return -1;

	for (Y = 0; Y < Height; Y++) {
		for (X = 0; X < Width; X++) {
			if (this->ShopInventoryMap[(CordY + Y) * 8 + (CordX + X)]) {
				Blank++;
				break;
			}
		}
	}

	if (Blank == 0) {
		for (Y = 0; Y < Height; Y++) {
			for (X = 0; X < Width; X++) {
				this->ShopInventoryMap[(CordY + Y) * 8 + (CordX + X)] = 1;
			}
		}

		return (CordX + CordY * 8);
	}

	return -1;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CShop::LoadShopItem(char* filename)
{
	int Token;
	int type;
	int index;
	int level;
	int dur;
	int op1;
	int op2;
	int op3;
	int exc;
	int ancient;
	int price;

	this->Init();

	SMDFile = fopen(filename, "r");

	if (SMDFile == NULL) {
		g_Setup.MsgBox("Shop data load error %s", filename);
		return false;
	}

	while (true) {
		Token = GetToken();

		if (Token == 2) break;

		if (Token == 1) {
			type = TokenNumber;

			Token = GetToken();
			index = TokenNumber;

			Token = GetToken();
			level = TokenNumber;

			Token = GetToken();
			dur = TokenNumber;

			Token = GetToken();
			op1 = TokenNumber;

			Token = GetToken();
			op2 = TokenNumber;

			Token = GetToken();
			op3 = TokenNumber;

			Token = GetToken();
			exc = TokenNumber;

			Token = GetToken();
			ancient = TokenNumber;
			//if(ancient)ancient |= 8;
	
			Token = GetToken();
			price = TokenNumber;

			if (false == this->InsertItem(type, index, level, dur, op1, op2, op3, exc, ancient, price)) {
				g_Setup.MsgBox("error-L3 : %s %s %d", filename, __FILE__, __LINE__);
			}
		}
	}

	fclose(SMDFile);

	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CShop::ShopRequest(int aIndex)
{
	g_GS.LogAdd("[%s][%s] requested : %d, `%s`", __FUNCTION__, gObj[aIndex].Name, this->ShopId, this->szShopFile);

	g_CoinShopLog.Output("[%s][%s][%d]: [%s][%s]: requested shop with `%s`",
		g_ModuleName, __FUNCTION__, this->ShopId, gObj[aIndex].AccountID, gObj[aIndex].Name, this->szShopFile);

	gObj[aIndex].TargetShopNumber = COIN_SHOP_START + this->ShopId + 1;

/*	gObj[aIndex].m_IfState.use = 1;
	gObj[aIndex].m_IfState.type = 3;
	gObj[aIndex].m_ShopTime = 0;*/

	PMSG_TALKRESULT pResult;

	pResult.h.c = 0xC3;
	pResult.h.headcode = 0x30;
	pResult.h.size = sizeof(pResult);
	pResult.result = 0;

	g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);

	BYTE SendByte[1024];
	PMSG_SHOPITEMCOUNT pShopItemCount;
	int lOfs = 0;

	lOfs += sizeof(pShopItemCount);

	int size = lOfs + this->SendItemDataLen;

	LPBYTE buf = (LPBYTE)&pShopItemCount;

	buf[0] = 0xC2;
	buf[1] = SET_NUMBERH(size);
	buf[2] = SET_NUMBERL(size);
	buf[3] = 0x31;

	pShopItemCount.Type = 0;
	pShopItemCount.count = this->ItemCount;

	memcpy(SendByte, &pShopItemCount, sizeof(pShopItemCount));
	memcpy(&SendByte[lOfs], this->SendItemData, this->SendItemDataLen);

	g_GS.DataSend(aIndex, SendByte, size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CShop::BuyRequest(int aIndex, BYTE bProductPos)
{
	OBJECTSTRUCT *  lpObj = &gObj[aIndex];

	g_GS.LogAdd("[%s][%s] requested : %d, `%s`", __FUNCTION__, lpObj->Name, this->ShopId, this->szShopFile);

	PMSG_BUYRESULT pResult;

	PHeadSetB((LPBYTE)&pResult, 0x32, sizeof(pResult));
	pResult.Result = -1;

	if (bProductPos > MAX_ITEM_IN_SHOP - 1) {
		g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
		return;
	}

	if (!PacketCheckTime(lpObj)) {
		g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
		return;
	}

	if (lpObj->CloseType != -1) {
		g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
		return;
	}

	if (!gObjFixInventoryPointer(aIndex)) {
		g_GS.LogAdd("[Fix Inv.Ptr] False Location - %s, %d", __FILE__, __LINE__);
	}

	/*if (gObj[aIndex].m_ShopTime == 0) {
		gObj[aIndex].m_ShopTime = 1;
	}

	if (gObj[aIndex].m_ShopTime > 	60) {
		if (lpObj->m_IfState.use != 0 && lpObj->m_IfState.type == 3) {
			lpObj->TargetShopNumber = -1;
			lpObj->m_IfState.use = 0;
			lpObj->m_IfState.type = 0;
		}

		g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
		return;
	}

	if (lpObj->m_IfState.use > 0 && lpObj->m_IfState.type != 3) {
		g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
		return;
	}*/

	if (this->Items[bProductPos].IsItem() == true) {
		if (gObjIsFreeSlotForItem(aIndex, this->Items[bProductPos])) {
			static bool isSrand = false;

			if (!isSrand) {
				srand(time(NULL));

				isSrand = true;
			}

			_NEW_OBJECT * nObject = &g_GS.nObject[FIXINDEX];

			 nObject->nBuyItemCode = (aIndex * 100)  + rand() % 10000;
			 nObject->bBuyProductPos = bProductPos;
			 nObject->buyShop = this;

			 g_Msg.Msg(aIndex, "@[Shop] to buy %s", this->Items[bProductPos].GetName());
			 g_Msg.Msg(aIndex, "@[Shop] with price %d coins", this->Prices[bProductPos]);
			 g_Msg.Msg(aIndex, "@[Shop] type /buy %d", nObject->nBuyItemCode);

			 g_CoinShopLog.Output("[%s][%s][%d]: [%s][%s]: requested buy item `%s` with price `%d`",
				 g_ModuleName, __FUNCTION__, this->ShopId, gObj[aIndex].AccountID, gObj[aIndex].Name, this->Items[bProductPos].GetName(), this->Prices[bProductPos]);

		} else {			
			g_Msg.Msg(aIndex, "@[Shop] : אין לך מספיק מקום כדי לרכוש חפץ זה");
		}
	}

	g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

void CShop::BuyResult(int aIndex, BYTE bProductPos, SHOP_BUY_RESULT eResult)
{
	PMSG_BUYRESULT pResult;

	PHeadSetB((LPBYTE)&pResult, 0x32, sizeof(pResult));

	pResult.Result = -1;

	if (eResult == SHOP_BUY_RESULT::SHOP_BUY_RESULT_NOCOINS) {
		g_Msg.Msg(aIndex, "@[Shop] אין לך מספיק מטבעות");
		g_Msg.Msg(aIndex, "@[Shop] מחיר החפץ הוא : %d", this->Prices[bProductPos]);
		g_Msg.Msg(aIndex, "@[Shop] כדי לקנות מטבעות הכנס לאתר muonline.co.il");

		g_CoinShopLog.Output("[%s][%s][%d]: [%s][%s]: no enough coins to buy the item",
			g_ModuleName, __FUNCTION__, this->ShopId, gObj[aIndex].AccountID, gObj[aIndex].Name);
	} else if (this->Items[bProductPos].IsItem() == true) {
		pResult.Result = gObjShopBuyInventoryInsertItem(aIndex, this->Items[bProductPos]);

		if (pResult.Result != 0xFF)
		{
			ItemByteConvert((LPBYTE)&pResult.ItemInfo, this->Items[bProductPos]);

			g_GS.LogAdd("[%s][%s][%s] Buy [%s] From (%d)(%s)",
				__FUNCTION__, gObj[aIndex].AccountID, gObj[aIndex].Name, this->Items[bProductPos].GetName(),
				this->ShopId, this->szShopFile);

			g_Msg.Msg(aIndex, "@[Shop] קנית את החפץ בהצלחה מחירו היה %d מטבעות", this->Prices[bProductPos]);

			g_GS.GCMoneySend(aIndex, gObj[aIndex].Money);

			g_CoinShopLog.Output("[%s][%s][%d]: [%s][%s]: buy successfuly item with %d, `%s`",
				g_ModuleName, __FUNCTION__, this->ShopId, gObj[aIndex].AccountID, gObj[aIndex].Name, this->ShopId, this->szShopFile);
		}
	} else {
		g_Msg.Msg(aIndex, "@[Shop] %s %d תקלה", __FILE__, __LINE__);
	}

	g_GS.DataSend(aIndex, (LPBYTE)&pResult, pResult.h.size);
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

bool CShop::LoadShops()
{
	free(Shops);

	char szTemp[1024] = { 0 };
	FILE * fHandler = NULL;

	do {
		sprintf(szTemp, "%s/shop%d.txt", SHOPS_FOLDER_PATH, bShopsCount);

		fHandler = fopen(szTemp, "r");

		if (fHandler) {
			++bShopsCount;
			fclose(fHandler);
		}

	} while (fHandler);

	Shops = new CShop[bShopsCount];

	bool bReturn = false;

	for (BYTE i = 0; i < bShopsCount; ++i) {
		sprintf(szTemp, "%s/shop%d.txt", SHOPS_FOLDER_PATH, i);
		
		Shops[i].ShopId = i;
		
		memset(Shops[i].szShopFile, 0, sizeof CShop().szShopFile);
		memcpy(Shops[i].szShopFile, szTemp, strlen(szTemp));

		if (bReturn = Shops[i].LoadShopItem(szTemp)) {
			g_CoinShopLog.Output("[%s][%s]: %s loaded",
				g_ModuleName, __FUNCTION__, szTemp);
			g_GS.LogAdd("[%s] `%s` Loaded", __FUNCTION__, szTemp);
		}
	}

	return bReturn;
}
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------