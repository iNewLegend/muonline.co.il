#include "StdAfx.h"
#include "Console.h"

Logger Console;
DWORD PiD;


void __stdcall LoggerCore(PVOID pVoid)
{

	#if(ABSOLUTE_CONSOLE == ON)

    AllocConsole();
    system("color f0");
	
	do {
		Sleep(1);
	}
    while(true);
	
	#endif
}

void Logger::Init()
{
	#if(ABSOLUTE_CONSOLE == ON)

    CreateThread( 0 , 0 , (LPTHREAD_START_ROUTINE) LoggerCore , 0 , 0 , &PiD ); 
    Sleep(100);
        
	this->Write("MuOnline.co.il developer console");

	#endif
}
void Logger::Write(const char* Format, ...)
{
	#if(ABSOLUTE_CONSOLE == ON)

    char Message[1024];
    DWORD dwBytesWritten;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    va_list pArguments;
    va_start(pArguments, Format);
    vsprintf(Message,Format, pArguments);
    va_end(pArguments);
    char outputmsg[2048];
    sprintf(outputmsg,"%s\n", Message);
    WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);
	
	#endif
}
void Logger::WriteDT(const char* Format, ...)
{
	#if(ABSOLUTE_CONSOLE == ON)

    SYSTEMTIME t;
    GetLocalTime(&t);

    char Message[1024];
    DWORD dwBytesWritten;
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
    va_list pArguments;
    va_start(pArguments, Format);
    vsprintf(Message,Format, pArguments);
    va_end(pArguments);
    char currdate[11] = {0};
    sprintf(currdate, "%02d:%02d:%02d", t.wHour, t.wMinute, t.wSecond);
    char outputmsg[2048];
    sprintf(outputmsg,"%s %s\n", currdate,Message);
    WriteFile(Handle, outputmsg, strlen(outputmsg), &dwBytesWritten, NULL);

	#endif
}
