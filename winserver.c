#include <stdio.h>
#include <winsock2.h>
#define BACKLOGCONNECTIONS 5

#pragma comment (lib, "ws2_32.lib")

int main()
{
    /* Defining socket variables */
    WSADATA WSAData;
    SOCKET serverSocket;
    SOCKADDR_IN addr, cln;
    char readbuffer[256];
    int bnd, accept_serverSocket, read_received, send_success;
    
    /* Defining socket */
    WSAStartup(MAKEWORD(2,0), &WSAData);;
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	/* Socket error handling */
	if(serverSocket == -1) 
	{
	printf("error in socket creation\n");
	return 0;
	}
	printf("socket created successfully\n");

    /* Make socket reusable */
	int val = 1;
	int result = 0;
	result = setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));	

    /* Assigning address and port no to addr */
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1968);

    /* Define bind */
    bnd = bind(serverSocket, (SOCKADDR*)&addr, sizeof(addr));

    /* Bind error handling */
	if (bnd == 0) 
	{
	printf("Bind successful\n");
	}
	else 
	{
	printf("Bind failed\n");
	return 0;
	}

    /* Define listen */
	int lstn = listen(serverSocket, BACKLOGCONNECTIONS);
	int lenaddr = sizeof(cln);

    /* Define accept */
	accept_serverSocket = accept(serverSocket, (SOCKADDR*)&addr, &lenaddr);

    /* Accept error handling  */
    if (accept_serverSocket == -1) 
	{
	printf("Error in accept\n");
	return 0;
	}
	
	printf("new connection is established successfully\n");

	while(1)
	{
	printf("Waiting for data from client\n");
	memset(readbuffer,0x00,sizeof(readbuffer));
	char recv_success[10] = "Received!";
	read_received = read(accept_serverSocket, readbuffer, sizeof(readbuffer));
	printf("Data from client =%s\n",readbuffer);
	if (read_received > 0) 
	{
		send_success = send(accept_serverSocket, recv_success, sizeof(recv_success), 0);
		if (send_success == -1)
		{
			printf("Send success error");
			continue;
		}

    /* Define connect, from template code
    connect(serverSocket, (SOCKADDR*)&addr, sizeof(addr));
    printf("Connected to server!");
    */

    /* Close socket */
    closesocket(serverSocket);
    WSACleanup();
    printf("Socket closed");
    }
    }
}
