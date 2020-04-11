
//
// Created by thari on 4/4/2020.
//

//#define debugOutput

#define _WIN32_WINNT 0x501

#include <winsock2.h>
#include <ws2tcpip.h>

#ifdef debugOutput
#include <iostream>
#endif

#ifndef bufflen
#define bufflen 512
#endif

class serverCon {
private:
    WSADATA wsaData;
    int iResult;
    struct addrinfo *server_addrInfo = NULL, *ptr = NULL, clientInfo;
    SOCKET serverConnection = INVALID_SOCKET;

public:
    int connectTo(char address[128], char port[8]);
    int sendData(char data[bufflen]);
    int readData(char buff[bufflen]);
    int cleanUp();

};