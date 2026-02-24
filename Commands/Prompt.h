//
// Created by sofija on 24/02/26.
//

#ifndef PROMPT_H
#define PROMPT_H
#include "Command.h"


class Prompt : public Command {
public:
    void execute() override;
    Prompt(const std::string& arg, const std::string& opt);
};

#endif //PROMPT_H
