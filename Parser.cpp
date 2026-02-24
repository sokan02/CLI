//
// Created by sofija on 11/01/26.
//
#include "Parser.h"

#include <iostream>
#include <bits/ostream.tcc>

#include "Commands/Command.h"
#include "Commands/Echo.h"
#include "Commands/Wc.h"
#include "Commands/Time.h"
#include "Commands/Touch.h"
#include "Commands/Date.h"
#include "Commands/Rm.h"
#include "Commands/Truncate.h"
#include "Commands/Prompt.h"
#include "Commands/Head.h"
#include "Commands/Tr.h"

using namespace std;

Command* Parser::parseCommand(string line) {
    std::vector<std::string> tokens = tokenize(line);

    std::string cmd;
    std::string opt;
    std::string args;
    std::string with;

    if (tokens.empty()) {
        return nullptr;
    }

    cmd = tokens[0];

    if (tokens.size() >= 2) {
        if (!tokens[1].empty() && tokens[1][0] == '-' && opt.empty()) {
            opt = tokens[1];
        } else if (args.empty()) {
            args = tokens[1];
        }
    }

    if (tokens.size() >= 3) {
        if (!tokens[2].empty() && tokens[2][0] == '-' && opt.empty()) {
            opt = tokens[2];
        } else if (args.empty()) {
            args = tokens[2];
        }
    }

    if (tokens.size() >= 4) {
        with = tokens[3];
    }


    if (cmd == "time"){
        return new Time(args, opt);
    }

    else if (cmd == "date") {
        return new Date(args, opt);
    }

    else if (cmd == "touch") {
        if (tokens.size() > 2) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Touch(args, opt);
    }

    else if (cmd == "echo") {
        if (tokens.size() > 3) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Echo(args, opt);
    }

    else if (cmd == "wc") {
        if (tokens.size() > 3) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Wc(args, opt);
    }

    else if (cmd == "rm") {
        if (tokens.size() > 2) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Rm(args, opt);
    }

    else if (cmd == "truncate") {
        if (tokens.size() > 2) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Truncate(args, opt);
    }

    else if (cmd == "prompt") {
        if (tokens.size() > 2) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Prompt(args, opt);
    }

    else if (cmd == "head") {
        if (tokens.size() > 3) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Head(args, opt);
    }

    else if (cmd == "tr") {
        if (tokens.size() > 4) {
            std::cout << "Error - too many arguments" << std::endl;
            return nullptr;
        }
        return new Tr(args, opt, with);
    }

    else {
        cout << "Error - unknown command: " << cmd << endl;
    }

    return nullptr;

}

bool Quote = false;

vector<string> Parser::tokenize(string line) {
    vector<string> tokens;
    string current;

    for (char c : line) {
        if (c == '"') {
            Quote = !Quote;
        }
        if (isspace(c) && !Quote) {
            if (!current.empty()) {
                tokens.push_back(current);
                current.clear();
            }
        }
        else {
            current.push_back(c);
        }
    }

    if (!current.empty()) {
        tokens.push_back(current);
    }

    return tokens;
}