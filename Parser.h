//
// Created by sofija on 11/01/26.
//

#ifndef PARSER_H
#define PARSER_H


#include <string>
#include <vector>
using namespace std;
class Command;

class Parser {
public:
    Command* parseCommand(string line);

private:
    vector<string> tokenize(string line);
};

#endif //PARSER_H
