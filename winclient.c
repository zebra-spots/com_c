#include <stdio.h>
#include <winsock2.h>

#pragma comment (lib, "ws2_32.lib")

int main()
{
	WSDATA WSAData;
	SOCKET serverSocket;
	SOCKADDR_IN addr;

	WSAStartup(MAKEWORD(2,0), &WSAData);
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	addr.sin_family = AF_INET;
    	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    	addr.sin_port = htons(1968);

	connect(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
	printf("Connected to server!");
	
	closesocket(serverSocket);
	WSACleanup();
	printf("socket closed");
}
