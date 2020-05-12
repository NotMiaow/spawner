#ifndef SPAWNER_H__
#define SPAWNER_H__

#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <string>
#include <fstream>

#include "basic_lib.h"

class Spawner
{
public:
    Spawner() { }
    Spawner(std::string name);
    ~Spawner();
    void Stop();
private:
    void Loop();
    void WaitForTerminate();
    std::string Execute(const char* cmd);
private:
    std::atomic<bool> m_alive;
    std::promise<void> m_exitSignal;
    std::shared_future<void> m_future;
    std::thread m_terminateThread;
    std::thread m_loopThread;

    std::string m_name;
    const int WAIT_DELAY = 50;
    const int RELAUNCH_DELAY = 500;
};

#endif