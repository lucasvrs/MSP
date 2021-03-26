#ifndef XMLREADER_H
#define XMLREADER_H

#include "xmlconstants.h"

#include <QList>

class QFile;
class QDomDocument;
class QDomElement;
class QString;

/*! Converts tag names into usable strings
 * \brief The XMLNameConverter struct
 */
struct XMLNameConverter
{
    QString tagName;
    Language curLang;
    XMLNameConverter() : tagName(""), curLang(ENGLISH) {}
    XMLNameConverter(const QString& name) { tagName = name; }
    const QString& curName() const { return tagName; }

    /*! Converts the current name string to a string with certain standards
     * \brief convertedName
     * \return QString
     */
    const QString& convertedName()
    {
        QString res = "";
        for(int i = 0; i < tagName.length(); i++)
        {
            if(tagName[i] == "_")
            {
                tagName = tagName.replace(i, 1, " ");
            }
            if(i < tagName.length() - 1 && curLang == GERMAN)
            {
                for(int j = 0; j < VOWELS.length(); j++)
                {
                    if(tagName[i] == VOWELS[j])
                    {
                        if(tagName[i + 1] == "e")
                        {
                            tagName = tagName.replace(i, 2, REPLACE_VOWELS[j]);
                        }
                        break;
                    }
                }
            }
        }
        return tagName;
    }
    void setCurName(const QString& name) { tagName = name; }
    void setCurLanguage(Language lan) { curLang = lan; }
};

class XMLReader
{
public:
    XMLReader(const QString& f);
    const QList<QDomElement>* allElemsUnderRoot();
    const QList<QDomElement>* allElemsUnderElem(const QDomElement& elem);
    const QDomElement& findElemUnderRoot(const QDomElement& elem);
    const QDomElement& findElemUnderRoot(const QString& name);
    const QDomElement& findElemUnderRoot(const QString& name, const QString& attr, const QString& attrV);
    const QDomElement& findElemUnderElem(const QDomElement& elem, const QString& name);
    const QDomElement& findElemUnderElem(const QDomElement& elem, const QString& name, const QString& attr, const QString& attrV);
    const QDomElement& findElemUnderElem(const QDomElement& rootElem, const QDomElement& elem);

private:
    QFile* m_file;
    QDomDocument* m_doc;
    QDomElement* m_rootElement;
    void init();
};

#endif // XMLREADER_H
