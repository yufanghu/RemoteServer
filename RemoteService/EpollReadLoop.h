#ifndef _EPOLL_READ_LOOP
#define _EPOLL_READ_LOOP
#include "IOEventLoop.h"

class CEpollReadLoop : public CIOEventLoop
{
public:
	CEpollReadLoop();
	~CEpollReadLoop();
	virtual void Start() override;
	virtual void Stop() override;
	void AddFD(int fd);
private:
	void init_epoll();
	void loop();
	void handle_recv(int fd);
private:
	int _epollfd;
};

#endif

