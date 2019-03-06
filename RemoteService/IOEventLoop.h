#pragma once
#include <memory>
#include <thread>
class EPoller;
class CIOEventLoop
{
public:
	CIOEventLoop();
	~CIOEventLoop();

	virtual void Start() = 0;

	virtual void Stop() = 0;

	void SetPoller(std::shared_ptr<EPoller> pollerPtr);

private:
	virtual void Loop() = 0;

protected:
	std::shared_ptr<EPoller> _pollerPtr;
	std::thread _threadPtr;
	bool _bRunning;
};

