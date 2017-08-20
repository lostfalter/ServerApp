#pragma once

#include "TcpConnection.h"

#include <memory>


class EchoServer
{
public:
    EchoServer();
    ~EchoServer();
private:
    void Start();
    void Stop();
    
    void OnAcceptConnection(
        asio::ip::tcp::acceptor& acceptor,
        TcpConnection::ptr connection,
        const asio::error_code& errorCode);

    void WaitForConnection(asio::ip::tcp::acceptor& acceptor);
private:
    asio::io_service m_ioService;
};

