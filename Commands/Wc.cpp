#include "Wc.h"
#include <cctype>

Wc::Wc(const std::string &arg, const std::string &opt) : Command(arg, opt) {}

int Wc::countWordsFromStream(std::istream &is) {
  int cnt = 0;
  bool lastLetter = false;

  char c;
  while (is.get(c)) {
    if (std::isspace(static_cast<unsigned char>(c))) {
      lastLetter = false;
    } else {
      if (!lastLetter)
        cnt++;
      lastLetter = true;
    }
  }
  if (is.eof()) {
    is.clear();
    if (&is == &std::cin)
      clearerr(stdin);
  }
  return cnt;
}

int Wc::countCharsFromStream(std::istream &is) {
  int cnt = 0;
  char c;
  while (is.get(c)) {
    if (c != '\n')
      cnt++;
  }
  if (is.eof()) {
    is.clear();
    if (&is == &std::cin)
      clearerr(stdin);
  }
  return cnt;
}

void Wc::execute() {
  if (!in || !out)
    return;

  if (m_opt == "-w") {
    int w = countWordsFromStream(*in);
    (*out) << w << std::flush;
  } else if (m_opt == "-c") {
    int c = countCharsFromStream(*in);
    (*out) << c << std::flush;
  } else {
    std::cerr << "Error - unknown option: " << m_opt << '\n';
  }
}