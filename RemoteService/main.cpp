#include <cstdio>
#include "ServerSocket.h"
int main()
{
    printf("hello from RemoteService!\n");
	CServerSocket server(8889);
	server.init_socket();
	server.run_server();

	system("pause");

    return 0;
}