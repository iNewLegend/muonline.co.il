#include "CFlamePList.h"

CFlamePList::CFlamePList () {

}

std::vector<std::string> CFlamePList::GetProccessList()
{
	mProccessList.clear();
	this->GenerateProccessList();
	
	return mProccessList;
}

void CFlamePList::GenerateProccessList()
{
	HANDLE hSnaphot, hProccess;
	PROCESSENTRY32 pe32;
	std::vector < std::string > ::iterator it = mProccessList.begin();
	
	hSnaphot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnaphot == INVALID_HANDLE_VALUE) {
		throw new std::exception("Failed to acquire process snapshot");
	}

	pe32.dwSize = sizeof(PROCESSENTRY32);
	
	if (!Process32First(hSnaphot, &pe32)) {
		CloseHandle(hSnaphot);
		throw new std::exception("Failed to get proclist");		
	}

	do {

		it = mProccessList.insert(it, pe32.szExeFile);
	} while (Process32Next(hSnaphot, &pe32));

	CloseHandle(hSnaphot);
}
