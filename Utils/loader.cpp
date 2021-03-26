#include "loader.h"
#include "Xml/xmlreader.h"
#include "Utils/msp.h"
#include <QString>
#include <QDomElement>
#include <QFile>
#include <QDebug>

/*! Reads the contents of a stylesheet into a string
 * \brief readStylesheet
 * \param path - file path
 * \return String
 */
QString readStylesheet(const QString& path)
{
    XMLReader r("./../FinalMsp/Config/optionconfig.xml");
    QString theme = r.findElemUnderElem(r.findElemUnderRoot("interface"), "theme").text();
    QString sheet;
    sheet = loadStylesheet(path);
    return sheet;
}

/*! Loads the contents of a qt stylesheet into a string and replaces special terms in it
 * \brief loadStylesheet
 * \param path - file path
 * \return String
 */
QString loadStylesheet(const QString& path)
{
    QFile f(path);
    f.open(QFile::ReadOnly);
    QString contents = QLatin1String(f.readAll());
    contents.replace("\r\n", "");
    contents.replace("@mainColor", getColorString(MSP::mainColor()));
    contents.replace("@sideMenuColor", getColorString(MSP::sideMenuColor()));
    contents.replace("@sideMenuHoverColor", getColorString(MSP::sideMenuHoverColor()));
    contents.replace("@sideMenuPressedColor", getColorString(MSP::sideMenuPressedColor()));
    contents.replace("@textColor", getColorString(MSP::textColor()));
    contents.replace("@featureColor", getColorString(MSP::featureColor()));
    contents.replace("@contrastColor", getColorString(MSP::contrastColor()));
    f.close();
    return contents;
}

/*! Returns a color as rgba() string
 * \brief getColorString
 * \param rgb - Struct holding the rgb values of a color
 * \return String
 */
QString getColorString(const RgbHolder& rgb)
{
    return "rgba(" + QString::number(rgb.red) + ", " + QString::number(rgb.green) + ", "
           + QString::number(rgb.blue) + ", 255)";
}
