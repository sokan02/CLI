#include "Commands/Command.h"
#include "Program.h"
#include "Parser.h"
#include "Reader.h"
#include <iostream>
using namespace std;

int main() {

    Program* program = Program::getInstance();
    Parser* parser = new Parser();
    Reader* reader = new ConsoleReader();

    while (true) {
        try {
            cout << program->getArgument();

            string line = reader->getLine();
            if (reader->isEof())
                break;

            Command* cmd = parser->parseCommand(line);
            if (!cmd) continue;
            program->add(cmd);
            program->executeNext();
        }
        catch (const std::exception& e) {
            cerr << e.what() << endl;
        }
    }


    delete parser;
    delete reader;


    return 0;
}