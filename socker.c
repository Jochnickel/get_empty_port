  GNU nano 2.9.8                                               c.c                                                          
#include <strings.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>  //inet_addr

#define PORT 0

int main()
{
        int new_socket , c;
        struct sockaddr_in server , client;

        int socket_desc = socket(AF_INET , SOCK_STREAM , 0);

        if (socket_desc == -1) puts("Could not create socket");

        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( PORT );

        if (bind(socket_desc,(struct sockaddr *)&server , sizeof(server))) puts("bind failed");

        struct sockaddr_in my_addr;
        bzero(&my_addr, sizeof(my_addr));
        int len = sizeof(my_addr);
        getsockname(socket_desc, (struct sockaddr *) &my_addr, &len);
        unsigned int myPort = ntohs(my_addr.sin_port);
        printf("Local port : %u\n", myPort);
        return 0;
}

