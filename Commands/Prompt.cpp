//
// Created by sofija on 24/02/26.
//
#include "Prompt.h"

#include <iostream>
// #include <bits/ostream.tcc>

#include "../Program.h"

Prompt::Prompt(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

void Prompt::execute() {
  if (m_arg == "") {
    std::cout << "Error - prompt requires an argument" << std::flush;
    return;
  }
  if (m_opt != "") {
    std::cout << "Error - prompt cannot have an option" << std::flush;
    return;
  }
  if (!isFile()) {
    Program *program = Program::getInstance();
    program->setArgument(noQuotation(this->m_arg));
  } else {
    std::cout << "Error - cannot use text file as argument" << std::flush;
  }
}
