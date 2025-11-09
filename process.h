#ifndef PROCESS_H
#define PROCESS_H

#include <string>

class Process {
private:
    int pid;
    std::string user;
    double cpuUsage;
    double memUsage;
    std::string command;

public:
    Process(int pid);
    int getPid() const;
    std::string getUser() const;
    double getCpuUsage() const;
    double getMemUsage() const;
    std::string getCommand() const;

    void updateUsage();
};

#endif
