#include <iostream>

#include "EchoService/EchoClient.h"
#include "EchoService/EchoServer.h"


int main()
{
    std::cout << "Start to test server app!" << std::endl;

    
    EchoServer server;
    EchoClient client;

    int b;
    std::cin >> b;

    return 0;
}