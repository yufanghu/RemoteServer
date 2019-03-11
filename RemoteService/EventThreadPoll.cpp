#include "EventThreadPoll.h"
#include "ConnPoller.h"
#include "IOEventLoop.h"
CEventThreadPoll::CEventThreadPoll(int maxThreadCount) : _curThread(maxThreadCount)
{

}

CEventThreadPoll::~CEventThreadPoll()
{
}

void CEventThreadPoll::Start()
{
	for (int i = 0; i < _curThread; ++i) {
		CConnPoller * poller = new CConnPoller();
		std::shared_ptr<CConnPoller> aPoller(poller);
		
		auto loop = new CIOEventLoop();
		loop->SetPoller(aPoller);
		std::shared_ptr<CIOEventLoop> aloop(loop);
		_loops.push_back(aloop);
	}

	/*_acceptLoop = std::make_shared<CIOEventLoop>(new CAcceptorLoop());*/
}

void CEventThreadPoll::Stop()
{
	for (int i = 0; i < _curThread; ++i) {
		_loops[i]->Stop();
	}
	_loops.empty();
}

std::shared_ptr<CIOEventLoop> CEventThreadPoll::GetNextLoop()
{
	if (_curThread == 3)
		_curThread = 0;
	std::shared_ptr<CIOEventLoop> temp =  _loops[_curThread];
	_curThread++;
	return temp;
}
