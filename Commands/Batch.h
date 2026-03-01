//
// Created by sofija on 01/03/26.
//

#ifndef BATCH_H
#define BATCH_H
#include "Command.h"
#include "streamInterfaces.h"

class Batch : public Command, public IOutput {
public:
  Batch(const std::string &arg, const std::string &opt);
  void execute() override;
  void setOutput(std::ostream *o) override { out = o; }

private:
  std::ostream *out = nullptr;
};

#endif // BATCH_H
