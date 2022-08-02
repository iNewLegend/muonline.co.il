#ifndef _CCRC32_H
#define _CCRC32_H

#define CRC32_POLYNOMIAL 0x04C11DB7
#define CRC32BUFSZ 1024

struct tagCRC32 
{
	char filePath[100];
	long crc32;

	tagCRC32()
	{
		memset(this->filePath, 0, sizeof(this->filePath));

		this->crc32 = 0;
	}
};

struct tagCRC32Holder
{
	tagCRC32 crc32[200];
	BYTE	 bCount;
};

struct crc32Package
{
	BYTE Head;
	tagCRC32Holder tData;
};

class CCRC32
{
	public:
		void Initialize(void);
		unsigned long FileCRC(const char *sFileName);
		unsigned long FullCRC(unsigned char *sData, unsigned long ulLength);
		void PartialCRC(unsigned long *ulInCRC, unsigned char *sData, unsigned long ulLength);

	private:
		unsigned long Reflect(unsigned long ulReflect, char cChar);
		unsigned long ulTable[256];
};

#endif