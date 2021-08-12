#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <iostream>

int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024] = {};
    sockaddr_in serv_addr = {};

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        std::cout << "Error : Could not create socket \n";
        return 0;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0){
        std::cout << "inet_pton error occured \n";
        return 1;
    }

    if( connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr))){
        std::cout << "Error : Connect Failed \n";
        return 1;
    }
    else{
        std::cout << "Connect to server ...\n";
    }

    while((n = read(sockfd, recvBuff, sizeof(recvBuff) - 1)) > 0){
        recvBuff[n] = 0;
        std::cout << recvBuff;
    }

    if(n < 0){
        std::cout << "Read error \n";
    }

    return 0;
}            
