//
// Created by sofija on 27/05/25.
//

#ifndef COMMAND_H
#define COMMAND_H
#include <string>

class Command {
public:
        Command(const std::string& arg, const std::string& opt);
        virtual void execute() = 0;
//protected:
    std::string m_arg;
    std::string m_opt;
    bool isFile();
    std::string noQuotation(std::string text);
    std::string readConsole();
    std::string readFile();
};

#endif //COMMAND_H
