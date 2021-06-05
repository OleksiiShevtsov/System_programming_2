#include <any>
#include <iostream>
#include <type_traits>
#include <typeinfo>
#include <vector>

template <class T>
std::string type_name()
{
    typedef typename std::remove_reference<T>::type TR;
    std::string r = typeid(TR).name();
    if (std::is_const<TR>::value)
        r = "const " + r;
    if (std::is_lvalue_reference<T>::value)
        r += "&";
    if (std::is_volatile<TR>::value)
        r += " volatile";
    else if (std::is_rvalue_reference<T>::value)
        r += "&&";
    return r;
}

template<typename T>
void f(T& val) {
    std::cout << sizeof(val) << std::endl;
    std::cout << type_name<T>() << std::endl;
    std::cout << type_name<decltype(val)>() << std::endl;
}

struct Orc {
    Orc() {}
};

int main() {

    auto i = 10;
    std::cout << "auto: " << i << std::endl;

    Orc orc;
    int array[10] = {};
    f("");
    std::string str;

    f(orc);
    f(array);
    f(str);

    std::vector<int> myMap(10, 10);

    for (auto it : myMap) {
        std::cout << it << std::endl;
    }
    //std::any a = 1;
}