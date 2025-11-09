#include "process.h"
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <pwd.h>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

Process::Process(int pid) : pid(pid), cpuUsage(0.0), memUsage(0.0) {
    // Get command
    ifstream cmdFile("/proc/" + to_string(pid) + "/comm");
    getline(cmdFile, command);

    // Get memory usage (in MB)
    ifstream status("/proc/" + to_string(pid) + "/status");
    string line;
    while (getline(status, line)) {
        if (line.find("VmRSS:") == 0) {
            istringstream iss(line);
            string key;
            double memKb;
            iss >> key >> memKb;
            memUsage = memKb / 1024.0;
            break;
        }
    }

    // Get user (from UID)
    ifstream statusFile("/proc/" + to_string(pid) + "/status");
    while (getline(statusFile, line)) {
        if (line.find("Uid:") == 0) {
            istringstream iss(line);
            string key;
            int uid;
            iss >> key >> uid;
            struct passwd *pw = getpwuid(uid);
            if (pw)
                user = pw->pw_name;
            else
                user = "unknown";
            break;
        }
    }
}

int Process::getPid() const { return pid; }
std::string Process::getUser() const { return user; }
double Process::getCpuUsage() const { return cpuUsage; }
double Process::getMemUsage() const { return memUsage; }
std::string Process::getCommand() const { return command; }

void Process::updateUsage() {
    // Simplified CPU usage calculation (can be enhanced)
    cpuUsage = 0.0; // placeholder; complex to calculate precisely
}
