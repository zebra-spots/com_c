#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define BACKLOGCONNECTIONS 5

int main() 
{
        /* Variables */
        char readbuffer[50];
        // Struct for server and client
        struct sockaddr_in srv, cln; 
        int sockfd, bnd, accept_sockfd;

        /* Define socket */
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        /* Socket error handling */
        if(sockfd == -1) 
        {
        printf("error in socket creation\n");
        return 0;
        }
        printf("socket created successfully\n");

        /* Assigning address and port to struct */
        srv.sin_family = AF_INET;
        srv.sin_addr.s_addr = inet_addr("0.0.0.0");
        srv.sin_port = htons(1668);

        /* Define bind */
        bnd = bind(sockfd, (struct sockaddr*)&srv, sizeof(srv));

        /* Bind error handling */
        if (bnd == 0) 
        {
        printf("Bind successful");
        }
        else 
        {
        printf("Bind failed");
        return 0;
        }

        /* Define listen */
        int lstn = listen(sockfd, BACKLOGCONNECTIONS);
        int lenaddr = sizeof(cln);

        /* Define accept */
        accept_sockfd = accept(sockfd, (struct sockaddr*)&srv, &lenaddr);
        //printf("%d", accept_sockfd);


        /* Accept error handling */
        if (accept_sockfd == -1) 
        {
        printf("Error in accept\n");
        return 0;
        }

        printf("new connection is established successfully\n");
        while(1)
        {
        printf("wainting for data from client\n");
        memset(readbuffer,0x00,sizeof(readbuffer));
        read(accept_sockfd,readbuffer,sizeof(readbuffer));
        printf("Data from client =%s\n",readbuffer);
        }
}