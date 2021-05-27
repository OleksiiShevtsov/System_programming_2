#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

HANDLE client = INVALID_HANDLE_VALUE;
HANDLE server = INVALID_HANDLE_VALUE;

int main() {

	client = CreateEventA(0, FALSE, FALSE, "EventClient");
	server = OpenEventA(EVENT_MODIFY_STATE, TRUE, "EventServer");
	
	server = CreateEventA(0, FALSE, FALSE, "EventServer");
	client = OpenEventA(EVENT_MODIFY_STATE, TRUE, "EventClient");
	
	string login;
	cout << "Enter login: ";
	cin >> login;
	
	ofstream fout;
	fout.open("data.txt", ofstream::app);
	fout << login;
	fout.close();

	SetEvent(server);
	
	WaitForSingleObject(client, INFINITE);
	
	//////////////////////////////////////////
	string status;
	ifstream fin;
	fin.open("data.txt");
	if(fin.is_open()){
		
		cout <<"file is open"<< endl;
		
		getline(fin, status);
		fin.close();
		
		cout << status << endl;
		
		fstream clear_file("data.txt", ios::out);
		clear_file.close();		
		
		cout << "clear" << endl;
	}
	else{
		cout <<"the file did not open"<< endl;
	}
	
	fstream clear_file("data.txt", ios::out);
	clear_file.close();
	
	
	cout << "Enter exit: ";
	int exit; cin >> login;
		
	return 0;
}
