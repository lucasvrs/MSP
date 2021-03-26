#include "xmlreader.h"

#include <QDomDocument>
#include <QFile>
#include <QDebug>

/*! Initializes all member variables and tries to open a xml file.
 * \brief XMLReader::XMLReader
 * \param f - QString: file name
 */
XMLReader::XMLReader(const QString& f)
{
    m_file = new QFile(f);
    m_doc = new QDomDocument;
    m_rootElement = new QDomElement;
    init();
}

/*! Tries to open a xml file.
 * \brief XMLReader::init
 */
void XMLReader::init()
{
    if(!m_file->open(QIODevice::ReadOnly))
    {
        return;
    }
    if(!m_doc->setContent(m_file))
    {
        m_file->close();
        return;
    }
    m_file->close();
    *m_rootElement = m_doc->documentElement();
}

/*! Returns all elements on the second layer of the xml tree.
 * \brief XMLReader::allElemsUnderRoot
 * \return QList<QDomElement>
 */
const QList<QDomElement>* XMLReader::allElemsUnderRoot()
{
    QList<QDomElement>* list = new QList<QDomElement>();
    QDomElement e = m_rootElement->firstChild().toElement();
    while(!e.isNull())
    {
        list->append(e);
        e = e.nextSibling().toElement();
    }
    return list;
}

/*! Returns all elements one layer beneath forwarded element
 * \brief XMLReader::allElemsUnderElem
 * \param elem - QDomElement: root element
 * \return QList<QDomElement>
 */
const QList<QDomElement>* XMLReader::allElemsUnderElem(const QDomElement& elem)
{
    QList<QDomElement>* list = new QList<QDomElement>();
    QDomElement e = elem.firstChild().toElement();
    while(!e.isNull())
    {
        list->append(e);
        e = e.nextSibling().toElement();
    }
    return list;
}

/*! Searches for an element beneath the root element
 * \brief XMLReader::findElemUnderRoot
 * \param elem - QDomElement: Element to be searched for
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderRoot(const QDomElement& elem)
{
    QDomElement* res;
    QDomElement e = m_rootElement->firstChild().toElement();
    while(!e.isNull())
    {
        if(e == elem)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}

/*! Searches via name for an element beneath the root element
 * \brief XMLReader::findElemUnderRoot
 * \param name - QString: name of the element
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderRoot(const QString& name)
{
    QDomElement* res;
    QDomElement e = m_rootElement->firstChild().toElement();
    while(!e.isNull())
    {
        if(e.tagName() == name)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}

/*! Searches via name for an element beneath the root element
 * \brief XMLReader::findElemUnderRoot
 * \param name      - QString: name of the element
 * \param attr      - atrribute of the element
 * \param attrV     - attribute value
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderRoot(const QString& name, const QString& attr, const QString &attrV)
{
    QDomElement* res;
    QDomElement e = m_rootElement->firstChild().toElement();
    while(!e.isNull())
    {
        if(e.tagName() == name && e.attribute(attr) == attrV)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}

/*! Searches via name for an element beneath an element
 * \brief XMLReader::findElemUnderElem
 * \param elem - QDomElement: root element
 * \param name - QString: name of searched element
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderElem(const QDomElement& elem, const QString& name)
{
    QDomElement* res;
    QDomElement e = elem.firstChild().toElement();
    while(!e.isNull())
    {
        if(e.tagName() == name)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}

/*! Searches for an element beneath another element
 * \brief XMLReader::findElemUnderElem
 * \param elem  - QDomElement: root element
 * \param name  - tag name to be searched for
 * \param attr  - attribute to be searched for
 * \param attrV - attributes value to be searched for
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderElem(const QDomElement& elem, const QString& name, const QString& attr, const QString& attrV)
{
    QDomElement* res;
    QDomElement e = elem.firstChild().toElement();
    while(!e.isNull())
    {
        if(e.tagName() == name && e.attribute(attr) == attrV)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}

/*! Searches for an element beneath another element
 * \brief XMLReader::findElemUnderElem
 * \param rootElem - QDomElement: root element
 * \param elem - QDomElement: Element to be searched for
 * \return QDomElement
 */
const QDomElement& XMLReader::findElemUnderElem(const QDomElement& rootElem, const QDomElement& elem)
{
    QDomElement* res;
    QDomElement e = rootElem.firstChild().toElement();
    while(!e.isNull())
    {
        if(e == elem)
        {
            res = &e;
            return *res;
        }
        e = e.nextSibling().toElement();
    }
    res = new QDomElement();
    return *res;
}
