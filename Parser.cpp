//
// Created by sofija on 11/01/26.
//
#include "Parser.h"

#include <cctype>
#include <iostream>
#include <string>
#include <vector>

// Commands
#include "Commands/Batch.h"
#include "Commands/Command.h"
#include "Commands/Date.h"
#include "Commands/Echo.h"
#include "Commands/Head.h"
#include "Commands/Prompt.h"
#include "Commands/Rm.h"
#include "Commands/Time.h"
#include "Commands/Touch.h"
#include "Commands/Tr.h"
#include "Commands/Truncate.h"
#include "Commands/Wc.h"

using namespace std;

// -------------------- LEXICAL CHECK --------------------
// Returns false and prints error with ^ markers if any invalid characters
// are found. Valid outside quotes: alphanumeric, . _ - / | < > " space tab.
// Unclosed quotes are also reported as an error.
bool Parser::lexicalCheck(const string &line) {
  bool inQuote = false;
  int quoteStart = -1;
  vector<int> bad;

  for (int i = 0; i < (int)line.size(); ++i) {
    char ch = line[i];
    if (inQuote) {
      if (ch == '"')
        inQuote = false;
    } else {
      if (ch == '"') {
        inQuote = true;
        quoteStart = i;
      } else if (!inQuote) {
        bool valid = std::isalnum(static_cast<unsigned char>(ch)) ||
                     ch == '.' || ch == '_' || ch == '-' || ch == '/' ||
                     ch == '|' || ch == '<' || ch == '>' || std::isspace(ch);
        if (!valid)
          bad.push_back(i);
      }
    }
  }

  if (inQuote)
    bad.push_back(quoteStart);

  if (bad.empty())
    return true;

  std::cerr << "Error - unexpected characters:\n";
  std::cerr << line << '\n';
  string markers(line.size(), ' ');
  for (int pos : bad)
    markers[pos] = '^';
  std::cerr << markers << '\n';
  return false;
}

// -------------------- TOKENIZE --------------------
// - navodnici: sve unutra se tretira kao deo tokena (razmaci ne seku token)
// - specijalni tokeni | < > su uvek posebni tokeni (osim ako su unutar
// navodnika)
// - navodnike zadržavamo u tokenu, pa kasnije možeš noQuotation()
vector<string> Parser::tokenize(const string &line) {
  vector<string> tokens;
  string cur;
  bool is_quotation = false;

  auto flush = [&]() {
    if (!cur.empty()) {
      tokens.push_back(cur);
      cur.clear();
    }
  };

  for (int i = 0; i < (int)line.length(); i++) {
    char ch = line[i];
    if (ch == '"') {
      is_quotation = !is_quotation;
      cur.push_back(ch);
    } else if (is_quotation) {
      cur.push_back(ch);
    } else if (ch == '|' || ch == '<') {
      flush();
      tokens.push_back(string(1, ch));
    } else if (ch == '>') {
      flush();
      if (i + 1 < (int)line.length() && line[i + 1] == '>') {
        i++;
        tokens.push_back(">>");
      } else {
        tokens.push_back(">");
      }
    } else if (std::isspace(static_cast<unsigned char>(ch))) {
      flush();
    } else {
      cur.push_back(ch);
    }
  }
  flush();
  return tokens;
}

