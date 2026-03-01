//
// Created by sofija on 24/02/26.
//
#include "Time.h"
#include <iomanip>
#include <iostream>

Time::Time(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

void Time::execute() {
  time_t now = time(nullptr);
  tm *localTime = localtime(&now);

  (*out) << std::put_time(localTime, "%H:%M:%S") << std::flush;
}
