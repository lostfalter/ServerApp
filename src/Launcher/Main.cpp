#include <iostream>

#include "EchoService/EchoClient.h"
#include "EchoService/EchoServer.h"


int main()
{
    std::cout << "Start to test server app!" << std::endl;
    
    
    EchoServer server(145);
    EchoClient client("145");

    return 0;
}