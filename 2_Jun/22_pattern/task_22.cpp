#include <iostream>

//SOLID

//Singlton
class Singlton{
public:
	Singlton(){
		m_instance = this;
	}
	static Singlton* getSinglton(){
		return m_instance;
	}
	std::string getAppPath(){
		return "cd: main/";
	}
private:
	static Singlton* m_instance;
};

Singlton* Singlton::m_instance = 0;

int main(){
	
	Singlton singlton();
	
	Singlton* p_singlton;
	
	p_singlton = Singlton::getSinglton();
	
	std::cout << p_singlton->getAppPath() << std::endl;
	
	return 0;
}

