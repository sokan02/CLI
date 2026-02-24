//
// Created by sofija on 24/02/26.
//

#ifndef DATE_H
#define DATE_H
#include "Command.h"
#include "streamInterfaces.h"

class Date : public Command, public IOutput {
public:
    Date(const std::string& arg, const std::string& opt);
    void execute() override;
    void setOutput(std::ostream* o) override { out = o; }
private:
    std::ostream* out = nullptr;
};

#endif //DATE_H
