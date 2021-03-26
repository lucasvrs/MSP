#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QList>
#include <QColor>

const static QList<QString> VOWELS = {"a", "u", "o"};
const static QList<QString> REPLACE_VOWELS = {"ä", "ü", "ö"};

/*! Containing all used languages
 * \brief The Language enum
 */
enum Language
{
    GERMAN = 0,
    ENGLISH
};

const static QList<QString> TOKEN = {"de", "eng"};

#endif // CONSTANTS_H
