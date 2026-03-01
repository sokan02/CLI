//
// Created by sofija on 24/02/26.
//
#include "Touch.h"
#include <filesystem>
#include <fstream>
#include <iostream>

Touch::Touch(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

void Touch::execute() {
  if (!std::filesystem::exists(m_arg)) {
    std::ofstream out(m_arg);
    out.close();
  } else {
    std::cerr << "Error: File already exists\n";
  }
}
