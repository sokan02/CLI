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

            ParsedLine pl = parser->parseLine(line);
            if (pl.pipeline.empty()) continue;
            program->executeParsedLine(pl);
        }
        catch (const std::exception& e) {
            cerr << e.what() << endl;
        }
    }


    delete parser;
    delete reader;


    return 0;
}