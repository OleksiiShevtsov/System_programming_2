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
	const char* name = "";
	void(Gamble::*setPredictions)(const char* name, int predictionsValue);
};

class Gamble {

public:

	void setPredictions(const char* userName, int prediction) {
		m_predictions.insert(std::pair<const char*, int>(userName, prediction));
	}

	Gamble() {
		srand(static_cast<unsigned int>(time(0)));
		m_hiddenNumber = rand() % 20 + 1;
		std::cout << "prediction: " << m_hiddenNumber << std::endl;
		m_dataPrediction.setPredictions = setPredictions;
	}

	void MakePrediction(const char* userName, int prediction) {

		m_dataPrediction.predictionsValue = prediction;
		m_dataPrediction.name = userName;

		HANDLE thread = CreateThread(0, 0, ThreadStart, &m_dataPrediction, 0, 0);
	}

	void findAnAccuratePrediction() {

		std::map<const char*, int> bestPredictions;
		std::pair<const char*, int> bestPrediction;

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
			cout << endl;
		}
	}

	void allPredictions() {
		for (auto iter = m_predictions.begin(); iter != m_predictions.end(); iter++) {
			cout << "all prediction: " << iter->first << ": " << iter->second << std::endl;
		}
	}
	
	DataPrediction m_dataPrediction;

private:

	std::map<const char*, int> m_predictions;
	int m_hiddenNumber;
};

DWORD WINAPI ThreadStart(void* param) {
	EnterCriticalSection(&criticalSection);

	    DataPrediction* dataPrediction = static_cast<DataPrediction*>(param);
		int value = dataPrediction->predictionsValue;
		const char* name = dataPrediction->name;

	    dataPrediction->setPredictions(name, value);

	LeaveCriticalSection(&criticalSection);

	return 0;
}

int main() {

	InitializeCriticalSection(&criticalSection);
	Gamble gamble;
	std::chrono::seconds waitingTime(20s);
	std::string strName;
	int prediction;

	auto start = chrono::high_resolution_clock::now();
	while ( true ) {
		auto end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			std::cout << "Enter name: ";
	
		end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			std::cin >> strName;
		
		end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			std::cout << "Enter prediction: ";
		
		end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			std::cin >> prediction;

		end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
		
			gamble.MakePrediction(strName.c_str(), prediction);
		
		end = std::chrono::high_resolution_clock::now();
		if (std::chrono::duration_cast<std::chrono::seconds>(end - start) > waitingTime) { break; }
	}

	gamble.findAnAccuratePrediction();
	gamble.allPredictions();

	DeleteCriticalSection(&criticalSection);

	return 0;
}