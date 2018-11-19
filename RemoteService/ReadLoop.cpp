#include "ReadLoop.h"
#include <algorithm>
#include <string.h>
#include <unistd.h>

CReadLoop::CReadLoop() : _bRunning(false), _max_fd(0)
{
	FD_ZERO(&_client_fdset); 
	FD_ZERO(&_client_fdset_copy);
}


CReadLoop::~CReadLoop()
{
}

void CReadLoop::Start()
{
	_bRunning = true;
	while (_bRunning){
		_client_fdset_copy = _client_fdset;
		//如果ret大于0表示返回就绪的描述的个数
		int ret = select(_max_fd + 1, &_client_fdset_copy, NULL, NULL, NULL);
		if (ret < 0) {
			printf("error\n");
		}
		else if (ret == 0) {
			printf("timeout\n");
		}
		else {
			for (auto j = 0; j < _fd_set.size(); ++j) {
				int fd = _fd_set.at(j);
				if (FD_ISSET(fd, &_client_fdset_copy)) {
					HandleRecv(fd, j);
				}
			}
		}
	}
}

void CReadLoop::Stop()
{
	_bRunning = false;
}

void CReadLoop::AddFD(int fd)
{
	_fd_set.emplace_back(fd);
}

void CReadLoop::RemoveFD(int fd)
{
	std::remove(_fd_set.begin(), _fd_set.end(), fd);
}


void CReadLoop::HandleRecv(int fd, int pos)
{
	const static int chunck_size = 512;

	std::string data;
	data.reserve(256);
	char buf[chunck_size] = { 0 };

	printf("handle_recv\n");
	while (1) {
		memset(buf, 0, sizeof(buf));
		int ret = ::read(fd, buf, sizeof(buf));
		if (ret == -1) {
			int err = errno;
			if (err == EINTR) {
				continue;
			}

			break;
		}
		if (0 == ret) {
			printf("closed by client");
			FD_CLR(fd, &_client_fdset);
			::close(fd);
			_fd_set[pos] = -1;
		}
		else {
			data += buf;
		}

	}
	if (!data.empty())
		printf("%s\n", data.c_str());

}