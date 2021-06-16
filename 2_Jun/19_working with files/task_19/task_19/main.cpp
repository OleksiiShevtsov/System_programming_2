#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <Windows.h>

namespace fs = std::filesystem;

int main() {
	
	fs::path p("../");

	std::ofstream(p/"task_19.txt");

	fs::create_directories(p/"folder");

	for (auto& dir : fs::directory_iterator(p)) {
		std::cout << dir.path() << std::endl;
	}

	p /= "1.txt";
	std::cout << p.extension() << std::endl;
	std::cout << p.filename() << std::endl;
	std::cout << p.parent_path() << std::endl;
	std::cout << "size file: " << fs::file_size(p.parent_path()/"task_19.txt") << std::endl;

	return 0;
}