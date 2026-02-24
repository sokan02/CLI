//
// Created by sofija on 24/02/26.
//

#ifndef TR_H
#define TR_H
#include "Command.h"
#include "streamInterfaces.h"

class Tr : public Command, public IInput, public IOutput {
public:
    Tr(const std::string& arg, const std::string& opt, const std::string& with);
    void execute() override;
    void replaceAll(std::string& str, const std::string& from, const std::string& to);
    void setInput(std::istream* i) override { in = i; }
    void setOutput(std::ostream* o) override { out = o; }
private:
    std::string getText(std::istream& in);
    std::string with;
    std::string getWhat();
    std::istream* in = nullptr;
    std::ostream* out = nullptr;
};

#endif //TR_H
