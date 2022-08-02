#pragma once



class TAutoMessageManager
{
public:
	static void Start();

private:
	static void loadMessages();
	static void worker();
};



