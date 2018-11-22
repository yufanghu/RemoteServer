#include "RobinThreadPoll.h"

using namespace pool;
RobinThreadPoll::RobinThreadPoll(int num): _thread_count(num), _round_index(0), _running(false)
{

}


RobinThreadPoll::~RobinThreadPoll()
{
}

pool::RobinTask* pool::RobinThreadPoll::get_next_task()
{

}

void pool::RobinThreadPoll::start()
{
	_running = true;
}

void pool::RobinThreadPoll::stop()
{
	_running = false;
}

pool::RobinTask::RobinTask() : _running(false)
{

}

pool::RobinTask::~RobinTask()
{

}

void pool::RobinTask::start()
{
	_running = true;
	_threads = std::make_shared<std::thread>([this]() {
		while (_running) {
			std::unique_lock<std::mutex> lock(_mutex);
			while(_events.empty())
				_cond.wait(lock);
			if (!_running)
				break;
			Event * task = _events.front();
			_events.pop_front();
			lock.unlock();

			task->work();
		}
	});
}

void pool::RobinTask::stop()
{
	_running = false;
	_threads->join();
}

void pool::RobinTask::add_event(Event* es)
{
	std::unique_lock<std::mutex> lock(_mutex);
	_cond.notify_one();
	_events.push_back(es);
}
