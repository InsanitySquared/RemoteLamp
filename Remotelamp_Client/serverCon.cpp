//
// Created by thari on 4/4/2020.
//

#include "serverCon.h"

int serverCon::connectTo(char *address, char *port) {

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
#ifdef debugOutput
        std::cout << "Could not start WSAthingy" << std::endl;
#endif
        return -1;
    }

#ifdef debugOutput
    std::cout << "Started WSA thingy" << std::endl;
#endif

    ZeroMemory(&clientInfo, sizeof(clientInfo));
    clientInfo.ai_family = AF_INET;
    clientInfo.ai_socktype = SOCK_STREAM;
    clientInfo.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(address, port, &clientInfo, &server_addrInfo);
    if (iResult != 0) {
#ifdef debugOutput
        std::cout << "Could not resolve server address." << std::endl;
#endif
        WSACleanup();
        return -2;
    } else {
#ifdef debugOutput
        std::cout << "Successfully resolved server!" << std::endl;
#endif
    }

    ptr = server_addrInfo;
    serverConnection = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
    if (serverConnection == INVALID_SOCKET) {
#ifdef debugOutput
        std::cout << "Could not create socket." << std::endl;
#endif
        freeaddrinfo(server_addrInfo);
        WSACleanup();
        return -3;
    } else {
#ifdef debugOutput
        std::cout << "Successfully created socket!" << std::endl;
#endif
    }


    // connect-----------------------------------------------

    iResult = connect(serverConnection, ptr->ai_addr, (int) ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        closesocket(serverConnection);
        serverConnection = INVALID_SOCKET;
    }
    //TODO-
    // Should really try the next address returned by getaddrinfo
    // if the connect call failed
    // But for this simple example we just free the resources
    // returned by getaddrinfo and print an error message

    freeaddrinfo(server_addrInfo);

    if (serverConnection == INVALID_SOCKET) {
#ifdef debugOutput
        std::cout << "Could not connect to server" << std::endl;
#endif
        WSACleanup();
        return -4;
    } else {
#ifdef debugOutput
        std::cout << "Successfully connected to server!" << std::endl;
#endif
    }

    return 1;
}

int serverCon::sendData(char *data) {

    iResult = send(serverConnection, data, (int) strlen(data), 0);
    if (iResult == SOCKET_ERROR) {
#ifdef debugOutput
        std::cout<<"Send error"<<std::endl;
#endif
        closesocket(serverConnection);
        WSACleanup();
        return -1;
    }

    return 1;
}

int serverCon::readData(char *buff) {

    iResult = recv(serverConnection, buff, (bufflen-1), 0);
    if (iResult < 0){
#ifdef debugOutput
        std::cout<<"read failed."<<std::endl;
#endif
        return -1;
    }

    return iResult;
}

int serverCon::cleanUp() {

    iResult = shutdown(serverConnection, SD_SEND);
    if (iResult == SOCKET_ERROR) {
#ifdef debugOutput
        std::cout << "Could not close socktet... hmmm" << std::endl;
#endif
        closesocket(serverConnection);
        WSACleanup();
        return -1;
    }

    closesocket(serverConnection);
    WSACleanup();

#ifdef debugOutput
    std::cout << "Closed and done!" << std::endl;
#endif

    return 1;
}