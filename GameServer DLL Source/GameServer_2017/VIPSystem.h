#pragma once
class VIPSystem
{
private:
	// ---- VIP System -----
	bool	IsVIPSystemOn;
	int		bGSVIPCode;
	// Bronze VIP
	bool	bPostCommand;
	bool	bOffTradeCommand;
	bool	bVIPSing;
	int		bVIPDays;
	int		bVIPPrice;
	// Silver VIP
	bool	sPostCommand;
	bool	sOffTradeCommand;
	bool	sVIPSing;
	int		sVIPDays;
	int		sVIPPrice;
	// Gold VIP
	bool	gPostCommand;
	bool	gOffTradeCommand;
	bool	gVIPSing;
	int		gVIPDays;
	int		gVIPPrice;
	// Platinum VIP
	bool	pPostCommand;
	bool	pOffTradeCommand;
	bool	pVIPSing;
	int		pVIPDays;
	int		pVIPPrice;
	// ----

public:
	VIPSystem();
	~VIPSystem();
	// -----

	void Init();
	bool RequestVIPBonus(int aIndex, int RequestCode);
	void VIPBuyRequest(int aIndex, int VipLevel);
	LPCSTR RequestVipLevelName(int VipLevel, int Lang);
};

extern VIPSystem g_VIPSystem;