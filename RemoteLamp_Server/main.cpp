#include <iostream>
#include <pthread.h>

#include "listenner.h"
#include "ipConnection.h"

#define cliPORT 30000
#define lamPort 30002
#define maxThreads 40

char buffer[bufflen];

int lampFD;

void *clientHandler(void *socFD){
    int cliFD;
    cliFD=*((int *) socFD);
    std::cout<<"New client!"<<std::endl;

    ipConnection client(cliFD);
    client.sendData("hi");
    client.readData(buffer);
    if ((buffer[0]!='y')&&(buffer[1]!='o')){
        std::cout<<"wrong client accept thing"<<std::endl;
        exit(0);
    }

    ipConnection lamp(lampFD);

    while(client.dataAvailable()<2){}

    client.readData(buffer);
    if((buffer[0]!='l')&&(buffer[1]!='f')){
        std::cout<<"wrong again";
        client.cleanUp();
        pthread_exit(NULL);
    }

    lamp.sendData(buffer);
    lamp.readData(buffer);
    client.sendData(buffer);
    if ((buffer[0]=='f')&&(buffer[1]=='l')){
        std::cout<<"Light failed.";
    }

    std::cout<<"One cleint done. May you have a prosperous new year!"<<std::endl;
    client.sendData("done");

    std::cout<<"Exiting thread..."<<std::endl;
    client.cleanUp();
    pthread_exit(NULL);
}

int main() {

    std::cout<<"Mornin! Waiting for lamp client"<<std::endl;

    listenner lampList(lamPort);

    lampFD=lampList.acceptNewClient();
    ipConnection lamp(lampFD);
    lamp.readData(buffer);
    if ((buffer[0]!='l')&&(buffer[1]!='p')){
        std::cout<<"wrong lamp client"<<std::endl;
    }
    lamp.sendData("ok");

    std::cout<<"Welcome to RemoteLamp. New session? (y/n): ";
    char inp;
    std::cin>>inp;
    if (inp!='y'){
        exit(0);
    }
    std::cout<<"Enter number of participants: ";
    int nPart;
    std::cin>>nPart;

    lamp.sendData("ns");
    lamp.readData(buffer);
    if ((buffer[0]!='n')&&(buffer[1]!='p')){
        std::cout<<"Wrong ack upon session creation"<<std::endl;
        lamp.cleanUp();
        exit(0);
    }
    std::cout<<"New session created"<<std::endl;
    char nPartc[5];
    sprintf(nPartc, "%d", nPart);
    lamp.sendData(nPartc);

    std::cout << "Starting listenner for clients" << std::endl;

    pthread_t cliThread[nPart];

    listenner listenner(cliPORT);

    bool stop=false;
    int threadNo=0;
    while((threadNo<=(nPart-1))&&(!stop)){

        int fD=listenner.acceptNewClient();
        std::cout<<"got new client, creating thread..."<<std::endl;

        int rc = pthread_create(&cliThread[threadNo], NULL, clientHandler, &fD);
        if (rc) {
            std::cout << "Error:unable to create thread," << rc << std::endl;
        }

        threadNo=threadNo+1;
    }
    std::cout << "Max clients reached, stopping listenner" << std::endl;
    listenner.stopListening();
    pthread_exit(NULL);
}
