//
// Created by sofija on 27/05/25.
//
#include "Command.h"
#include <cerrno>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <ostream>

Command::Command(const std::string &arg, const std::string &opt)
    : m_arg(arg), m_opt(opt) {}

bool Command::isFile() {
  int cnt = 0;
  for (char c : m_arg) {
    if (c == '"') {
      cnt++;
    }
  }
  if (cnt == 0)
    return true;
  if (cnt % 2 == 0)
    return false;
  return true;
}

std::string Command::noQuotation(std::string text) {
  std::string newText = "";
  for (char c : text) {
    if (c != '"') {
      newText.push_back(c);
    }
  }
  return newText;
}

std::string Command::readConsole() {
  std::string newText = "";
  std::string line;
  while (getline(std::cin, line)) {
    newText += line;
    newText += "\n";
    std::cin.clear();
  }

  if (std::cin.eof()) {
    std::cin.clear();
    clearerr(stdin);
  }

  return newText;
}

std::string Command::readFile() {

  std::ifstream file(m_arg);

  if (!file.is_open()) {
    std::cout << strerror(errno) << std::flush;
    return "";
  }

  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());

  return content;
}