//
// Created by sofija on 24/02/26.
//
#include "Rm.h"
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <iostream>

Rm::Rm(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

void Rm::execute() {
  if (m_opt != "") {
    std::cerr << "Error - rm cannot have an option\n";
    return;
  }
  if (!std::filesystem::remove(m_arg)) {
    std::cerr << "Could not delete file\n";
  }
}