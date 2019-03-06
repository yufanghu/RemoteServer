#include "ServerSocket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <signal.h>
#include <sys/select.h>
#include <sys/types.h>
#include <arpa/inet.h> 
#include <string.h>
#include <unistd.h>
#include<fcntl.h>

CServerSocket::CServerSocket(int port) : _sockfd(-1),
_running(false), _max_fd(0), _port(-1)
{
	this->_port = port;
}

CServerSocket::~CServerSocket()
{

}

void CServerSocket::run_server()
{
	_running = true;
	run_loop();
}
void CServerSocket::init_socket()
{
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (_sockfd < 0) {
		printf("socket create failed\n");
		exit(0);
	}

	int flag = 1;

	//SO_REUSEADDR 设置端口重用防止出现 服务器进程异常关闭该端口处于time_wait状态
	setsockopt(_sockfd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag));

	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (-1 == bind(_sockfd, (sockaddr*)&addr, sizeof(addr))) {
		printf("bind failed\n");
		exit(0);
	}

	if (-1 == listen(_sockfd, 10)) {
		printf("listen failed\n");
		exit(0);
	}
}

void CServerSocket::stop_server() 
{
	_running = false;
}

void CServerSocket::run_loop()
{
	auto func = [&]()->int {
		while (_running) {

		}
	};

	_thread_ptr = std::make_shared<std::thread>(func);

}