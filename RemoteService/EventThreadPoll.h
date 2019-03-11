#pragma once
#include <functional>
#include <vector>
#include <thread>
class CIOEventLoop;
class CEventThreadPoll
{
	typedef std::function<void(int fd)> FuncPool;
public:
	CEventThreadPoll(int maxThreadCount);
	~CEventThreadPoll();

	void Start();

	void Stop();

	std::shared_ptr<CIOEventLoop> GetNextLoop();

private:
	int _curThread;
	std::vector<std::shared_ptr<CIOEventLoop>> _loops;
	std::shared_ptr<CIOEventLoop> _acceptLoop;
};

