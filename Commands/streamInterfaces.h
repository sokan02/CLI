//
// Created by sofija on 24/02/26.
//

#ifndef STREAMINTERFACES_H
#define STREAMINTERFACES_H
#include <iostream>

struct IInput {
  virtual void setInput(std::istream *in) = 0;
  virtual ~IInput() = default;
};

struct IOutput {
  virtual void setOutput(std::ostream *out) = 0;
  virtual ~IOutput() = default;
};

#endif // STREAMINTERFACES_H
