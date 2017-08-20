#pragma once

#include <thread>
#include <mutex>

class EchoClient
{
public:
    EchoClient();
    ~EchoClient();
private:
    void Run();
    void Stop();

    void WorkingJob();
    
    bool NeedToExit() const;
private:
    std::thread* m_thread;
    
    mutable std::mutex m_mutex;
    bool m_exit;
};