// -------------------- BUILD SINGLE COMMAND --------------------
// tokens su npr: ["wc", "-w", "file.txt"] ili ["tr", "\"ab\"", "\"cd\""] itd.
// - cmd = tokens[0]
// - opt = prvi token koji počinje sa '-' (ako postoji)
// - arg = prvi "normalan" token posle cmd (ako postoji)
// - with = sledeći "normalan" token (koristi se za tr)
// - ako ima više od toga -> error
Command *Parser::buildCommand(const vector<string> &tokens) {
  if (tokens.empty())
    return nullptr;

  string cmd = tokens[0];
  string opt;
  string arg;
  string with;

  for (int i = 1; i < (int)tokens.size(); ++i) {
    const string &x = tokens[i];

    // Parse tr args: [argument] -"what" ["with"]
    if (cmd == "tr") {
      if (!x.empty() && x[0] == '-' && opt.empty()) {
        opt = x;
      } else if (with.empty() && !opt.empty()) {
        with = x;
      } else if (arg.empty()) {
        arg = x;
      } else {
        std::cerr << "Error - too many arguments\n";
        return nullptr;
      }
      continue;
    }

    if (!x.empty() && x[0] == '-' && opt.empty()) {
      opt = x;
    } else if (arg.empty()) {
      arg = x;
    } else {
      std::cerr << "Error - too many arguments\n";
      return nullptr;
    }
  }

  // Factory
  if (cmd == "time") {
    if (!opt.empty() || !arg.empty()) {
      std::cerr << "Error - time does not support options or arguments\n";
      return nullptr;
    }
    return new Time(arg, opt);
  }
  if (cmd == "date") {
    if (!opt.empty() || !arg.empty()) {
      std::cerr << "Error - date does not support options or arguments\n";
      return nullptr;
    }
    return new Date(arg, opt);
  }
  if (cmd == "touch") {
    if (!opt.empty()) {
      std::cerr << "Error - touch does not support options\n";
      return nullptr;
    }
    if (arg.empty()) {
      std::cerr << "Error - touch requires a filename\n";
      return nullptr;
    }
    return new Touch(arg, opt);
  }
  if (cmd == "echo") {
    if (!opt.empty()) {
      std::cerr << "Error - echo does not support options\n";
      return nullptr;
    }
    return new Echo(arg, opt);
  }
  if (cmd == "wc") {
    if (opt != "-w" && opt != "-c") {
      std::cerr << "Error - wc requires -w or -c option\n";
      return nullptr;
    }
    return new Wc(arg, opt);
  }
  if (cmd == "rm") {
    if (!opt.empty()) {
      std::cerr << "Error - rm does not support options\n";
      return nullptr;
    }
    if (arg.empty()) {
      std::cerr << "Error - rm requires a filename\n";
      return nullptr;
    }
    return new Rm(arg, opt);
  }
  if (cmd == "truncate") {
    if (!opt.empty()) {
      std::cerr << "Error - truncate does not support options\n";
      return nullptr;
    }
    if (arg.empty()) {
      std::cerr << "Error - truncate requires a filename\n";
      return nullptr;
    }
    return new Truncate(arg, opt);
  }
  if (cmd == "prompt") {
    if (!opt.empty()) {
      std::cerr << "Error - prompt does not support options\n";
      return nullptr;
    }
    if (arg.empty() || arg.front() != '"') {
      std::cerr << "Error - prompt requires a quoted argument\n";
      return nullptr;
    }
    return new Prompt(arg, opt);
  }
  if (cmd == "head") {
    if (opt.size() < 3 || opt[0] != '-' || opt[1] != 'n' ||
        !std::isdigit(static_cast<unsigned char>(opt[2]))) {
      std::cerr << "Error - head requires -nCOUNT option (e.g. -n10)\n";
      return nullptr;
    }
    return new Head(arg, opt);
  }
  if (cmd == "tr") {
    if (opt.empty()) {
      std::cerr << "Error - tr requires an option\n";
      return nullptr;
    }
    return new Tr(arg, opt, with);
  }
  if (cmd == "batch") {
    if (!opt.empty()) {
      std::cerr << "Error - batch does not support options\n";
      return nullptr;
    }
    if (arg.empty()) {
      std::cerr << "Error - batch requires a filename\n";
      return nullptr;
    }
    return new Batch(arg, opt);
  }

  std::cerr << "Unknown command: " << cmd << '\n';
  return nullptr;
}

// -------------------- PARSE WHOLE LINE --------------------
// Podržava:
// - pipeline: cmd1 ... | cmd2 ... | cmd3 ...
// - redirekcije: < file, > file (u istoj liniji)
// Pravilo:
// - < i > važe za celu liniju
// - komande su segmenti između |
// Vraća ParsedLine:
// - pipeline: vektor Command*
// - inFile/outFile: optional
ParsedLine Parser::parseLine(const string &line) {
  ParsedLine res;

  if (!lexicalCheck(line))
    return res;

  vector<string> t = tokenize(line);
  if (t.empty())
    return res;

  vector<string> currentCmdTokens;
  bool ok = true;
  bool redirectionSeen = false;

  auto cleanup = [&]() {
    for (Command *c : res.pipeline)
      delete c;
    res.pipeline.clear();
  };

  auto flushCommand = [&]() {
    if (currentCmdTokens.empty())
      return;
    Command *c = buildCommand(currentCmdTokens);
    currentCmdTokens.clear();
    if (!c) {
      cleanup();
      ok = false;
      return;
    }
    res.pipeline.push_back(c);
  };

  for (size_t i = 0; i < t.size(); ++i) {
    const string &tok = t[i];

    if (tok == "|") {
      redirectionSeen = false;
      flushCommand();
      if (!ok)
        return {};
      continue;
    }

    if (tok == "<") {
      if (i + 1 >= t.size()) {
        std::cerr << "Error - missing input file after <\n";
        cleanup();
        return {};
      }
      flushCommand();
      if (!ok)
        return {};
      res.inFile = t[++i];
      redirectionSeen = true;
      continue;
    }

    if (tok == ">") {
      if (i + 1 >= t.size()) {
        std::cerr << "Error - missing output file after >\n";
        cleanup();
        return {};
      }
      flushCommand();
      if (!ok)
        return {};
      res.outFile = t[++i];
      redirectionSeen = true;
      continue;
    }

    if (tok == ">>") {
      if (i + 1 >= t.size()) {
        std::cerr << "Error - missing output file after >>\n";
        cleanup();
        return {};
      }
      flushCommand();
      if (!ok)
        return {};
      res.outFile = t[++i];
      res.appendOut = true;
      redirectionSeen = true;
      continue;
    }

    if (redirectionSeen) {
      std::cerr << "Error - unexpected token after redirection: " << tok
                << '\n';
      cleanup();
      return {};
    }

    currentCmdTokens.push_back(tok);
  }

  flushCommand();
  if (!ok)
    return {};
  return res;
}