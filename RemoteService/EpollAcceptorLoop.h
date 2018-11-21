#ifndef _EPOLL_ACCEPTOR_LOOP
#define _EPOLL_ACCEPTOR_LOOP

#include "IOEventLoop.h"
class CEpollAcceptorLoop : public CIOEventLoop
{
public:
	CEpollAcceptorLoop(int port);
	~CEpollAcceptorLoop();

	virtual void Start() override;

	virtual void Stop() override;
private:
	void init_socket();
	void loop();
	void handle_accept();
private:
	int _listenfd;
	int _port;
	int _epollfd;
};

#endif
