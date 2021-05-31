#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string>
#include <map>

using namespace std;

CRITICAL_SECTION criticalSection;

DWORD WINAPI ThreadStart(void* param);

class Gamble;

struct DataPrediction {
	int predictionsValue = 0;
	std::string name = "";
	std::map<std::string, int>* p_predictions;
};

class Gamble {

public:

	/*void setPredictions(const char* userName, int prediction) {
		m_predictions.insert(std::pair<const char*, int>(userName, prediction));
	}*/

	Gamble() {
		srand(static_cast<unsigned int>(time(0)));
		m_hiddenNumber = rand() % 20 + 1;
		std::cout << "prediction: " << m_hiddenNumber << std::endl;
		m_dataPrediction.p_predictions = &m_predictions;
	}

	void MakePrediction(std::string userName, int prediction) {

		m_dataPrediction.predictionsValue = prediction;
		m_dataPrediction.name = userName;

		HANDLE thread = CreateThread(0, 0, ThreadStart, this, 0, 0);
	}

	void findAnAccuratePrediction() {

		std::map<std::string, int> bestPredictions;
		std::pair<std::string, int> bestPrediction;

		int temp = 0;

		for (auto iter = m_predictions.begin(); iter != m_predictions.end(); iter++) {
			if (iter == m_predictions.begin()) {
				temp = abs(m_hiddenNumber - iter->second);
				bestPrediction.first = iter->first;
				bestPrediction.second = iter->second;
				continue;
			}
			if (temp > abs(m_hiddenNumber - iter->second)) {
				temp = abs(m_hiddenNumber - iter->second);
				bestPrediction.first = iter->first;
				bestPrediction.second = iter->second;
			}
		}
		if (m_predictions.size() != 0) {
			bestPredictions.insert(bestPrediction);
		}
		for (auto iter = m_predictions.begin(); iter != m_predictions.end(); iter++) {
			if (iter->second == bestPrediction.second) {
				bestPredictions.insert(*iter);
			}
		}
		for (auto iter = bestPredictions.begin(); iter != bestPredictions.end(); iter++) {
			cout << "best prediction: " << iter->first << ": " << iter->second << endl;
		}
	}

	void allPredictions() {
		for (auto iter = m_predictions.begin(); iter != m_predictions.end(); iter++) {
			cout << "all prediction: " << iter->first << ": " << iter->second << std::endl;
		}
	}
	
	DataPrediction m_dataPrediction;

private:

	std::map<std::string, int> m_predictions;
	int m_hiddenNumber;
};

DWORD WINAPI ThreadStart(void* param) {
	EnterCriticalSection(&criticalSection);
		
	    //DataPrediction* dataPrediction = static_cast<DataPrediction*>(param);
		Gamble* gamble = static_cast<Gamble*>(param);
		int value = gamble->m_dataPrediction.predictionsValue;
		std::string name = gamble->m_dataPrediction.name;
		gamble->m_dataPrediction.p_predictions->insert(std::pair<std::string, int>(name, value));

	LeaveCriticalSection(&criticalSection);

	return 0;
}

int main() {

	InitializeCriticalSection(&criticalSection);
	Gamble gamble;
	std::chrono::seconds waitingTime(2s);
	std::string strName;
	int prediction = 0;

	/*auto start = chrono::high_resolution_clock::now();
	while ( true ) {
		auto end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			std::cout << "Enter name: ";
		
			//std::cin >> strName;
			strName = "Alex";
			
			std::cout << "Enter prediction: ";
			prediction = prediction + 1;
			//std::cin >> prediction;
		
		gamble.MakePrediction(strName.c_str(), prediction);
	}*/

	gamble.MakePrediction("Alex1", prediction++);
	Sleep(100);
	gamble.MakePrediction("Alex1", prediction++);
	Sleep(100);
	gamble.MakePrediction("Alex1", prediction++);
	Sleep(100);
	gamble.MakePrediction("Alex1", prediction++);
	Sleep(100);

	gamble.findAnAccuratePrediction();
	gamble.allPredictions();

	DeleteCriticalSection(&criticalSection);

	return 0;
}