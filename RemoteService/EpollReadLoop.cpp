#include "EpollReadLoop.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<sys/epoll.h>
#include <fcntl.h>
#include <string>


CEpollReadLoop::CEpollReadLoop()
{
}


CEpollReadLoop::~CEpollReadLoop()
{
}


void CEpollReadLoop::Start()
{
	CIOEventLoop::Start();

}
void CEpollReadLoop::Stop()
{
	CIOEventLoop::Stop();
}

void CEpollReadLoop::init_epoll()
{
	_epollfd = epoll_create(256);
	if (_epollfd < 0) {
		printf("epoll_create failed\n");
		exit(0);
	}

}

void CEpollReadLoop::loop()
{
	epoll_event events[256];
	int timeout = -1;
	while (_bRunning) {
		int count = epoll_wait(_epollfd, events, 256, timeout);

		if (count == 0) {
			printf("timeout\n");
			continue;
		}
		else if (count < 0) {
			printf("error\n");
			continue;
		}
		else {

			printf("events....\n");
			for (int i = 0; i < count; ++i) {
				if (events[i].events & EPOLLIN) {
					handle_recv(events[i].data.fd);
				}
			}
		}
	}
}

void CEpollReadLoop::AddFD(int fd)
{
	epoll_event eEvent;
	eEvent.events = EPOLLIN;
	eEvent.data.fd = fd;
	epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd, &eEvent);
}

void CEpollReadLoop::handle_recv(int fd)
{
	const static int chunck_size = 512;

	std::string data;
	data.reserve(256);
	char buf[chunck_size] = { 0 };

	printf("handle_recv\n");

	while (1) {
		memset(buf, 0, sizeof(buf));
		int ret = ::read(fd, buf, sizeof(buf));
		if (ret == -1) {
			int err = errno;
			if (err == EINTR) {
				continue;
			}

			break;
		}
		if (0 == ret) {
			printf("closed by client");
			epoll_ctl(_epollfd, EPOLL_CTL_DEL, fd, NULL);
			::close(fd);
		}
		else {
			data += buf;
		}
	}
	if (!data.empty())
		printf("%s\n", data.c_str());
}