#include "txtreader.h"

/**
 * @brief Konstruktor
 */
TXTReader::TXTReader()
{
}

/*!
 * \brief reads a Textfile
 * \param file std::string filepath
 * \return string vextor with read lines
 */
QVector<std::string> TXTReader::getInput(std::string file)
{
    std::ifstream input(file);
   while(std::getline(input, m_line))
   {
       m_Input.append(m_line);
   }
  return m_Input;
}


