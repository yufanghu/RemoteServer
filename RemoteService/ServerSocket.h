#ifndef _SERVER_SOCKET_H
#define _SERVER_SOCKET_H
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
class CServerSocket {
public:
	enum {
		FD_MAX_SIZE = 1024,
		CHUNCK_SIZE = 512
	};
	CServerSocket(int port);
	~CServerSocket();
	void init_socket();
	void run_server();
	void stop_server();
private:
	void run_loop();
private:
	int _max_fd;
	int _sockfd;
	int _port;
	bool _running;
	std::shared_ptr<std::thread> _thread_ptr;
	//所有fd的集合
	std::unordered_set<int> _fdset;
};

#endif