//
// Created by sofija on 24/02/26.
//

#include "Truncate.h"

#include <fstream>
#include <iostream>

Truncate::Truncate(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

void Truncate::execute() {
    if (m_opt != "") {
        std::cout << "Error - truncate cannot have an option" << std::endl;
        return;
    }
    std::ofstream file(m_arg, std::ios::trunc);
    if (!file) {
        std::cerr << "Failed to clear file\n";
    }
}
