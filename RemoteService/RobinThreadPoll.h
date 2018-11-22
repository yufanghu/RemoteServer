#ifndef _ROBIN_THREAD_POLL
#define _ROBIN_THREAD_POLL
#include <thread>
#include <vector>
#include <deque>
#include <condition_variable>
namespace pool {
	typedef std::shared_ptr<std::thread> thread_ptr;

	class Event {
	public:
		Event() {}
		~Event() {}
		virtual void work() = 0;
	};

	class RobinTask {
	public:
		RobinTask();
		~RobinTask();
		void start();
		void stop();
		void loop();
		void add_event(Event*);
	private:
		bool _running;
		thread_ptr _threads;
		std::deque<Event*> _events;
		std::condition_variable _cond;
		std::mutex _mutex;
	};

	class RobinThreadPoll
	{
	public:
		RobinThreadPoll(int num);
		~RobinThreadPoll();

		RobinTask* get_next_task();
		
		void start();
		void stop();
	private:
		int _round_index;
		int _thread_count;
		bool _running;
	};
}


#endif

