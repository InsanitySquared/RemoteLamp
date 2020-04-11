//
// Created by thari on 09/04/2020.
//

#include "listenner.h"

listenner::listenner(int port) {

    listenSock = socket(AF_INET, SOCK_STREAM, 0);     //create the listening socket and add FD to FD table
    if (listenSock < 0){
    #ifdef debugOutput
        std::cout<<"Error creating Listening socket"<<std::endl;
    #endif
        //TODO-have to handle these errors
    }
    else{
    #ifdef debugOutput
        std::cout<<"Successfuly created listening socket!"<<std::endl;
    #endif
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));      //zero serv_addr

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(listenSock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){       //bind listenenr to adrress
    #ifdef debugOutput
        std::cout<<"Listenner bind failed"<<std::endl;
    #endif
    }
    else{
    #ifdef debugOutput
        std::cout<<"Listenner successfully bound!"<<std::endl;
    #endif
    }

    listen(listenSock, 10);          //listen for connections
}

int listenner::acceptNewClient() {

    clilen = sizeof(cli_addr);
    int connSock = accept(listenSock, (struct sockaddr *) &cli_addr, (socklen_t*)&clilen);
    if (connSock<0){
    #ifdef debugOutput
        std::cout<<"Error on accepting client and creating new socket"<<std::endl;
    #endif
        return -1;
    }
    else{
    #ifdef debugOutput
        std::cout<<"Client connection successful!"<<std::endl;
    #endif
    }

    return connSock;
}

int listenner::stopListening() {
    close(listenSock);
    return 1;
}
