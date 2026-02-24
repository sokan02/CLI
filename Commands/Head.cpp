//
// Created by sofija on 24/02/26.
//

#include "Head.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include<string>

Head::Head(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

int Head::getNoRows() {
    int rows = 0;
    for (char c : m_opt) {
        if (std::isdigit(c)) {
            rows = rows * 10 + c - '0';
        }
    }
    return rows;
}

std::string Head::getLines(int noLines, std::string text) {
    std::string newText;
    int cnt = 0;
    for (char c : text) {
        if (cnt == noLines) return newText;
        newText += c;
        if (c == '\n') cnt++;
    }
    return newText;
}



void Head::execute() {
    if (m_opt == "") {
        std::cout << "Error - head requires an option" << std::endl;
        return;
    }
    std::string text;
    if (m_arg == "")
        text = readConsole();
    else if (!isFile())
        text = this->noQuotation(this->m_arg);
    else
        text = readFile();

    std::cout << getLines(getNoRows(), text) << std::endl;
}