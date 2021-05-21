#include <iostream>
#include <windows.h>

using namespace std;


DWORD WINAPI ThreadStart(LPVOID param) {
	
	for (int i = 0; i < 10; i++) {
		cout << "DWORD: " << i << endl;
	}
	return 0;
}

int main() {

	HANDLE thread = CreateThread(0, 0, ThreadStart, 0, 0, 0);
	WaitForSingleObject(thread, INFINITE);

	return 0;
}
