#include <cstdio>
#include "ServerSocket.h"
#include "EpollServer.h"
int main()
{
    printf("hello from RemoteService!\n");
	/*CServerSocket server(8889);
	server.init_socket();
	server.run_server();*/

	CEpollServer server(8888);
	server.Startup();

	system("pause");

    return 0;
}