#include <iostream>
#include <string>
#include "user_info.pb.h"

int main()
{
    //client
    UserInfo clientUi;
    clientUi.set_name("Alex");
    clientUi.set_age(24);

    std::string data = clientUi.SerializeAsString();

    //server
    UserInfo serverUi;
    serverUi.ParseFromString(data);

    std::cout << serverUi.name() << std::endl;
    std::cout << serverUi.age() << std::endl;
}