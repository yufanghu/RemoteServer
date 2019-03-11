#pragma once
struct epoll_event;
class CIO
{
public:
	CIO();
	~CIO();
	
	void Read(epoll_event * pEvent);
	
	void Write(epoll_event * pEvent);
	
	int Accept(epoll_event * pEvent);
private:

};

