#include "IOEventLoop.h"



CIOEventLoop::CIOEventLoop() : _bRunning(false)
{
}


CIOEventLoop::~CIOEventLoop()
{
}

void CIOEventLoop::Start()
{
	_bRunning = true;
}

void CIOEventLoop::Stop()
{
	_bRunning = false;
}
