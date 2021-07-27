#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <chrono>
#include <thread>

int main() {

    char* argv[4] = {"", "-la", "/", 0};

    int pid = fork();

    // child
    if ( pid == 0 ) {

        //std::cout << "I'm child" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
        //execv( "/bin/ls", argv );

        return 0;
    }

    std::cout << "I'm parent";

    std::this_thread::sleep_for(std::chrono::seconds(100));

    return 0;
}
