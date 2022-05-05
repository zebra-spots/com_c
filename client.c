#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>

int main(int argc, char *argv[]) 
{
    int simpleSocket = 0;
    int simplePort = 0;
    int returnStatus = 0;
    char buffer[256] = "";
    struct sockaddr_in simpleStruct;

    if (argc != 3) 
    {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }

    /* create a streaming socket      */
    simpleSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (simpleSocket == -1) 
    {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else 
    {
        fprintf(stderr, "Socket created!\n");
    }

    /* retrieve the port number for connecting */
    simplePort = atoi(argv[2]);

    /* setup the address structure */
    /* use the IP address sent as an argument for the server address  */
    bzero(&simpleStruct, sizeof(simpleStruct)); 
    simpleStruct.sin_family = AF_INET;
    inet_addr(argv[2], &simpleStruct.sin_addr.s_addr);
    simpleStruct.sin_port = htons(simplePort);

    /*  connect to the address and port with our socket  */
    returnStatus = connect(simpleSocket, (struct sockaddr *)&simpleStruct, sizeof(simpleStruct));
    

    if (returnStatus == 0) 
    {
        fprintf(stderr, "Connect successful!\n");

            while(1)
            {

            /* Define send */
            //char client_request[] = "GET OFF MY BOX\n";
            //int message_send = send(simpleSocket, client_request, sizeof(client_request), 0);
            char message[256] = "";
            scanf("%s\n", message);
            int message_send_two = send(simpleSocket, message, sizeof(message), 0);
            
            /* Define read */
            char buffer[256] = "";
            int var = read(simpleSocket, buffer, sizeof(buffer));
            puts(buffer);
            
            /* Define recv */ 
            /*
            char server_resp[256] = "";
            int message_recv = recv(simpleSocket, server_resp, sizeof(server_resp), 0);
            puts(server_resp);
            //message_send = send(simpleSocket, client_request, sizeof(client_request), 0);
            */
            }

    }
    else 
    {
        fprintf(stderr, "Could not connect to address!\n");
        close(simpleSocket);
        exit(1);
    }

}
