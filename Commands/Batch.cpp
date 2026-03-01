//
// Created by sofija on 01/03/26.
//

#include "Batch.h"
#include "../Parser.h"
#include "../Program.h"
#include <fstream>
#include <iostream>
#include <string>

Batch::Batch(const std::string &arg, const std::string &opt)
    : Command(arg, opt), out(&std::cout) {}

void Batch::execute() {
  std::ifstream file(m_arg);
  if (!file.is_open()) {
    std::cerr << "Error - cannot open file: " << m_arg << '\n';
    return;
  }

  Parser parser;
  Program *program = Program::getInstance();

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty())
      continue;
    try {
      ParsedLine pl = parser.parseLine(line);
      if (pl.pipeline.empty())
        continue;
      program->executeParsedLine(pl, out);
    } catch (const std::exception &e) {
      std::cerr << e.what() << '\n';
    }
  }
}
