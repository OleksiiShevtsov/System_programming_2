#include <iostream>
#include <windows.h>
#include <vector>

using namespace std;
/*	Semaphore: * CLIENT -----> SERVER */

HANDLE semaphore = INVALID_HANDLE_VALUE;
vector<int> data;

DWORD WINAPI ThreadClient(LPVOID param) {	
	 	
	WaitForSingleObject(semaphore, INFINITE);
	
	cout << data[0] << endl;
	cout << "EXIT ThreadClient" << endl;
	
	return 0;
}

DWORD WINAPI ThreadServer(LPVOID param) {
	
	LONG prevVal = 0;
		
	data.push_back(100);
	ReleaseSemaphore(semaphore, 4, &prevVal);
	
	cout << "EXIT ThreadServer" << endl;
	
	while(true){};
	
	return 0;
}


int main() {
	
	semaphore = CreateSemaphore(0, 4, 4, "semaphore");//Semaphore
	
	CreateThread(0, 0, ThreadServer, 0, 0, 0);
	
	for(int i = 0; i < 20; i++){
		CreateThread(0, 0, ThreadClient, 0, 0, 0);
	}
	
	Sleep(2000);

	cout << "EXIT main" << endl;

	return 0;
}
