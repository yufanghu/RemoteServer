#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

#include <thread>
#include <deque>
#include <memory>
#include <vector>
#include <condition_variable>
#include <mutex>

class CTask;
class CThreadPooll
{
public:
	CThreadPooll(int maxThreadCount);
	~CThreadPooll();

	void Start();

	void Stop();

	void AddTask(CTask * pTask);

private:
	int _maxThreadCount;
	bool _bActive;
	
	std::deque<CTask*> m_taskQueue;

	std::vector<std::shared_ptr<std::thread>> m_threadVct;

	std::condition_variable _condition;

	std::mutex _mutex;
};

#endif

