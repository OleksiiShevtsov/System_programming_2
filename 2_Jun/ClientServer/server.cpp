#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

HANDLE client = INVALID_HANDLE_VALUE;
HANDLE server = INVALID_HANDLE_VALUE;

struct User{
	User(string login){
		this->login = login;
		activUser = false;
	}
	string login;
	bool activUser;
};

int main() {

	server = CreateEventA(0, FALSE, FALSE, "EventServer");
	client = OpenEventA(EVENT_MODIFY_STATE, TRUE, "EventClient");

	vector<User> dataBaseLogin;
	ifstream finDataBaseLogin;
	
	finDataBaseLogin.open("dataBaseLogin.txt");
	
	if(finDataBaseLogin.is_open()){
		
		cout <<"dataBaseLogin is open"<< endl;
		
		string dataLoginStr;
		
		do{
			
			getline(finDataBaseLogin, dataLoginStr);
			User user(dataLoginStr);
			dataBaseLogin.push_back(user);
		
		}while(dataLoginStr != "");
	
		finDataBaseLogin.close();
	}
	else{
		cout <<"the dataBaseLogin did not open"<< endl;
	}	
	
	vector<string> activeClient;
	
	string login;
	
	for(;;){
		
		WaitForSingleObject(server, INFINITE);
		
		ifstream fin;
		fin.open("data.txt");
		if(fin.is_open()){
			
			cout <<"file is open"<< endl;
			
			getline(fin, login);
			fin.close();
			
			fstream clear_file("data.txt", ios::out);
			clear_file.close();		

			if(login == "exit"){
				break;
			}	
			
			string sendToClient = "invalid login";
			for(int i = 0; i < dataBaseLogin.size(); i++){
				if(login == dataBaseLogin[i].login){
					dataBaseLogin[i].activUser = true;
					sendToClient = "active";
				}
			}
			
			ofstream fout;
			fout.open("data.txt", ofstream::app);
			fout << sendToClient;
			fout.close();
			
			cout << login <<": "<< sendToClient << endl;
			
			SetEvent(client);
		}
		else{
			cout <<"the file did not open"<< endl;
		}
		cout << endl;
	};
		

	cout << "EXIT SERVER" << endl;
	int exit; cin >> exit;
	
	return 0;
}
