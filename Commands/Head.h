//
// Created by sofija on 24/02/26.
//

#ifndef HEAD_H
#define HEAD_H
#include "Command.h"
#include "streamInterfaces.h"

class Head : public Command, public IInput, public IOutput {
public:
    Head(const std::string& arg, const std::string& opt);
    void execute() override;
    int getNoRows();
    std::string getLines(int noLines, std::string text);
    void setInput(std::istream* i) override { in = i; }
    void setOutput(std::ostream* o) override { out = o; }
private:
    std::istream* in = nullptr;
    std::ostream* out = nullptr;
};

#endif //HEAD_H
