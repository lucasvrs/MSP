#ifndef TXTWRITER_H
#define TXTWRITER_H

#include <iostream>
#include <fstream>
#include <string>
#include <ios>


class TXTWriter
{
public:
    TXTWriter();

    void writeInFileAppend(std::string file, std::string input);
    void writeInFile(std::string filename, std::string input);


};

#endif // TXTWRITER_H
