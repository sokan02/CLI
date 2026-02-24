//
// Created by sofija on 24/02/26.
//
#include "Time.h"
#include <iostream>
#include<iomanip>

Time::Time(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

void Time::execute() {
    if (m_arg != "" || m_opt != "") {
        std::cout << "Error - time cannot have arguments or options." << std::endl;
        return;
    }
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    (*out) << std::put_time(localTime, "%H:%M:%S") << std::endl;
}
