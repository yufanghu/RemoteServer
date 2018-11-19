#include "AcceptorLoop.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#include<fcntl.h>
#include <stdio.h>

CAcceptorLoop::CAcceptorLoop(int listenfd): _listenfd(listenfd)
{
}

CAcceptorLoop::~CAcceptorLoop()
{
}

void CAcceptorLoop::Start()
{
	_bRunning = true;
	fd_set temp_set;
	FD_SET(_listenfd, &temp_set);
	int _max_fd = _listenfd;
	while (_bRunning) {
		fd_set fd_copy = temp_set;
		//如果ret大于0表示返回就绪的描述的个数
		int ret = select(_max_fd + 1, &fd_copy, NULL, NULL, NULL);
		if (ret < 0) {
			printf("error\n");
		}
		else if (ret == 0) {
			printf("timeout\n");
		}
		else {
			//有可读
			if (FD_ISSET(_listenfd, &fd_copy)) {
				handle_accept();
			}
		}
	}
}

void CAcceptorLoop::handle_accept()
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	int new_fd = accept(_listenfd, (struct sockaddr*)&client, &len);

	int flag = fcntl(new_fd, F_GETFL, 0);
	fcntl(new_fd, F_SETFL, flag | O_NONBLOCK);
}

void CAcceptorLoop::Stop()
{

}
