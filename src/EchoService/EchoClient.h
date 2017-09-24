#pragma once

#include <thread>
#include <mutex>
#include <string>

#include "asio.hpp"

class EchoClient
{
public:
    EchoClient(std::string serverPort);
    ~EchoClient();
private:
    void Run();
    void Stop();

    void WorkingJob();

    void ConnectToServer();

    void WaitForUserInput();

    void SendMessageToServer();
    
    void ReceiveMessageFromServer();
    
    bool NeedToExit() const;
private:
    std::thread* mThread;
    
    mutable std::mutex mMutex;
    bool mExit;

    std::string mInputMessage;
    std::string mReceiveMessage;
    std::array<char, 128> mBuffer;

    std::string mServerIPAddress;

    asio::io_service mIOService;
    asio::ip::tcp::socket mSocket;
    
    std::string mServerPort;

    asio::ip::tcp::resolver::iterator mEndpointIterator;
};