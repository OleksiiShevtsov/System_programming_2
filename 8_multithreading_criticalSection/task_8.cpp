#include <iostream>
#include <windows.h>

using namespace std;

/*	критическая секция: */

LONG count = 0;
CRITICAL_SECTION criticalSection;

DWORD WINAPI ThreadStart(LPVOID param) {

	EnterCriticalSection(&criticalSection);
	++count;
	cout << "dword count: " << count << endl;
	LeaveCriticalSection(&criticalSection);
	
	return 0; 
}

int main() {
	
	InitializeCriticalSection(&criticalSection);
	
	for(int i = 0; i < 100; i++){
		HANDLE thread1 = CreateThread(0, 0, ThreadStart, 0, 0, 0);
	}
	
	Sleep(1000);
	
	DeleteCriticalSection(&criticalSection);
	
	cout << "main count: " << count << endl;

	return 0;
}
