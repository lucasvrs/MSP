#ifndef LOADER_H
#define LOADER_H

class QString;
struct RgbHolder;

extern QString readStylesheet(const QString& path);
extern QString loadStylesheet(const QString& path);
extern QString getColorString(const RgbHolder& rgb);

#endif // LOADER_H
