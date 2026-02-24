#ifndef WC_H
#define WC_H

#include "Command.h"
#include "streamInterfaces.h"
#include <iostream>
#include <istream>
#include <ostream>

class Wc : public Command, public IInput, public IOutput {
    std::istream* in = &std::cin;
    std::ostream* out = &std::cout;

public:
    Wc(const std::string& arg, const std::string& opt);

    void setInput(std::istream* i) override { in = i; }
    void setOutput(std::ostream* o) override { out = o; }

    void execute() override;

private:
    static int countWordsFromStream(std::istream& is);
    static int countCharsFromStream(std::istream& is);
};

#endif