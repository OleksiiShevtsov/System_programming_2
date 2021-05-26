#include <iostream>
#include <windows.h>

template<class T, T INVALID_VALUE>
class WinResourceWrapper {
public:
	WinResourceWrapper(T res) : m_res(res) {

		if (m_res == INVALID_VALUE) {
			throw("invalid value");
		}
	}

	T getHendl() const {
		return m_res;
	}

	~WinResourceWrapper();

	WinResourceWrapper(const WinResourceWrapper&) = delete;
	WinResourceWrapper& operator=(const WinResourceWrapper&) = delete;

private:
	T m_res;
};

template<>
WinResourceWrapper<HANDLE, INVALID_HANDLE_VALUE>::~WinResourceWrapper() {
	CloseHandle(m_res);
	std::cout << "close HANDLE" << std::endl;
}

template<>
WinResourceWrapper<HMODULE, static_cast<HMODULE>(NULL)>::~WinResourceWrapper() {
	FreeLibrary(m_res);
	std::cout << "close HMODULE" << std::endl;
}

using HandleWrapper = WinResourceWrapper<HANDLE, INVALID_HANDLE_VALUE>;
using HmoduleWrapper = WinResourceWrapper<HMODULE, static_cast<HMODULE>(NULL)>;

int main() {

	HANDLE handle = 0;
	HandleWrapper wrapper1 = (handle);
	HMODULE hmodule = reinterpret_cast<HMODULE>(1);
	HmoduleWrapper wrapper2 = (hmodule);

	int exit; std::cin >> exit;
	return 0;
}
