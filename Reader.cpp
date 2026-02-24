//
// Created by sofija on 11/01/26.
//
#include "Reader.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;


Reader::Reader(istream* input)
 : input(input) {}

string Reader::getLine() {
    string line;
    getline(*input, line);
    return line;
}

bool Reader::isEof() {
    if (input->eof()) {
        input->clear();
        return true;
    }
    return false;
}

ConsoleReader::ConsoleReader()
 : Reader(&cin) {}

FileReader::FileReader(string path)
 : Reader(new ifstream(path)) {}

FileReader::~FileReader() {
    delete input;
}
