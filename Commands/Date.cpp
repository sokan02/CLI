//
// Created by sofija on 24/02/26.
//

#include "Date.h"
#include <iomanip>
#include <iostream>

Date::Date(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

void Date::execute() {
  time_t now = time(nullptr);
  tm *localTime = localtime(&now);

  (*out) << std::put_time(localTime, "%d-%m-%Y") << std::flush;
}
