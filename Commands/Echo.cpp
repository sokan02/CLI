//
// Created by sofija on 24/02/26.
//

#include "Echo.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>

Echo::Echo(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

std::string Echo::getText(std::istream &is) {
    std::string text;

    char c;
    while (is.get(c)) {
        text += c;
    }
    if (std::cin.eof()) {
        std::cin.clear();
        clearerr(stdin);
    }
    return text;
}


void Echo::execute() {
    (*out) << getText(*in) << std::endl;
}