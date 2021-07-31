#include <iostream>
#include <string>
#include <algorithm>

size_t getLastWorldSizeFor(const std::string& str) {
	for (int i = str.length(); i >= 0; i--) {
		if (str[i] == ' ') {
			return str.length() - i - 1;
		}
	}
	return 0;
}

size_t getLastWorldSize(const std::string& str) {
	return str.length() - str.find_last_of(' ') - 1;
}

bool checkPolynom(const std::string& str) {

	std::string checkingStr(str);

	checkingStr.erase(std::remove(checkingStr.begin(), checkingStr.end(), ' '), checkingStr.end());
	std::transform(checkingStr.begin(), checkingStr.end(), checkingStr.begin(), tolower);
	std::reverse(&checkingStr[0], &checkingStr[checkingStr.length()/2]);

	std::string beginCheckingStr(checkingStr.begin(), (checkingStr.begin() + checkingStr.length() / 2));
	std::string endCheckingStr((checkingStr.begin() + checkingStr.length() / 2), checkingStr.end());

	if (beginCheckingStr.length() != endCheckingStr.length()) {
		endCheckingStr.erase(endCheckingStr.begin(), (endCheckingStr.begin() + 1));
	}
	return beginCheckingStr == endCheckingStr;
}

int main() {

	std::string str1 = "Alex World!";

	std::cout << getLastWorldSizeFor(str1) << std::endl;
	std::cout << getLastWorldSize(str1) << std::endl;

	std::string str2 = "Doge1e g o d";
	std::cout << checkPolynom(str2) << std::endl;

	return 0;
}