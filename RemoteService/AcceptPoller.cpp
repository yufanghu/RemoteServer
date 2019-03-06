#include "AcceptPoller.h"
#include "IO.h"
CAcceptPoller::CAcceptPoller()
{
}


CAcceptPoller::~CAcceptPoller()
{
}

void CAcceptPoller::Wait()
{
	epoll_event ev;
	int nums = epoll_wait(_epollfd, &ev, 1, 100);
	for (int i = 0; i < nums; ++i) {
		//connect or accept
		if (ev.events&EPOLLIN) {
			_ioPtr->Read(&ev);
		}
		else {
			printf("err...........\n");
		}
	}
}
