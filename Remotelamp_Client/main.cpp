//normal usual boring old includes
#include "serverCon.h"
#include <iostream>

#define bufflen 512
#define servPort "30000"

char buffer[bufflen];

int main() {
    std::cout << "Hello, World!" << std::endl;
    serverCon server;
    server.connectTo("192.168.1.7", servPort);

    server.readData(buffer);
    if((buffer[0]!='h')&&(buffer[1]!='i')){
        std::cout<<"Wrong server"<<std::endl;
        server.cleanUp();
        return 1;
    }
    server.sendData("yo");

    std::cout<<"Type in any character and press ENTER to light lamp when your turn comes: "<<std::endl;
    int y;
    std::cin>>y;

    server.sendData("lf");
    server.readData(buffer);
    if ((buffer[0]=='f')&&(buffer[1]=='l')){
        std::cout<<"Light failed.";
        exit(0);
        server.cleanUp();
    }
    else if ((buffer[0]!='f')&&(buffer[1]!='l')){
        std::cout<<"Light Success!"<<std::endl;
    }

    server.cleanUp();
    std::cout<<"Done! Have a prosperous Sinhala and Tamil new year!";

    return 0;
}
