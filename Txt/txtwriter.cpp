#include "txtwriter.h"

/*!
 * \brief Konstruktor
 */
TXTWriter::TXTWriter()
{

}

/*!
 * \brief appends a Line to an existing textfile
 * \param filename std::string filepath
 * \param input writing line
 */
void TXTWriter::writeInFileAppend(std::string filename, std::string input)
{
    std::ofstream file;
    file.open(filename, std::ios_base::app);
    file << input;
    file.close();

}

/*!
 * \brief overwrites textfile
 * \param filename std::string filepath
 * \param input writing line
 */
void TXTWriter::writeInFile(std::string filename, std::string input)
{
    std::ofstream file;
    file.open(filename);
    file << input;
    file.close();

}


