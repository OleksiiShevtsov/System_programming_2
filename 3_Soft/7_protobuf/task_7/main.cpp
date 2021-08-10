#include <iostream>
#include <string>
#include "proto_message/user_info.pb.h"

int main()
{
    //client
    Diploma diploma;
    diploma.set_specialization("Dev");
    diploma.set_degree( Diploma_Degree_BACHELOR );

    UserInfo clientUi;
    clientUi.set_name( "Alex" );
    clientUi.set_age( 24 );
    clientUi.set_allocated_diploma( &diploma );

    Notebook* notebook_1 = clientUi.add_notebook();
    notebook_1->set_size( 64 );
    Notebook* notebook_2 = clientUi.add_notebook();
    notebook_2->set_size( 96 );

    std::string data = clientUi.SerializeAsString();

    //server
    UserInfo serverUi;
    serverUi.ParseFromString(data);

    std::cout << serverUi.name() << std::endl;
    std::cout << serverUi.age() << std::endl;

    std::cout << serverUi.diploma().specialization() << std::endl;
    std::cout << serverUi.diploma().degree() << std::endl;

    for( int i = 0; i < serverUi.notebook_size(); i++ ){
        std::cout << serverUi.notebook(i).size() << std::endl;
    }

    return 0;
}

//to json format
//#include <google/protobuf/util/json_util.h>
//google::protobuf::util::JsonPrintOptions options;
//options.add_whitespace = true;
//options.always_print_primitive_fields = true;
//std::string json_string;
//MessageToJsonString(userInfo, &json_string, options);
