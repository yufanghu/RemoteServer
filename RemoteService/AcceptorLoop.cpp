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

CAcceptorLoop::CAcceptorLoop(int listenfd, FuncAccept func) : _listenfd(listenfd), _callback(func)
{
}

CAcceptorLoop::~CAcceptorLoop()
{

}



void CAcceptorLoop::handle_accept()
{
	struct sockaddr_in client;
	socklen_t len = sizeof(client);

	int new_fd = accept(_listenfd, (struct sockaddr*)&client, &len);

	int flag = fcntl(new_fd, F_GETFL, 0);
	fcntl(new_fd, F_SETFL, flag | O_NONBLOCK);


	_callback(new_fd);
}

