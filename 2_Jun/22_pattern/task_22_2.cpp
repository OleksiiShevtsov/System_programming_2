#include <iostream>

//SOLID

//fabric
class A{public: virtual void f() = 0;};
class A1 : public A{public: void f(){std::cout<<"A1";}};
class A2 : public A{public: void f(){std::cout<<"A2";}};

A* getA(){
	if(true){
		return new A1;
	}
	else {
		return new A2;
	}
}

int main(){
	
	A* a = getA();
	
	a->f();
	
	return 0;
}

