#include <stdio.h>      
#include <sys/types.h>
#include <sys/socket.h>   
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXBUF 1024

int main(int argc, char* argv[])
{
/* Declare Variables */
    int udpSocket;
    int returnStatus;
    int addrlen;
    struct sockaddr_in udpClient, udpServer;
    char buf[MAXBUF];
/* Argc error handling */
    if (argc != 3) 
    {
        fprintf(stderr, "Usage: %s <server> <port>\n", argv[0]);
        exit(1);
    }
/* Create Socket */
    udpSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpSocket == -1) 
    {
        fprintf(stderr, "Could not create a socket!\n");
        exit(1);
    }
    else 
    {
	fprintf(stderr, "Socket created!\n");
    }
/* Client address */
    udpClient.sin_family = AF_INET;
    udpClient.sin_addr.s_addr = INADDR_ANY;
    udpClient.sin_port = 0;
/* Bind */
    returnStatus = bind(udpSocket, (struct sockaddr*)&udpClient, sizeof(udpClient));

    if (returnStatus == 0) 
    {
        fprintf(stderr, "Bind completed!\n");
    }
    else 
    {
        fprintf(stderr, "Could not bind to address!\n");
        close(udpSocket);
        exit(1);
    }
/* Define Sendto */
    strcpy(buf, "I love doing assembly stuff.\n");
    /* server address */ 
    /* use the command line arguments */
    udpServer.sin_family = AF_INET;
    udpServer.sin_addr.s_addr = inet_addr(argv[1]);
    udpServer.sin_port = htons(atoi(argv[2]));
    
    addrlen = sizeof(udpServer);
    printf("%d \n", strlen(buf));
    printf("%d \n", addrlen);

    returnStatus = sendto(udpSocket, buf, (strlen(buf)+1), 0, (struct sockaddr *)&udpServer, addrlen);
    //sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

    if (returnStatus == -1) 
    {
        fprintf(stderr, "Could not send message!\n");
    }
    else 
    {

        printf("Message sent.\n");

        /* message sent: look for confirmation */
        
    }

/* Define Recvfrom */
        returnStatus = recvfrom(udpSocket, buf, sizeof(buf), 0, (struct sockaddr *)&udpClient, &addrlen);
        //recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
        
        if (returnStatus == -1) 
        {
            perror("Recieved from error:  \n"); 
            fprintf(stderr, "Did not receive confirmation!\n");
        }
        else 
        {

            buf[returnStatus] = 0;
            printf("Received: %s\n", buf);
        }

/* Define close */
    close(udpSocket);
    return 0;
}
