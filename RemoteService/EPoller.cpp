#include "EPoller.h"
#include <stdlib.h>
#include <string.h>
#include "Channel.h"
#include "IO.h"
EPoller::EPoller() : _epollfd(-1), _ioPtr(std::make_shared<CIO>())
{

}


EPoller::~EPoller()
{

}


void EPoller::Update(int fd, EPollState state)
{
	epoll_event ev;
	ev.data.fd = fd;
	ev.events = EPOLLIN | ((ELT == state) ? EPOLLET : 0);
	switch (state) {
	case EAdd:
		epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &ev);
		break;
	case EModify:
		epoll_ctl(_epollfd, EPOLL_CTL_MOD, fd, &ev);
		break;
	case EDel:
		epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, &ev);
		break;
	default:
		//error log
		break;
	}
}
void EPoller::InitCreate(int size/* = EPOLL_SIZE*/)
{
	_epollfd = epoll_create(size);
	if (_epollfd)
		exit(0);
}



