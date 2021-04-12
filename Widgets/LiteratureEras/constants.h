#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QList>
#include <QColor>

constexpr int TIMELINE_HEIGHT = 250;
constexpr int TIMELINE_BORDER = 2000;
constexpr int TEXT_SPACING = 100;
constexpr double MULTIPLICATOR = 1.0;
constexpr double DIVISOR = 1/MULTIPLICATOR;
constexpr int FONT_SIZE = 12;

const static QList<QString> VOWELS = {"a", "u", "o"};
const static QList<QString> REPLACE_VOWELS = {"ä", "ü", "ö"};
const static QList<QColor> COLORS = {Qt::red, Qt::cyan, Qt::green,
                                     Qt::magenta, Qt::yellow, Qt::blue,
                                     Qt::gray};

enum Language
{
    GERMAN = 0,
    ENGLISH
};

const static QList<QString> TOKEN = {"de", "eng"};

#endif // CONSTANTS_H
