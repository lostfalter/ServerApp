#include "EchoClient.h"

#include <iostream>
#include <array>

#include "asio.hpp"

EchoClient::EchoClient(std::string serverPort)
    : mThread(NULL), mExit(false), mServerPort(serverPort), mSocket(mIOService)
{

    mServerIPAddress = "127.0.0.1";

    Run();
}

EchoClient::~EchoClient()
{
    Stop();
}

void EchoClient::WorkingJob()
{
    try
    {
        ConnectToServer();

        while (true)
        {
            if (NeedToExit())
            {
                break;
            }

            WaitForUserInput();

            if (mInputMessage == "exit")
            {
                break;
            }

            SendMessageToServer();

            ReceiveMessageFromServer();
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void EchoClient::ConnectToServer()
{
    using asio::ip::tcp;

    tcp::resolver resolver(mIOService);
    tcp::resolver::query query(mServerIPAddress, mServerPort);
    mEndpointIterator = resolver.resolve(query);

    asio::connect(mSocket, mEndpointIterator);

    ReceiveMessageFromServer();
}

void EchoClient::WaitForUserInput()
{
    std::getline(std::cin, mInputMessage);
}

void EchoClient::SendMessageToServer()
{
    asio::write(mSocket,  asio::buffer(mInputMessage));
}

void EchoClient::ReceiveMessageFromServer()
{

    asio::error_code errorCode;
    size_t len = mSocket.read_some(asio::buffer(mBuffer), errorCode);

    if (errorCode == asio::error::eof)
    {
        // connection has been ended
        std::cout << "Connection has been closed from server.\n";
        mExit = true;
    }
    else if (errorCode)
    {
        std::cout << "Connection has been closed from server.\n";

        throw asio::system_error(errorCode);
        // other error
    }
    else
    {
        // normal 
        // just print receive message
        std::cout.write(mBuffer.data(), len);
        std::cout << std::endl;
    }
}

void EchoClient::Stop()
{
    if (mThread == NULL)
    {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(mMutex);
        mExit = true;
    }
    
    mThread->join();
    delete mThread;
}

void EchoClient::Run()
{
    WorkingJob();
    //mThread = new std::thread(&EchoClient::WorkingJob, this);
}

bool EchoClient::NeedToExit() const
{
    std::lock_guard<std::mutex> lock(mMutex);

    return mExit;
}
