#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    int listenfd = 0;
    sockaddr_in serv_addr = {};

    listenfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);//127.0.0.1 lockalhost
    serv_addr.sin_port = htons(5000);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    listen(listenfd, 10);

    std::cout << "start: sever..." << std::endl;
    while(1){
        int connfd = accept(listenfd, nullptr, NULL);

        time_t ticks = time(NULL);
        std::string outBuf = "Hi there!!!";
        write(connfd, outBuf.data(), outBuf.size());
        close(connfd);
        sleep(1);
    }
}
