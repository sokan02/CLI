//
// Created by sofija on 24/02/26.
//

#ifndef TOUCH_H
#define TOUCH_H
#include "Command.h"

class Touch : public Command {
public:
    void execute() override;
    Touch(const std::string& arg, const std::string& opt);
};

#endif //TOUCH_H
