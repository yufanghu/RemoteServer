#pragma once
#include <functional>
typedef std::function<void(int)> FuncAccept;
class CAcceptorLoop 
{
public:
	CAcceptorLoop(int _listenfd, FuncAccept func);
	~CAcceptorLoop();
	
private:
	void handle_accept();
private:
	int _listenfd;
	FuncAccept _callback;
};

