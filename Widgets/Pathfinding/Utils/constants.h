#ifndef CONSTANTS_H
#define CONSTANTS_H

/*! Type of node
 * \brief The DelimiterType enum
 */
enum DelimiterType
{
    Start,
    Destination,
    None,
    DelimiterTypeLength
};

static const char* MODE_STRINGLIST[3] = {"Delimiter", "Obstacle", "Delete"};

constexpr short MAX_STEPS = 1000;

#endif // CONSTANTS_H
