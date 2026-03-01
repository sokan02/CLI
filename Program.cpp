//
// Created by sofija on 13/01/26.
//
#include "Program.h"
#include "Commands/streamInterfaces.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>

static std::string noQuotation(const std::string &text) {
  std::string newText = "";
  for (char c : text) {
    if (c != '"') {
      newText.push_back(c);
    }
  }
  return newText;
}

static bool isFile(std::string s) {
  return !(s.size() >= 2 && s.front() == '"' && s.back() == '"');
}

Program::Program() : argument("$") {}

Program *Program::getInstance() {
  static Program instance;
  return &instance;
}

Program::~Program() {
  for (Command *cmd : commands) {
    delete cmd;
  }
}

void Program::add(Command *cmd) {
  commands.push_back(cmd);
  if (commands.size() == 1)
    it = commands.begin();
  else
    ++it;
}

void Program::executeNext() {
  wireSingle(*it);
  (*it)->execute();
}

bool Program::hasNext() { return it != commands.end(); }

string Program::getArgument() { return argument; }

void Program::setArgument(string arg) { argument = arg; }

void Program::executeParsedLine(ParsedLine &pl, std::ostream *defaultOut) {
  if (pl.pipeline.empty())
    return;

  // Local streams so nested calls (e.g. batch) don't clobber each other.
  std::ofstream localFileOut;
  std::ifstream localFileIn;
  std::istringstream localTextIn;

  auto openOut = [&]() -> std::ostream * {
    if (!pl.outFile)
      return defaultOut;
    auto mode = pl.appendOut ? (std::ios::out | std::ios::app)
                             : (std::ios::out | std::ios::trunc);
    localFileOut.close();
    localFileOut.open(*pl.outFile, mode);
    if (!localFileOut.is_open())
      throw std::runtime_error("Error - cannot open output file: " +
                               *pl.outFile);
    return &localFileOut;
  };

  auto openIn = [&](Command *cmd) -> std::istream * {
    if (pl.inFile) {
      localFileIn.close();
      localFileIn.open(*pl.inFile);
      if (!localFileIn.is_open())
        throw std::runtime_error("Error - cannot open file: " + *pl.inFile);
      return &localFileIn;
    }
    const std::string &arg = cmd->m_arg;
    if (arg.empty())
      return &std::cin;
    if (isFile(arg)) {
      localFileIn.close();
      localFileIn.open(arg);
      if (!localFileIn.is_open())
        throw std::runtime_error("Error - cannot open file: " + arg);
      return &localFileIn;
    }
    localTextIn.clear();
    localTextIn.str(noQuotation(arg));
    return &localTextIn;
  };

  // ---- Semantic stream validation (Type 4) ----
  int n = pl.pipeline.size();

  for (int i = 0; i < n; ++i) {
    Command *cmd = pl.pipeline[i];
    bool hasInput  = dynamic_cast<IInput *>(cmd)  != nullptr;
    bool hasOutput = dynamic_cast<IOutput *>(cmd) != nullptr;

    // Commands without output stream can only be last.
    if (i < n - 1 && !hasOutput) {
      std::cerr << "Error - command at position " << i + 1
                << " has no output stream and cannot appear in the middle of a pipeline\n";
      for (Command *c : pl.pipeline) delete c;
      pl.pipeline.clear();
      return;
    }

    // Commands without input stream can only be first.
    if (i > 0 && !hasInput) {
      std::cerr << "Error - command at position " << i + 1
                << " has no input stream and cannot appear after the first position in a pipeline\n";
      for (Command *c : pl.pipeline) delete c;
      pl.pipeline.clear();
      return;
    }

    // A non-first piped command cannot also define its input via argument.
    if (i > 0 && hasInput && !cmd->m_arg.empty()) {
      std::cerr << "Error - command at position " << i + 1
                << " receives piped input but also defines an argument\n";
      for (Command *c : pl.pipeline) delete c;
      pl.pipeline.clear();
      return;
    }
  }

  // Argument and < redirection cannot both define input for the first command.
  Command *first = pl.pipeline[0];
  if (pl.inFile.has_value() && !first->m_arg.empty() &&
      dynamic_cast<IInput *>(first) != nullptr) {
    std::cerr << "Error - command has both an argument and < redirection\n";
    for (Command *c : pl.pipeline) delete c;
    pl.pipeline.clear();
    return;
  }

  // ---- Execute ----
  if (n == 1) {
    Command *cmd = pl.pipeline[0];
    if (IOutput *o = dynamic_cast<IOutput *>(cmd))
      o->setOutput(openOut());
    if (IInput *inp = dynamic_cast<IInput *>(cmd))
      inp->setInput(openIn(cmd));
    cmd->execute();
    if (!pl.outFile)
      *defaultOut << '\n';
    else
      localFileOut.close();
    delete cmd;
    return;
  }

  // Pipeline: run sequentially, passing data through stringstreams.
  std::stringstream buf;

  for (int i = 0; i < n; ++i) {
    Command *cmd = pl.pipeline[i];
    bool isFirst = (i == 0);
    bool isLast  = (i == n - 1);

    std::stringstream nextBuf;

    if (IOutput *o = dynamic_cast<IOutput *>(cmd))
      o->setOutput(isLast ? openOut() : static_cast<std::ostream *>(&nextBuf));

    if (IInput *inp = dynamic_cast<IInput *>(cmd))
      inp->setInput(isFirst ? openIn(cmd) : static_cast<std::istream *>(&buf));

    cmd->execute();
    delete cmd;

    if (!isLast)
      buf = std::move(nextBuf);
  }
  if (!pl.outFile)
    *defaultOut << '\n';
  else
    localFileOut.close();
}

void Program::wireSingle(Command *cmd) {
  if (!cmd)
    return;

  if (IOutput *out = dynamic_cast<IOutput *>(cmd)) {
    out->setOutput(&std::cout);
  }

  IInput *in = dynamic_cast<IInput *>(cmd);
  if (!in)
    return;

  const std::string &arg = cmd->m_arg;

  std::istream *inStream = &std::cin;

  if (arg.empty()) {
    inStream = &std::cin;
  } else if (isFile(arg)) {
    fileIn.close();
    fileIn.open(arg);

    if (!fileIn.is_open()) {
      throw std::runtime_error("Error - cannot open file: " + arg);
    }

    inStream = &fileIn;
  } else {
    textIn.clear();
    textIn.str("");
    textIn.str(noQuotation(arg));
    inStream = &textIn;
  }

  in->setInput(inStream);
}
