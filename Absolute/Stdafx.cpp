// stdafx.cpp : source file that includes just the standard includes
// Absolute.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "bass.lib")


char	StreamBuffUrl[100]	= "http://radio.muonline.co.il:6969/";
DWORD	StreamUrl			= 0;

// leo : bad practice;

int char2int(char input)
{
	if (input >= '0' && input <= '9')
		return input - '0';
	if (input >= 'A' && input <= 'F')
		return input - 'A' + 10;
	if (input >= 'a' && input <= 'f')
		return input - 'a' + 10;
	
	throw "test";
}

// This function assumes src to be a zero terminated sanitized string with
// an even number of [0-9a-f] characters, and target to be sufficiently large
void hex2bin(const char* src, char* target)
{
	while (*src && src[1])
	{
		*(target++) = char2int(*src) * 16 + char2int(src[1]);
		src += 2;
	}
}

std::string urlencode(const std::string &c)
{
	std::string escaped = "";
	int max = c.length();
	for (int i = 0; i<max; i++)
	{
		if ((48 <= c[i] && c[i] <= 57) ||//0-9
			(65 <= c[i] && c[i] <= 90) ||//abc...xyz
			(97 <= c[i] && c[i] <= 122) || //ABC...XYZ
			(c[i] == '~' || c[i] == '!' || c[i] == '*' || c[i] == '(' || c[i] == ')' || c[i] == '\'')
			)
		{
			escaped.append(&c[i], 1);
		}
		else
		{
			escaped.append("%");
			escaped.append(char2hex(c[i]));//converts char 255 to string "ff"
		}
	}
	return escaped;
}

std::string char2hex(char dec)
{
	char dig1 = (dec & 0xF0) >> 4;
	char dig2 = (dec & 0x0F);
	if (0 <= dig1 && dig1 <= 9) dig1 += 48;    //0,48inascii
	if (10 <= dig1 && dig1 <= 15) dig1 += 97 - 10; //a,97inascii
	if (0 <= dig2 && dig2 <= 9) dig2 += 48;
	if (10 <= dig2 && dig2 <= 15) dig2 += 97 - 10;

	std::string r;
	r.append(&dig1, 1);
	r.append(&dig2, 1);
	return r;
}