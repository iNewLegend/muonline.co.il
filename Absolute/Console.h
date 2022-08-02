#pragma once

class Logger
{
public:
    void Init();
    void Write(const char* Format, ...);
    void WriteDT(const char* Format, ...);

};

extern Logger Console;