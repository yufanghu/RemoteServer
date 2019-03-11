#include "IO.h"
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
CIO::CIO()
{
}


CIO::~CIO()
{

}

void CIO::Read(epoll_event * pEvent)
{

}

void CIO::Write(epoll_event * pEvent)
{

}

int CIO::Accept(epoll_event * pEvent)
{
	sockaddr_in addr;
	auto length = sizeof(addr);
	int fd = accept(pEvent->data.fd, (sockaddr*)&addr, NULL);
	return fd;
}
