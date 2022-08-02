#pragma once

#define PACKET_1MB				1024
#define PACKET_2MB				PACKET_1MB * 2
#define PACKET_4MB				PACKET_2MB * 2
#define PACKET_8MB				PACKET_4MB * 2
#define PACKET_MAX_SIZE			PACKET_8MB
#define PACKET_STRING_END_FLAG  0x00

#define MAKE_NUMBERW(x,y)  ( (WORD)(((BYTE)((y)&0xFF)) |   ((BYTE)((x)&0xFF)<<8 ))  ) 
#define SET_NUMBERH(x) ( (BYTE)((DWORD)(x)>>(DWORD)8) )
#define SET_NUMBERL(x) ( (BYTE)((DWORD)(x) & 0xFF) )

class CPacket
{
private:
	BYTE			data[PACKET_MAX_SIZE];
	UINT			length;
	UINT			totalLength;


public:
	CPacket(BYTE type);
	CPacket(UCHAR* packet, UINT length);

	~CPacket();

	void writeByte(BYTE byte);
	void writeWord(WORD word);
	void writeLong(ULONG ulong);
	void writeString(std::string string);
	void writeString(UCHAR* string, UINT length);
	void writeBuffer(UCHAR* packet, UINT length);
	void writeSize(WORD wSize);


	BYTE			readByte();
	WORD			readWord();
	ULONG			readLong();
	std::string		readString();

	unsigned int __inline getLength()
	{
		return this->length;
	}

	void __inline setLength(UINT length)
	{
		this->length = length;
	}

	void __inline addLength(UINT amount)
	{
		this->length += amount;
		this->totalLength += amount;
	}

	// not good practice
	UINT __inline getLengthTotal()
	{
		return this->totalLength - 1;
	}

	std::string __inline getBuffer()
	{
		return std::string((char*)this->data, this->length);
	}


};

