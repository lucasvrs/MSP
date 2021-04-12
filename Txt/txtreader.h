#ifndef TXTREADER_H
#define TXTREADER_H

#include <iostream>
#include <fstream>
#include <string>
#include <QVector>

class TXTReader
{
public:
    TXTReader();

    QVector<std::string> m_Input;
    std::string m_line;

    QVector<std::string> getInput(std::string input);

};

#endif // TXTREADER_H
