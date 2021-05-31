#include <iostream>
#include <map>
#include <vector>
#include <windows.h>
#include <math.h>

HANDLE h = INVALID_HANDLE_VALUE;
std::vector<std::string> passwords;
int id = 0;
const int passwordsCount = 100;

struct Semaphore {
    int resourcesCount; // 0
    int maxRosources;   // 10
};
bool CheckPwd(std::string pwd) {
    return false;
}
DWORD WINAPI Client(LPVOID arg) {

    DWORD res = WaitForSingleObject(h, INFINITE);
    std::cout << "Client " << id++ << " received data\n";
    for (int j = 0; j < passwordsCount; ++j) {
        CheckPwd(passwords[j]);
    }
   // std::cout << data[0] << std::endl;
   // std::cout << "Client " << id << " finished\n";
    return 0;
}


DWORD WINAPI Server(LPVOID arg) {
    LONG prevVal = 0;
    passwords.resize(passwordsCount);
    for (int i = 0; i < 20; ++i) {
        Sleep(1000);
        for (int j = 0; j < passwordsCount; ++j) {
            passwords[j] = std::string("pwd");
        }
        std::cout << "Server prepared first data\n";
        ReleaseSemaphore(h, 1, &prevVal);
    }

    return 0;
}

int main() {
	
    h = CreateSemaphore(0, 0, 10, "ServerDataSync");
    CreateThread(0, 0, Server, 0, 0, 0);
    for (int i = 0; i < 20; ++i) {

        CreateThread(0, 0, Client, (LPVOID)i, 0, 0);

    }
    Sleep(1000000);
    std::cout << "";
    return 0;
}
