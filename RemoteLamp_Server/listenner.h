//
// Created by thari on 09/04/2020.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include<strings.h>
#include<unistd.h>

#ifdef debugOutput
    #include <iostream>
#endif

class listenner {
private:
    int listenSock, connSock;     //init file descriptors for sockets
    int clilen, n;        //init some variables

    struct sockaddr_in serv_addr, cli_addr;

public:
    listenner(int port);
    int acceptNewClient();
    int stopListening();
};