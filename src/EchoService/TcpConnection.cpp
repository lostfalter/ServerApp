#include "TcpConnection.h"

#include <functional>

TcpConnection::ptr TcpConnection::Create(asio::io_service& ioService)
{
    return std::make_shared<TcpConnection>(ioService);
}

void TcpConnection::Start()
{
    asio::async_write(
        m_socket,
        asio::buffer(m_message),
        std::bind(
            &TcpConnection::OnWriteDone,
            shared_from_this(),
            std::placeholders::_1,
            std::placeholders::_2));
}

asio::ip::tcp::socket& TcpConnection::GetSocket()
{
    return m_socket;
}

TcpConnection::TcpConnection(asio::io_service& ioService)
    : m_socket(ioService)
{
    
}

void TcpConnection::OnWriteDone(
    const asio::error_code& errorCode, size_t transferredByte)
{
    
}
