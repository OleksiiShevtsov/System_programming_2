//#include "calculator_impl.h"
//#include "calculator_dll.h"
#include "windows.h"
#include <iostream>

typedef int *Sum(int, int);

typedef bool(IDP)();

int main() {

	HMODULE loadLibrary1 = LoadLibraryA("calculator_dll.dll");
	void* pointer1 = GetProcAddress(loadLibrary1, "sum");
	Sum* sum = static_cast<Sum*>(pointer1);
	std::cout << sum(10, 10) << std::endl;

	HMODULE loadLibrary2 = LoadLibraryA("kernel32.dll");
	void* pointer2 = GetProcAddress(loadLibrary2, "IsDebuggerPresent");
	IDP* d = static_cast<IDP*>(pointer2);
	std::cout << d() << std::endl;


	//std::cout << sum(10, 10) << std::endl;

	return 0;
}