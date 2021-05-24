#include <iostream>
#include <windows.h>

using namespace std;

HANDLE mutex = INVALID_HANDLE_VALUE;

DWORD WINAPI ThreadStart(LPVOID param) {

	WaitForSingleObject(mutex, INFINITE);

	for(int i = 0; i < 5; i++){
		cout << "dword" << endl;
	}
	
	cout << "_-_-_-_-_" << endl;
	
	ReleaseMutex(mutex);
	
	return 0; 
}

int main() {

	mutex = CreateMutexA(0, false, "Mutex");
	
	HANDLE thread[2] = {};
	thread[0] = CreateThread(0, 0, ThreadStart, 0, 0, 0);
	thread[1] = CreateThread(0, 0, ThreadStart, 0, 0, 0);
	
 	WaitForMultipleObjects(std::size(thread), thread, TRUE, INFINITE);
	
	for(int i = 0; i < 10; i++){
		cout << "main" << endl;
	}

	return 0;
}
