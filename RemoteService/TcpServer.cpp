#include "TcpServer.h"
#include "EventThreadPoll.h"
#include "AcceptorLoop.h"
CTcpServer::CTcpServer() : _eventPoll(std::make_shared<CEventThreadPoll>(new CEventThreadPoll(5)))
{

}


CTcpServer::~CTcpServer()
{
}

void CTcpServer::Start()
{
	_eventPoll->Start();
}
