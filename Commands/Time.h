//
// Created by sofija on 24/02/26.
//

#ifndef TIME_H
#define TIME_H
#include "Command.h"
#include "streamInterfaces.h"

class Time : public Command, public IOutput {
public:
    void execute() override;
    Time(const std::string& arg, const std::string& opt);
    void setOutput(std::ostream* o) override { out = o; }
private:
    std::ostream* out = nullptr;
};


#endif //TIME_H
