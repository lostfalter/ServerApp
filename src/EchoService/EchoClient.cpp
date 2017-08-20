#include "EchoClient.h"

#include <iostream>
#include <array>

#include "asio.hpp"

EchoClient::EchoClient()
    : m_thread(NULL), m_exit(false)
{
    Run();
}

EchoClient::~EchoClient()
{
    Stop();
}

void EchoClient::WorkingJob()
{
    std::string ipAddress = "127.0.0.1";
    
    using asio::ip::tcp;

    try
    {
        asio::io_service ioService;

        tcp::resolver resolver(ioService);
        tcp::resolver::query query(ipAddress, "daytime");
        tcp::resolver::iterator endpointIterator = resolver.resolve(query);

        tcp::socket socket(ioService);

        asio::connect(socket, endpointIterator);

        while (true)
        {
            if (NeedToExit())
            {
                break;
            }

            std::array<char, 128> buffer;
            asio::error_code errorCode;

            size_t len = socket.read_some(asio::buffer(buffer), errorCode);

            if (errorCode == asio::error::eof)
            {
                // connection has been ended
                break;
            }
            else if (errorCode)
            {
                throw asio::system_error(errorCode);
                // other error
            }

            std::cout.write(buffer.data(), len);
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

void EchoClient::Stop()
{
    if (m_thread == NULL)
    {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_exit = true;
    }
    
    m_thread->join();
    delete m_thread;
}

void EchoClient::Run()
{
    m_thread = new std::thread(&EchoClient::WorkingJob, this);
}

bool EchoClient::NeedToExit() const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return m_exit;
}
