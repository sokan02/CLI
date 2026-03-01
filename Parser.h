//
// Created by sofija on 11/01/26.
//

#ifndef PARSER_H
#define PARSER_H

#include <optional>
#include <string>
#include <vector>

class Command;

struct ParsedLine {
  std::vector<Command *> pipeline;    // komande u pipeline-u, redom
  std::optional<std::string> inFile;  // nakon '<' (ako postoji)
  std::optional<std::string> outFile; // nakon '>' ili '>>' (ako postoji)
  bool appendOut = false;             // true ako je '>>' (dodaj na kraj)
};

class Parser {
public:
  // Novi parser: vraća pipeline + redirekcije
  ParsedLine parseLine(const std::string &line);

private:
  bool lexicalCheck(const std::string &line);
  std::vector<std::string> tokenize(const std::string &line);

  // Pravi jednu komandu od tokena jednog segmenta (između |)
  Command *buildCommand(const std::vector<std::string> &tokens);
};

#endif // PARSER_H