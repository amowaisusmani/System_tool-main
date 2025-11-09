#ifndef SYSTEM_MONITOR_H
#define SYSTEM_MONITOR_H

#include <vector>
#include "process.h"

class SystemMonitor {
private:
    std::vector<Process> processes;

public:
    void refresh();
    void display() const;
    void killProcess(int pid);
};

#endif
