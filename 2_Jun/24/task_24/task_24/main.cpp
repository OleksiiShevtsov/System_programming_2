#include <iostream>
#include <string>
#include <algorithm>

size_t getLastWorldSizeFor(std::string& str) {
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
	for (;;) {
		str.find(' ');
		str.in
	}
}

int main() {

	std::string str = "Alex World!";

	std::cout << getLastWorldSizeFor(str) << std::endl;
	std::cout << getLastWorldSize(str) << std::endl;

	str = "Do geese see god";

	return 0;
}