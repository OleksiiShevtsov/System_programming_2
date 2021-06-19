#include <iostream>
#include <vector>
#include <map>

class Alex {

public:
	Alex(const std::initializer_list<int>& initList) {
		for (auto& init : initList) {
			vecAlex.push_back(init);
		}
	}

	void printAlex(){
		for (const auto& vec : vecAlex) {
			std::cout << vec << " ";
		}
	}

private:
	std::vector<int> vecAlex;
};

struct Worker {
	std::string name = "Alex";
	int age = 24;
} worker;

auto getWorker() {
	return std::tuple("Alex3", 26);
}

int main() {

	std::initializer_list<int> initList{ 1, 2, 3 };
	std::cout << initList.size() << std::endl;

	/*int i1 = 0;
	int i2( 0 );
	int i3{ 0 };
	int i4 = { 0 };
	int i5 = int(0);
	int i6 = int{ 0 };*/
	//auto i7 = { 0 };//initializer_list
	
	Alex alex{ 1, 2, 3, 4, 5 };
	alex.printAlex();

	/////////////////////////
	
	auto[name, age] = getWorker();
	std::cout << name << std::endl;
	std::cout << age << std::endl;

	std::map<std::string, int> myMap;
	std::pair<std::string, int> p("Alex", 25);
	auto [key, data] = myMap.insert(p);
	std::cout << key->first << std::endl;
	std::cout << key->second << std::endl;
	std::cout << data << std::endl;


	//std::tuple<std::map<std::string, int>::iterator, bool> t(myMap.insert(p));

	//дз std::variant, std::any, initialization in if()

	return 0;
}
