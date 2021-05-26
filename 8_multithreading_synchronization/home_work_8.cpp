 #include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <map>

using namespace std;

CRITICAL_SECTION criticalSection;

class Gamble;

DWORD WINAPI ThreadStart(void* param) {
		
	EnterCriticalSection(&criticalSection);	
	
	Gamble* gamble = static_cast<Gamble*>(param);	
		
	cout << gamble->m_dataPrediction.predictionsValue << endl;
	//cout << gamble->name << endl;
	
	

	LeaveCriticalSection(&criticalSection);
		
	return 0;
}

class Gamble{

public:
	Gamble(){
		srand(static_cast<unsigned int>(time(0)));
		m_hiddenNumber = rand() % 100 + 1;
	}
	
	void MakePrediction(char* userName, int prediction){
		
		m_dataPrediction.predictionsValue = prediction;
		m_dataPrediction.name = userName;
		
		HANDLE thread = CreateThread(0, 0, ThreadStart, this, 0, 0);
	}
	
	struct DataPrediction{
		int predictionsValue;
		char* name;
	} m_dataPrediction;
	
	void setPredictions(char* userName, int prediction){
		m_predictions.insert( std::pair<char*, int>(userName, prediction) );
	}
	
private:
	
	std::map<std::string, int> m_predictions;
	
	int m_hiddenNumber; 
};

int main() {
	
	InitializeCriticalSection(&criticalSection);
	
	Gamble gamble;
	gamble.MakePrediction("Alex", 12);


	
	Sleep(2000);
	DeleteCriticalSection(&criticalSection);
	
	return 0;
}
