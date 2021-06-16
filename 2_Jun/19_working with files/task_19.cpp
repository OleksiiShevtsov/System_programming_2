#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

int main() {

	fstream fs;
	fs.open("task_19.txt", fstream::in | fstream::out | fstream::app);

	if (!fs.is_open()) {
		cout << "the file did not open" << endl;
	}
	else {
		string msg;
		int value;
		cout << "file is open" << endl;
		cout << "enter 1 for recording" << endl;
		cout << "enter 2 for reading" << endl;
		cin >> value;

		if (value == 1) {
			cin >> msg;
			fs << msg << "\n";

			fs.seekg(0, std::ios::end);
			cout << "size str: " << fs.tellg() << endl;

			string str(std::istreambuf_iterator<char>(fs), {});
			cout << str << endl;
		}

		if (value == 2) {
			while (!fs.eof()) {
				msg = "";
				fs >> msg;
				cout << msg << endl;
			}

			string str(std::istreambuf_iterator<char>(fs), {});
			cout << str << endl;
		}
	}

	return 0;
}
