//
// Created by sofija on 13/01/26.
//
#include "Program.h"
#include "Commands/streamInterfaces.h"
#include <iostream>
#include <fstream>
#include <iomanip>

static std::string noQuotation(const std::string& text) {
    std::string newText = "";
    for (char c : text) {
        if (c != '"') {
            newText.push_back(c);
        }
    }
    return newText;
}

static bool isFile(std::string s) {
    return !(s.size() >= 2 && s.front() == '"' && s.back() == '"');
}

Program::Program() : argument("$"){}

Program* Program::getInstance() {
    static Program instance;
    return &instance;
}

Program::~Program() {
    for (Command* cmd : commands) {
        delete cmd;
    }
}

void Program::add(Command* cmd) {
    commands.push_back(cmd);
    if (commands.size() == 1) it = commands.begin();
    else ++it;
}

void Program::executeNext() {
    wireSingle(*it);
    (*it)->execute();
}

bool Program::hasNext() {
    return it != commands.end();
}

string Program::getArgument() {
    return argument;
}

void Program::setArgument(string arg) {
    argument = arg;
}
void Program::wireSingle(Command *cmd) {
    if (!cmd) return;

    if (IOutput* out = dynamic_cast<IOutput*>(cmd)) {
        out->setOutput(&std::cout);
    }

    IInput* in = dynamic_cast<IInput*>(cmd);
    if (!in) return;

    const std::string& arg = cmd->m_arg;

    std::istream* inStream = &std::cin;

    if (arg.empty()) {
        inStream = &std::cin;
    }
    else if (isFile(arg)) {
        fileIn.close();
        fileIn.open(arg);

        if (!fileIn.is_open()) {
            throw std::runtime_error("Error - cannot open file: " + arg);
        }

        inStream = &fileIn;
    }
    else {
        textIn.clear();
        textIn.str("");
        textIn.str(noQuotation(arg));
        inStream = &textIn;
    }

    in->setInput(inStream);
}