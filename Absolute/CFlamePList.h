#pragma once
#include "Stdafx.h"
#include <vector>
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>

class CFlamePList {
public:
	CFlamePList();
	~CFlamePList();
	std::vector<std::string> GetProccessList();
private:
	void GenerateProccessList();
	std::vector<std::string> mProccessList;
};

