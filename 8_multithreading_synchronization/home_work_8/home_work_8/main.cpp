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
		m_hiddenNumber = rand() % 100 + 1;
	}

	void MakePrediction(const char* userName, int prediction) {

		m_dataPrediction.predictionsValue = prediction;
		m_dataPrediction.name = userName;

		HANDLE thread = CreateThread(0, 0, ThreadStart, this, 0, 0);
	}

	DataPrediction m_dataPrediction;

	void setPredictions(const char* userName, int prediction) {
		m_predictions.insert(std::pair<const char*, int>(userName, prediction));
	}

	void findAnAccuratePrediction() {

		std::map<const char*, int> bestPredictions;

		int temp = 0;

		for (int i = 0; i < m_predictions.size(); i++) {
			for (auto iter = m_predictions.begin(); iter != m_predictions.end(); iter++) {
				temp = m_hiddenNumber - iter->second;
				if (temp > abs(m_hiddenNumber - iter->second)) {
					temp = abs(m_hiddenNumber - iter->second);
				}
			}
		}
	}

private:

	std::map<const char*, int> m_predictions;

	int m_hiddenNumber;
};

DWORD WINAPI ThreadStart(void* param) {

	EnterCriticalSection(&criticalSection);

		Gamble* gamble = static_cast<Gamble*>(param);
		cout << gamble->m_dataPrediction.predictionsValue << endl;
		cout << gamble->m_dataPrediction.name << endl;
		gamble->setPredictions(gamble->m_dataPrediction.name, gamble->m_dataPrediction.predictionsValue);

	LeaveCriticalSection(&criticalSection);

	return 0;
}

int main() {

	InitializeCriticalSection(&criticalSection);

	Gamble gamble;
	
	gamble.MakePrediction("Alex", 12);

	Sleep(2000);
	DeleteCriticalSection(&criticalSection);

	return 0;
}