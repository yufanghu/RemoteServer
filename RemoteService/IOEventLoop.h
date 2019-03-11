#pragma once
#include <memory>
#include <thread>
class EPoller;
class CIOEventLoop
{
public:
	CIOEventLoop();
	~CIOEventLoop();

	void Start();

	void Stop();

	void SetPoller(std::shared_ptr<EPoller> pollerPtr);

private:
	virtual void Loop();

	void HandleRecv(int fd, int pos);

protected:
	std::shared_ptr<EPoller> _pollerPtr;
	std::shared_ptr<std::thread> _threadPtr;
	bool _bRunning;
};

