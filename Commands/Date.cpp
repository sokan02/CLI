//
// Created by sofija on 24/02/26.
//

#include "Date.h"
#include <iostream>
#include <iomanip>

Date::Date(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

void Date::execute() {
    if (m_arg != "" || m_opt != "") {
        std::cout << "Error - date does not have options or arguments" << std::endl;
        return;
    }
    time_t now = time(nullptr);
    tm* localTime = localtime(&now);

    (*out)<< std::put_time(localTime, "%d-%m-%Y") << std::endl;
}
