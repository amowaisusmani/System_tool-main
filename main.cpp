#include "system_monitor.h"
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    SystemMonitor monitor;
    char choice;

    while (true) {
        monitor.refresh();
        monitor.display();

        cout << "\nEnter choice: ";
        if (cin.rdbuf()->in_avail()) {
            cin >> choice;
            if (choice == 'q')
                break;
            else if (choice == 'k') {
                int pid;
                cout << "Enter PID to kill: ";
                cin >> pid;
                monitor.killProcess(pid);
                this_thread::sleep_for(chrono::seconds(2));
            }
        }

        this_thread::sleep_for(chrono::seconds(3));
    }

    cout << "Exiting System Monitor.\n";
    return 0;
}
