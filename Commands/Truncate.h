//
// Created by sofija on 24/02/26.
//

#ifndef TRUNCATE_H
#define TRUNCATE_H
#include "Command.h"

class Truncate : public Command {
public:
    Truncate(const std::string& arg, const std::string& opt = "");
    void execute() override;
};

#endif //TRUNCATE_H
