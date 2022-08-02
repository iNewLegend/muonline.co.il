#include "Stdafx.h"
#include "TPacket.h"
//-----------------------------------------------------------------------------------------------------------
// made by Leo123 (czf.leo123@gmail.com) Leonid Vinikov
//-----------------------------------------------------------------------------------------------------------

CPacket::CPacket(BYTE type)
{
	totalLength = 0;
	memset(this->data, 0, PACKET_MAX_SIZE);

	// reversed for header
	if (type == 0xC2) {
		setLength(3);
	}
	else
	{
		setLength(2);
	}

	this->data[0] = type;
}

CPacket::CPacket(UCHAR* packet, UINT length)
{
	totalLength = 0;
	memset(this->data, 0, PACKET_MAX_SIZE);

	writeBuffer(packet, length);

	// reversed for header
	if (packet[0] == 0xC2) {
		setLength(4);
	}
	else
	{
		setLength(3);
	}

}

CPacket::~CPacket()
{
}
// ----
// # writers

// # writeByte (byte)
// # 1 size length
// ----
void CPacket::writeByte(BYTE byte)
{
	this->data[getLength()] = byte;

	addLength(1);
}

// # writeWord (word)
// # 2 size length
// ----
void CPacket::writeWord(WORD word)
{
	writeByte(LOBYTE(word));
	writeByte(HIBYTE(word));
}

// # writeLong (uLong)
// # 4 size length
// ----
void CPacket::writeLong(ULONG uLong)
{
	writeWord(LOWORD(uLong));
	writeWord(HIWORD(uLong));
}

// # writeString (string)
// # dnyamic size length
// ----
void CPacket::writeString(std::string string)
{
	memcpy(&this->data[getLength()], string.c_str(), string.length());
	memset(&this->data[getLength() + string.length()], PACKET_STRING_END_FLAG, 1);

	addLength(string.length() + 1);
}

void CPacket::writeString(UCHAR * string, UINT length)
{
	std::string newString;

	newString.insert(0, (char*)string, length);

	this->writeString(newString); // it just just parse so i don't know why, its not working...
}

void CPacket::writeBuffer(UCHAR * packet, UINT length)
{
	memcpy(this->data, packet, length);

	addLength(length + 1);
}

void CPacket::writeSize(WORD wSize)
{
	UINT length = getLength();

	setLength(1);

	if (this->data[0] == 0xC2) {
		writeByte(SET_NUMBERH(wSize));
		writeByte(SET_NUMBERL(wSize));
	}
	else {
		writeByte((BYTE)wSize);
	}

	setLength(length);
}

// ----
// # readers

BYTE CPacket::readByte()
{
	BYTE b = this->data[getLength()];
	addLength(1);
	return b;
}

WORD CPacket::readWord()
{
	BYTE a, b;
	a = readByte();
	b = readByte();

	return MAKEWORD(a, b);

	//return MAKEWORD(readByte(), readByte());
}

ULONG CPacket::readLong()
{
	WORD a = readWord();
	WORD b = readWord();

	return MAKELONG(a, b);
}

std::string	CPacket::readString()
{
	std::string sReturn;

	sReturn.insert(0, (char*)& this->data[getLength()]);

	addLength(sReturn.length() + 1);

	return sReturn;
}