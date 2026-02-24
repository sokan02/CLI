//
// Created by sofija on 24/02/26.
//

#ifndef ECHO_H
#define ECHO_H
#include <string>
#include <iostream>
#include "Command.h"
#include "streamInterfaces.h"

class Echo : public Command, public IInput, public IOutput {
public:
    void execute() override;
    std::string getText(std::istream& is);
    Echo(const std::string& arg, const std::string& opt);
    void setInput(std::istream* i) override { in = i; }
    void setOutput(std::ostream* o) override { out = o; }

private:
    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;
};

#endif //ECHO_H
