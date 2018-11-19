#include "ThreadPooll.h"
#include <iostream>
#include "Task.h"

CThreadPooll::CThreadPooll(int maxThreadCount) : _maxThreadCount(maxThreadCount),
_bActive(true)
{

}


CThreadPooll::~CThreadPooll()
{
}

void CThreadPooll::Start()
{
	m_threadVct.reserve(_maxThreadCount);

	for (int i = 0; i < _maxThreadCount; ++i){
		
		auto func = [this](){

			while (_bActive){
				std::unique_lock<std::mutex> lock(_mutex);
				
				while (m_taskQueue.empty()){
					_condition.wait(lock);

					if (!_bActive)
						break;
				}

				if (!_bActive)
					break;

				if (m_taskQueue.empty())
					continue;
				
				CTask * task = m_taskQueue.front();
				m_taskQueue.pop_front();
				
				lock.unlock();
				//std::cout << std::this_thread::get_id() << std::endl;
				task->Run();
			}

		};

		m_threadVct.emplace_back(std::make_shared<std::thread>(func));
	}
}

void CThreadPooll::Stop()
{
	_bActive = false;

	std::unique_lock<std::mutex> lock(_mutex);
	_condition.notify_all();
	lock.unlock();
	for (auto i = 0; i < m_threadVct.size(); ++i){
		if (m_threadVct.at(i)->joinable())
			m_threadVct.at(i)->join();
	}
	m_threadVct.clear();
}

void CThreadPooll::AddTask(CTask * pTask)
{
	std::unique_lock<std::mutex> lock(_mutex);
	m_taskQueue.emplace_back(pTask);
	_condition.notify_one();
}

