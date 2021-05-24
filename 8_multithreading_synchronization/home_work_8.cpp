#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

CRITICAL_SECTION criticalSection;

DWORD WINAPI ThreadStart(void* dataArrey) {
		
	static_cast<char*>(dataArrey);	
		
	cout << *(int*)dataArrey << endl;
	
		for(int i = sizeof(int); i < 6; i++){
			
			cout << *dataArrey + i << endl;
			
		}
		
	EnterCriticalSection(&criticalSection);
		
	LeaveCriticalSection(&criticalSection);
		
	return 0;
}

class Gamble{

public:
	Gamble(){
		srand(static_cast<unsigned int>(time(0)));
		m_hiddenNumber = rand() % 100 + 1;
		cout << m_hiddenNumber << endl;
	}
	
	void MakePrediction(std::string userName, int prediction){
		
		char dataArrey[sizeof(userName) + sizeof(prediction)];
		
		*(int*)dataArrey = prediction;
		
		for(int i = sizeof(prediction); i < sizeof(userName); i++){
			dataArrey[i] = userName[i - sizeof(prediction)];
		}
		
		HANDLE thread = CreateThread(0, 0, ThreadStart, dataArrey, 0, 0);
	}
	
private:
	std::map<std::string, int> m_prediction;
	int m_hiddenNumber; 
};

int main() {
	
	InitializeCriticalSection(&criticalSection);
	
	Gamble gamble;
	gamble.MakePrediction("Alex", 12);

	DeleteCriticalSection(&criticalSection);

	return 0;
}
