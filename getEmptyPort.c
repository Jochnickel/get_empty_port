#include <errno.h> // errno
#include <unistd.h> // sleep
#include <strings.h> // bzero
#include <error.h> // error
#include <stdio.h> // puts printf
#include <arpa/inet.h> //sockaddr_in, INADDR_ANY, htons, ntohs

#define PORT 0

int main() {

        /* create a socket */
        int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
        if (socket_desc<0)
                error(/*exit code = */-1,/*stderr:*/ 9 /*== Bad file descriptor*/,"Could not create socket");

        /* bind the socket */
        struct sockaddr_in server;
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons( PORT );

        if ( bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0 )
                error(-1,errno,"bind failed");

        /* get the port number */
        struct sockaddr_in my_addr;             bzero(&my_addr, sizeof(my_addr));
        int len = sizeof(my_addr);
        getsockname(socket_desc, (struct sockaddr *) &my_addr, &len);

        unsigned int port = ntohs(my_addr.sin_port);

        listen(socket_desc , 3);
        printf("Open port : %u\n", port); sleep(5);

        close(socket_desc);
        puts("port closed"); sleep(10);

        return port;
}
