//
// Created by sofija on 24/02/26.
//
#include "Rm.h"
#include <filesystem>
#include <cerrno>
#include <iostream>
#include <ostream>
#include <cstring>

Rm::Rm(const std::string &arg, const std::string &opt) : Command(arg, opt) {}


void Rm::execute() {
    if (m_opt != "") {
        std::cout << "Error - rm cannot have an option" << std::endl;
        return;
    }
    if (!std::filesystem::remove(m_arg)) {
        std::cout << "Could not delete file" << std::endl;
    }
}