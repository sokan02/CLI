//
// Created by sofija on 24/02/26.
//

#include "Echo.h"
#include <iostream>

Echo::Echo(const std::string &arg, const std::string &opt)
    : Command(arg, opt) {}

std::string Echo::getText(std::istream &is) {
  std::string text;

  char c;
  while (is.get(c)) {
    text += c;
  }
  if (is.eof()) {
    is.clear();
    if (&is == &std::cin)
      clearerr(stdin);
  }

  // This is to fix empty newline.
  if (text.ends_with("\n"))
    text.pop_back();

  return text;
}

void Echo::execute() { (*out) << getText(*in) << std::flush; }