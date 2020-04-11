//
// Created by thari on 4/3/2020.
//

//#define debugOutput

#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include<strings.h>
#include<unistd.h>

#ifdef debugOutput
    #include <iostream>
#endif

#define bufflen 512

class ipConnection {
private:
    int connSock;     //init file descriptors for sockets
    int n;        //init some variables

public:
    ipConnection(int fd);
    int cleanUp();
    int sendData(char buff[bufflen]);
    int readData(char data[bufflen]);
    int dataAvailable();

};