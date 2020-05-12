#include "spawner.h"

Spawner::Spawner(std::string name)
{
	m_alive = true;
	m_future = m_exitSignal.get_future();
    m_name = name;

	m_loopThread = std::thread(&Spawner::Loop, this);
	m_terminateThread = std::thread(&Spawner::WaitForTerminate, this);
}

Spawner::~Spawner()
{
    m_loopThread.join();
    m_terminateThread.join();
}

void Spawner::Loop()
{
    std::string checkCommand = "pidof " + m_name;
    std::string startCommand = "setsid ./" + m_name + " &";

    int pId;
    std::string result;
    do {
        result = Execute(checkCommand.c_str());
        if(m_alive && !ToInt(result.substr(0, result.length() - 1), pId))
        {
            std::cout << std::endl << m_name << " is down. Restarting in a moment." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(RELAUNCH_DELAY));

            try { system(startCommand.c_str()); }
            catch (const std::exception& e) { }

            std::ofstream errorLogFile;
            errorLogFile.open ("LaunchLog.txt", std::ios::app);
            errorLogFile << "pId : " << pId << "\n";
            errorLogFile.close();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_DELAY));
    }
    while(m_alive || ToInt(result.substr(0, result.length() - 1), pId));
    if(ToInt(result.substr(0, result.length() - 1), pId))
        Execute(std::string("kill " + pId).c_str());
}

void Spawner::WaitForTerminate()
{
    while(m_alive && m_future.wait_for(std::chrono::milliseconds(WAIT_DELAY)) == std::future_status::timeout);
}

void Spawner::Stop()
{
	if(m_future.wait_for(std::chrono::milliseconds(WAIT_DELAY)) == std::future_status::timeout)
		m_exitSignal.set_value();
    m_alive = false;
}

std::string Spawner::Execute(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}