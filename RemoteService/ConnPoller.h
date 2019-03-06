#pragma once
#include "EPoller.h"

class CConnPoller : public EPoller
{
public:
	CConnPoller();
	~CConnPoller();

	virtual void Wait() override;

private:
	enum { EVENT_SIZE = 512 };
	epoll_event _events[EVENT_SIZE];
	int _epollfd;

};

