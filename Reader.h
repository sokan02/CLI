//
// Created by sofija on 11/01/26.
//

#ifndef READER_H
#define READER_H
#pragma once

#include <string>
#include <istream>
using namespace std;

class Reader {
public:
    Reader(istream* input);
    virtual ~Reader() {}

    string getLine();
    bool isEof();

protected:
    istream* input;
};

class ConsoleReader : public Reader {
public:
    ConsoleReader();
};

class FileReader : public Reader {
public:
    FileReader(string path);
    ~FileReader();
};
#endif //READER_H
