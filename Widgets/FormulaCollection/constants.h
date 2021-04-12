#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QList>
#include <QColor>

const static QList<QString> VOWELS = {"a", "u", "o"};
const static QList<QString> REPLACE_VOWELS = {"ä", "ü", "ö"};
const static QList<QColor> COLORS = {Qt::red, Qt::cyan, Qt::green,
                                     Qt::magenta, Qt::yellow, Qt::blue,
                                     Qt::gray};
const static QList<QString> MONTHS = {"January", "February", "March", "April", "May",
                                      "June", "July", "August", "September", "October",
                                      "November", "December"};

enum Language
{
    GERMAN = 0,
    ENGLISH
};

const static QList<QString> TOKEN = {"de", "eng"};

#endif // CONSTANTS_H
