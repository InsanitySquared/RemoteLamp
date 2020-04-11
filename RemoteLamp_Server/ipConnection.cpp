//
// Created by thari on 4/3/2020.
//

#include <cstring>
#include "ipConnection.h"


ipConnection::ipConnection(int fd){
    connSock=fd;
}

int ipConnection::sendData(char* buff){

    n = write(connSock,buff,std::strlen(buff));
    int y=0;
    while ((n < 0) && (y<6)){
        #ifdef debugOutput
            std::cout<<"Error writing to client, trying again"<<std::endl;
        #endif
        n = write(connSock,buff,strlen(buff));
        y=y+1;
    }
    if(y>5) {
        #ifdef debugOutput
            std::cout << "Write failed" << std::endl;
        #endif
        return -1;
    }
    return 0;
}

int ipConnection::readData(char *data) {

    bzero(data,bufflen);
    n = read(connSock,data,(bufflen-1));
    int y=0;
    while ((n < 0) && (y<6)){
        #ifdef debugOutput
            std::cout<<"Error reading from client, trying again"<<std::endl;
        #endif
        n = read(connSock,data,511);
        y=y+1;
    }
    if(y>5){
        #ifdef debugOutput
            std::cout<<"Read failed"<<std::endl;
        #endif
        return -1;
    }
    return 0;
}

int ipConnection::cleanUp() {
    #ifdef debugOutput
        std::cout << "Closing connections" << std::endl;
    #endif
    close(connSock);
    return 0;
}

int ipConnection::dataAvailable() {
    int count;
    ioctl(connSock, FIONREAD, &count);
    return count;
}
