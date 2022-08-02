#include "StreamPacketEngine_Client.h"
#include "Console.h"

CStreamPacketEngine_Client::CStreamPacketEngine_Client(void)
{
	this->Clear();
}

CStreamPacketEngine_Client::~CStreamPacketEngine_Client(void)
{
	return;
}

void CStreamPacketEngine_Client::Clear(void)
{
	this->m_wSize = 0;
}

void CStreamPacketEngine_Client::XorData(int iStart, int iEnd, int iDir)
{
	if (iStart > iEnd)
	{
		// @todo error msg 
		return;
	}

	BYTE byXorFilter[32];

	byXorFilter[0] = 0xE7;
	byXorFilter[1] = 0x6D;
	byXorFilter[2] = 0x3A;
	byXorFilter[3] = 0x89;
	byXorFilter[4] = 0xBC;
	byXorFilter[5] = 0xB2;
	byXorFilter[6] = 0x9F;
	byXorFilter[7] = 0x73;
	byXorFilter[8] = 0x23;
	byXorFilter[9] = 0xA8;
	byXorFilter[10] = 0xFE;
	byXorFilter[11] = 0xB6;
	byXorFilter[12] = 0x49;
	byXorFilter[13] = 0x5D;
	byXorFilter[14] = 0x39;
	byXorFilter[15] = 0x5D;
	byXorFilter[16] = 0x8A;
	byXorFilter[17] = 0xCB;
	byXorFilter[18] = 0x63;
	byXorFilter[19] = 0x8D;
	byXorFilter[20] = 0xEA;
	byXorFilter[21] = 0x7D;
	byXorFilter[22] = 0x2B;
	byXorFilter[23] = 0x5F;
	byXorFilter[24] = 0xC3;
	byXorFilter[25] = 0xB1;
	byXorFilter[26] = 0xE9;
	byXorFilter[27] = 0x83;
	byXorFilter[28] = 0x29;
	byXorFilter[29] = 0x51;
	byXorFilter[30] = 0xE8;
	byXorFilter[31] = 0x56;

	for (int i = iStart; i != iEnd; i += iDir)
	{
		this->m_byBuffer[i] ^= this->m_byBuffer[i - 1] ^ byXorFilter[i % 32];
	}
}

BOOL CStreamPacketEngine_Client::AddData(void* pSrc, WORD wSize)
{
	if (((this->m_wSize + wSize) >= 2048) || (wSize == 0))
	{
		Console.Write("[CStreamPacketEngine_Client] addData failed: m_wSize: `%d`, wSize: `%d`", this->m_wSize, wSize);
		int iSize = 2048;
		return FALSE;
	}

	memcpy((void*)& this->m_byBuffer[this->m_wSize], pSrc, wSize);
	this->m_wSize += wSize;
	return TRUE;
}

BOOL CStreamPacketEngine_Client::ExtractPacket(void* pTar)
{
	WORD wSize;
	BYTE byXorFilter[32];
	BYTE byTemp[2048];
	switch (this->m_byBuffer[0])
	{
	case 0xC1:
		wSize = this->m_byBuffer[1];
		break;

	case 0xC2:
		wSize = this->m_byBuffer[1] * 256 + this->m_byBuffer[2];
		break;

	default:
		return true;
		break;
	}

	if (this->m_wSize < wSize)
	{
		Console.Write("[CStreamPacketEngine_Client] ExtractPacket failed: m_wSize: `%d`, wSize: `%d`", this->m_wSize, wSize);

		return 2;
	}

	this->XorData((this->m_byBuffer[0] == 0xC1 ? 2 : 3) + 1, wSize, 1);
	memcpy(pTar, this->m_byBuffer, wSize);
	this->m_wSize -= wSize;
	memcpy(byTemp, &this->m_byBuffer[wSize], this->m_wSize);
	memcpy(this->m_byBuffer, byTemp, this->m_wSize);
	return false;
}
