#ifndef GET_EMPTY_PORT_H
#define GET_EMPTY_PORT_H

#include <errno.h> // errno
#include <unistd.h> // sleep, close
#include <strings.h> // bzero
//#include <error.h> // error
#include <stdlib.h> // exit
//#include <stdio.h> // puts printf
#include <arpa/inet.h> //sockaddr_in, INADDR_ANY, htons, ntohs

#define PORT 0

int getEmptyPort() {

 /* create a socket */
 int socket_desc = socket(AF_INET , SOCK_STREAM , 0);
 if (socket_desc<0){
  errno = 9; /* Bad file descriptor */
  exit(-1);
  //error(/*exit code = */-1,/*stderr:*/ 9 /*== Bad file descriptor*/,"Could not create socket");
 }

 /* bind the socket */
 struct sockaddr_in server;
 server.sin_family = AF_INET;
 server.sin_addr.s_addr = INADDR_ANY;
 server.sin_port = htons( PORT );

 if ( bind(socket_desc,(struct sockaddr *)&server, sizeof(server)) < 0 )
  exit(-1);
  //error(-1,errno,"bind failed");

 /* get the port number */
 struct sockaddr_in my_addr; bzero(&my_addr, sizeof(my_addr));
 int len = sizeof(my_addr);
 getsockname(socket_desc, (struct sockaddr *) &my_addr, &len);

 unsigned int port = ntohs(my_addr.sin_port);

 listen(socket_desc , 3);
 //printf("%u", port);// sleep(5);

 close(socket_desc);
 //puts("port closed"); sleep(10);

 return port;
}

#endif
