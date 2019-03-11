#pragma once
#include <memory>
class CEventThreadPoll;
class CTcpServer
{
public:
	CTcpServer();
	~CTcpServer();

	void Start();

private:
	std::shared_ptr<CEventThreadPoll> _eventPoll;
};

