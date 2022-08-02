//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __SHOP_H__
#define __SHOP_H__
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef GS_99_60T
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#include "item.h"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define SHOPS_FOLDER_PATH "../../coinshop"
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

#define MAX_ITEM_IN_SHOP 120
#define COIN_SHOP_START 32000
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

class CShop
{
protected:
	CItem Items[MAX_ITEM_IN_SHOP];
	BYTE ShopInventoryMap[MAX_ITEM_IN_SHOP];

	int ItemCount;
	BYTE SendItemData[MAX_ITEM_IN_SHOP*(MAX_ITEM_INFO + 1)];
	int SendItemDataLen;


	void	Init();
	bool	InsertItem(int type, int index, int level, int dur, int op1, int op2, int op3, int exc, int anceint, int price);
	int		InentoryMapCheck(int CordX, int CordY, int Width, int Height);
	bool	LoadShopItem(char* filename);

public:
	void	ShopRequest(int aIndex);
	void	BuyRequest(int aIndex, BYTE bProductPos);
	void	BuyResult(int aIndex, BYTE bProductPos, SHOP_BUY_RESULT eResult);

	int Prices[MAX_ITEM_IN_SHOP];
	char szShopFile[1024];
	int ShopId;

	static BYTE bShopsCount;

	static CShop * Shops;
	static bool LoadShops	();

};
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#endif
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------