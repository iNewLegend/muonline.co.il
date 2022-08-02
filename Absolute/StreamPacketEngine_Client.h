#pragma once 

#include "Stdafx.h"

class CStreamPacketEngine_Client
{
public:
	CStreamPacketEngine_Client(void);
	~CStreamPacketEngine_Client(void);
	void Clear(void);
	BOOL AddData(void* pSrc, WORD wSize);
	BOOL ExtractPacket(void* pTar);
protected:
	void XorData(int iStart, int iEnd, int iDir);
private:
	WORD m_wSize;
	BYTE m_byBuffer[2048];
};