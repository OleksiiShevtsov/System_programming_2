#include <iostream>
#include <windows.h>

using namespace std;

HANDLE eventServer = INVALID_HANDLE_VALUE;
HANDLE eventClient = INVALID_HANDLE_VALUE;

std::string text;

DWORD WINAPI ThreadServer(LPVOID param) {
	
	cout << "client: wait data..." << endl;
	
	SetEvent(eventClient);
	
	WaitForSingleObject(eventServer, INFINITE);

	cout << text << endl;
	
	return 0; 
}

DWORD WINAPI ThreadClient(LPVOID param) {

	WaitForSingleObject(eventClient, INFINITE);
	
	cout << "server: ready to give data..." << endl;
	
	text = "hello!!!";
	
	SetEvent(eventServer);
	
	return 0; 
}

int main() {

	eventServer = CreateEventA(0, false, false, "eventServer");
	eventClient = CreateEventA(0, false, false, "eventClient");

	HANDLE server = CreateThread(0, 0, ThreadServer, 0, 0, 0);
	HANDLE client = CreateThread(0, 0, ThreadClient, 0, 0, 0);
	
 	Sleep(1000);

	return 0;
}
