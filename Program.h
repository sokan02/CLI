//
// Created by sofija on 13/01/26.
//

#ifndef PROGRAM_H
#define PROGRAM_H

#include "Commands/Command.h"
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
using namespace std;

struct ParsedLine; // iz Parser.h

class Program {
public:
  static Program *getInstance();
  ~Program();
  void add(Command *cmd);

  void executeNext();
  bool hasNext();

  string getArgument();
  void setArgument(string arg);

  void wireSingle(Command *cmd);
  void executeParsedLine(ParsedLine &pl, std::ostream *defaultOut = &std::cout);

protected:
  Program();

private:
  list<Command *> commands;
  list<Command *>::iterator it;

  string argument;

  std::istringstream textIn;
  std::ifstream fileIn;
};

#endif // PROGRAM_H
