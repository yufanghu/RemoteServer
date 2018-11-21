#include "EpollServer.h"
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

CEpollServer::CEpollServer(int port) : _listenfd(-1), _port(port), _bRunning(false), _epollfd(-1)
{
}


CEpollServer::~CEpollServer()
{
}

void CEpollServer::InitSocket()
{
	_listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_listenfd < 0) {
		printf("socket create failed\n");
		exit(0);
	}

	int flag = 1;
	setsockopt(_listenfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (-1 == bind(_listenfd, (sockaddr*)&addr, sizeof(addr))) {
		printf("bind failed\n");
		exit(0);
	}

	if (-1 == listen(_listenfd, 10)) {
		printf("listen failed\n");
		exit(0);
	}
}

void CEpollServer::Startup()
{
	InitSocket();
	_bRunning = true;

	 _epollfd = epoll_create(256);
	if (_epollfd < 0) {
		printf("epoll_create failed\n");
		exit(0);
	}

	epoll_event eEvent;
	eEvent.events = EPOLLIN;
	eEvent.data.fd = _listenfd;
	epoll_ctl(_epollfd, EPOLL_CTL_ADD, _listenfd, &eEvent);

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
				int fd = events[i].data.fd;
				if (fd == _listenfd && (events[i].events & EPOLLIN)) {//ÓÐÐÂµÄconnection
					handle_accept();
				}
				else if (events[i].events & EPOLLIN) {
					handle_recv(events[i].data.fd);
				}
			}
		}


	}
}

void CEpollServer::handle_recv(int fd)
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

void CEpollServer::handle_accept()
{
	struct sockaddr_in peer;
	socklen_t len = sizeof(peer);

	int new_fd = accept(_listenfd, (struct sockaddr*)&peer, &len);
	if (new_fd > 0) {
		int fl = fcntl(new_fd, F_GETFL);
		fcntl(new_fd, F_SETFL, fl | O_NONBLOCK);


		epoll_event eEvent;
		eEvent.events = EPOLLIN | EPOLLET;
		eEvent.data.fd = new_fd;
		epoll_ctl(_epollfd, EPOLL_CTL_ADD, new_fd, &eEvent);

		printf("new accept");
	}


}