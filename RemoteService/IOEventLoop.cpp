#include "IOEventLoop.h"

CIOEventLoop::CIOEventLoop() : _bRunning(false)
{
}


CIOEventLoop::~CIOEventLoop()
{
}

void CIOEventLoop::SetPoller(std::shared_ptr<EPoller> pollerPtr)
{
	_pollerPtr = pollerPtr;
}

void CIOEventLoop::Start()
{
	
	if (!_bRunning) {
		_bRunning = true;
		/*_pollerPtr = std::make_shared<std::thread>(std::bind(CIOEventLoop::bind);*/
	}

}

void CIOEventLoop::Stop()
{
	_bRunning = false;
}
