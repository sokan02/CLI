//
// Created by sofija on 24/02/26.
//
#include "Touch.h"
#include <iostream>
#include <fstream>
#include <filesystem>

Touch::Touch(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

void Touch::execute() {
    if (m_opt != "") {
        std::cout << "Error - touch cannot have an option" << std::endl;
    }
    if (!std::filesystem::exists(m_arg)) {
        std::ofstream out(m_arg);
        out.close();
    } else {
        std::cout << "Error: File already exists" << std::endl;
    }
}
