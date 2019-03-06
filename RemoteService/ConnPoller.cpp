#include "EPoller.h"
#include <stdlib.h>
#include <string.h>
#include "Channel.h"
#include "ConnPoller.h"
#include "IO.h"

CConnPoller::CConnPoller() : _epollfd(-1)/*, _ioPtr(std::make_shared<CIO>())*/
{

}


CConnPoller::~CConnPoller()
{
}


void CConnPoller::Wait()
{
	int nums = epoll_wait(_epollfd, _events, 1, 100);
	for (int i = 0; i < nums; ++i) {
		if (_events[i].events&EPOLLIN) {
			_ioPtr->Read(&_events[i]);
		}
		else if (_events[i].events&EPOLLOUT) {
			_ioPtr->Write(&_events[i]);
		}
		else {
			printf("err...........\n");
		}

	}
}





