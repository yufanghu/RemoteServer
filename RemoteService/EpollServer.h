#ifndef _EPOLL_SERVER_H
#define _EPOLL_SERVER_H

class CEpollServer
{
public:
	CEpollServer(int port);
	~CEpollServer();

	void Startup();
private:
	void InitSocket();
	void handle_accept();
	void handle_recv(int fd);
private:
	int _listenfd;
	int _epollfd;
	int _port;
	bool _bRunning;
};

#endif

