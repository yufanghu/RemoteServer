#pragma once
#include "IOEventLoop.h"
#include <memory>
#include <thread>
#include <vector>

class CReadLoop : public CIOEventLoop
{
public:
	enum {
		FD_MAX_SIZE = 1024
	};
	CReadLoop();
	~CReadLoop();
	
	virtual void Start() override;
	
	virtual void Stop() override;

	void AddFD(int fd);

	void RemoveFD(int fd);

private:
	void HandleRecv(int fd, int pos);

private:
	std::vector<int> _fd_set;
	fd_set _client_fdset;
	fd_set _client_fdset_copy;
	bool _bRunning;
	int _max_fd;
};

