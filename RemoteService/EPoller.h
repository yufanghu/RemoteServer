#pragma once
#include <memory>
#include <sys/epoll.h>
#include "Uncopyable.hpp"

enum EPollState{
	EAdd, EModify, EDel
};
enum EPollMode {
	ELT, EFT,
};

class CIO;
class EPoller : private Uncopyable
{
public:
	EPoller();

	virtual ~EPoller();

	virtual void Wait() = 0;

	void Update(int fd, EPollState state);

protected:

	enum {
		EPOLL_SIZE = 256,
	};

	void InitCreate(int size = EPOLL_SIZE);

protected:
	std::shared_ptr<CIO> _ioPtr;
	int _epollfd;
};

