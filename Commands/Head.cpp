//
// Created by sofija on 24/02/26.
//

#include "Head.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>

Head::Head(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

int Head::getNoRows() {
  int rows = 0;
  for (char c : m_opt) {
    if (std::isdigit(c)) {
      rows = rows * 10 + c - '0';
    }
  }
  return rows;
}

std::string Head::getLines(int noLines, std::istream &is) {
  std::string newText;
  int cnt = 0;
  char c;
  while (cnt < noLines && is.get(c)) {
    newText += c;
    if (c == '\n')
      cnt++;
  }
  return newText;
}

void Head::execute() {
  std::string text;
  (*out) << getLines(getNoRows(), *in) << std::flush;
}