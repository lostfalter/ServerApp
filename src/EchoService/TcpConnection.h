#pragma once

#include <memory>
#include <string>

#include "asio.hpp"

class TcpConnection : public std::enable_shared_from_this<TcpConnection>
{
public:
    typedef std::shared_ptr<TcpConnection> ptr;
public:
    static ptr Create(asio::io_service& ioService);

    TcpConnection(asio::io_service& ioService);
public:
    void Start();

    asio::ip::tcp::socket& GetSocket();
private:
    void OnReadDone(const asio::error_code& errorCode, size_t transferredByte);

    void OnWriteDone(const asio::error_code& errorCode, size_t transferredByte);
private:
    asio::ip::tcp::socket mSocket;
    
    std::string mWelcomeMessage;
    std::string mMessage;

    std::array<char, 128> mBuffer;
};