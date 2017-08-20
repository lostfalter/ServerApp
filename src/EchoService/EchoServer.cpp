#include "EchoServer.h"
#include "Timer/Timer.h"
#include <iostream>
#include "asio.hpp"

EchoServer::EchoServer()
{
    Start();
}

EchoServer::~EchoServer()
{
    Stop();
}

void EchoServer::Stop()
{
    m_ioService.stop();
}

void EchoServer::Start()
{
    try
    {
        using asio::ip::tcp;

        tcp::acceptor acceptor(m_ioService, tcp::endpoint(tcp::v4(), 13));

        WaitForConnection(acceptor);

        m_ioService.run();
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void EchoServer::OnAcceptConnection(
    asio::ip::tcp::acceptor& acceptor,
    TcpConnection::ptr connection,
    const asio::error_code& errorCode)
{
    if (errorCode)
    {
        // error happened
        return;
    }

    connection->Start();

    WaitForConnection(acceptor);
}

void EchoServer::WaitForConnection(asio::ip::tcp::acceptor& acceptor)
{
    TcpConnection::ptr connection = std::make_shared<TcpConnection>(m_ioService);

    acceptor.async_accept(
        connection->GetSocket(),
        std::bind(
            &EchoServer::OnAcceptConnection,
            this,
            std::ref(acceptor),
            connection,
            std::placeholders::_1));
}
