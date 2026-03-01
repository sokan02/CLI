//
// Created by sofija on 24/02/26.
//

#include "Tr.h"
#include <iostream>

Tr::Tr(const std::string &arg, const std::string &opt, const std::string &with)
    : Command(arg, opt) {
  this->with = with;
}

std::string Tr::getWhat() {
  std::string what;
  for (char c : this->m_opt) {
    if (c != '-' && c != '"')
      what += c;
  }
  return what;
}

std::string Tr::getText(std::istream &is) {
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
  return text;
}

void Tr::replaceAll(std::string &str, const std::string &from,
                    const std::string &to) {
  if (from.empty())
    return;

  size_t start_pos = 0;

  while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length();
  }
}

void Tr::execute() {
  if (m_opt == "") {
    std::cerr << "Error - tr requires an option\n";
    return;
  }
  std::string with = noQuotation(this->with);
  std::string what = getWhat();
  std::string text = getText(*in);

  this->replaceAll(text, what, with);

  // This is to fix empty newline.
  if (text.ends_with("\n"))
    text.pop_back();

  (*out) << text << std::flush;
}
