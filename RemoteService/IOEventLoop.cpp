#include "IOEventLoop.h"
#include "EPoller.h"
#include <string.h>

CIOEventLoop::CIOEventLoop() : _bRunning(false)
{
}


CIOEventLoop::~CIOEventLoop()
{
}

void CIOEventLoop::SetPoller(std::shared_ptr<EPoller> pollerPtr)
{
	_pollerPtr = pollerPtr;
}

void CIOEventLoop::Loop()
{
	if(!_pollerPtr){
		return;
	}
	if (!_bRunning) {
		_bRunning = true;
		_threadPtr = std::make_shared<std::thread>([&]() {
			_pollerPtr->Wait();
		});
	}
}

void CIOEventLoop::Start()
{
	Loop();
}

void CIOEventLoop::Stop()
{
	_bRunning = false;
	if (_threadPtr->joinable())
		_threadPtr->join();
}



void CIOEventLoop::HandleRecv(int fd, int pos)
{
	/*const static int chunck_size = 512;

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

			::close(fd);

		}
		else {
			data += buf;
		}

	}
	if (!data.empty())
		printf("%s\n", data.c_str());*/

}