#include "TcpConnection.h"

#include <functional>
#include <iostream>

TcpConnection::ptr TcpConnection::Create(asio::io_service& ioService)
{
    return std::make_shared<TcpConnection>(ioService);
}

void TcpConnection::Start()
{
    asio::async_write(
        mSocket,
        asio::buffer(mWelcomeMessage),
        std::bind(
            &TcpConnection::OnWriteDone,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));

}

asio::ip::tcp::socket& TcpConnection::GetSocket()
{
    return mSocket;
}

TcpConnection::TcpConnection(asio::io_service& ioService)
    : mSocket(ioService)
{
    mWelcomeMessage = "Welcome to lostfly's server!\n";
}

void TcpConnection::OnReadDone(
    const asio::error_code& errorCode, size_t transferredByte)
{
    if (errorCode == asio::error::eof)
    {
        // connection has been ended
    }
    else if (errorCode)
    {
        throw asio::system_error(errorCode);
        // other error
    }
    else
    {
        // normal 
        // send it back to client
        asio::async_write(
            mSocket,
            asio::buffer(mBuffer, transferredByte),
            std::bind(
                &TcpConnection::OnWriteDone,
                shared_from_this(),
                std::placeholders::_1,
                std::placeholders::_2));
    }
}

void TcpConnection::OnWriteDone(
    const asio::error_code& errorCode, size_t transferredByte)
{
    //std::cout << "TCP connection write done." << std::endl;
    // TODO: print some log
    mSocket.async_read_some(
        asio::buffer(mBuffer),
        std::bind(
            &TcpConnection::OnReadDone,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}
