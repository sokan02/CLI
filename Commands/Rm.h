//
// Created by sofija on 24/02/26.
//

#ifndef RM_H
#define RM_H
#include "Command.h"

class Rm : public Command {
public:
    Rm(const std::string& arg, const std::string& opt = "");
    void execute() override;
};

#endif //RM_H
