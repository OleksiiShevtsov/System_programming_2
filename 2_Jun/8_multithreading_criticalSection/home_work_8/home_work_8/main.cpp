#include <iostream>
#include <string>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <cmath>

using namespace std;

CRITICAL_SECTION criticalSection;

DWORD WINAPI ThreadStart(void* param);

struct DataPrediction {
	int predictionsValue;
	const char* name;
};

class Gamble {

public:

	Gamble() {
		srand(static_cast<unsigned int>(time(0)));
		m_hiddenNumber = rand() % 20 + 1;
		std::cout << "prediction: " << m_hiddenNumber << std::endl;
	}

	void MakePrediction(const char* userName, int prediction) {

		m_dataPrediction.predictionsValue = prediction;
		m_dataPrediction.name = userName;

		HANDLE thread = CreateThread(0, 0, ThreadStart, this, 0, 0);
	}

	void setPredictions(const char* userName, int prediction) {
		m_predictions.insert(std::pair<const char*, int>(userName, prediction));
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
		bestPredictions.insert(bestPrediction);
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

		Gamble* gamble = static_cast<Gamble*>(param);
		int value = gamble->m_dataPrediction.predictionsValue;
		const char* name = gamble->m_dataPrediction.name;
		gamble->setPredictions(name, value);

	LeaveCriticalSection(&criticalSection);

	return 0;
}

int main() {

	InitializeCriticalSection(&criticalSection);

	Gamble gamble;
	
	gamble.MakePrediction("Alex1", 3);
	Sleep(100);
	gamble.MakePrediction("Alex2", 5);
	Sleep(100);
	gamble.MakePrediction("Alex3", 8);
	Sleep(100);
	gamble.MakePrediction("Alex5", 11);
	Sleep(100);
	gamble.MakePrediction("Alex6", 15);
	Sleep(100);
	gamble.MakePrediction("Alex7", 19);

	Sleep(100);

	gamble.allPredictions();
	gamble.findAnAccuratePrediction();

	Sleep(2000);

	DeleteCriticalSection(&criticalSection);

	return 0;
}