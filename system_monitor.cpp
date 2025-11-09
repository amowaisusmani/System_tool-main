#include "system_monitor.h"
#include <filesystem>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <signal.h>

using namespace std;
namespace fs = std::filesystem;

void SystemMonitor::refresh() {
    processes.clear();
    for (auto &entry : fs::directory_iterator("/proc")) {
        if (entry.is_directory()) {
            string name = entry.path().filename();
            if (all_of(name.begin(), name.end(), ::isdigit)) {
                int pid = stoi(name);
                processes.emplace_back(pid);
            }
        }
    }
}

void SystemMonitor::display() const {
    system("clear");
    cout << left << setw(8) << "PID"
         << setw(12) << "USER"
         << setw(10) << "CPU(%)"
         << setw(10) << "MEM(MB)"
         << setw(20) << "COMMAND" << endl;
    cout << string(60, '-') << endl;

    for (const auto &p : processes) {
        cout << left << setw(8) << p.getPid()
             << setw(12) << p.getUser()
             << setw(10) << fixed << setprecision(1) << p.getCpuUsage()
             << setw(10) << p.getMemUsage()
             << setw(20) << p.getCommand() << endl;
    }

    cout << "\n[k] Kill a process | [q] Quit | Refreshing every 3s...\n";
}

void SystemMonitor::killProcess(int pid) {
    if (kill(pid, SIGTERM) == 0)
        cout << "Process " << pid << " terminated successfully.\n";
    else
        perror("Error killing process");
}
