#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QList>
#include <QDomDocument>
#include <QString>
#include <QFile>
#include <QDomAttr>
#include <QDebug>

/*! Converts tag names into usable strings
 * \brief The XMLTagNameConverter struct
 */
struct XMLTagNameConverter
{
    QString tagName;
    XMLTagNameConverter() : tagName("") {}
    XMLTagNameConverter(const QString& name) { tagName = name; }
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
            if(tagName[i] == " ")
            {
                tagName = tagName.replace(i, 1, "_");
            }
        }
        return tagName;
    }
    void setCurName(const QString& name) { tagName = name; }
};

class XMLWriter
{
public:
    XMLWriter(const QString& filename, const QString& rootTagName)
    {
        m_file = new QFile(filename);
        m_doc = new QDomDocument;
        m_rootElement = new QDomElement;
        init(rootTagName);
    }
    XMLWriter(const QString& f)
    {
        m_nameConverter = false;
        m_file = new QFile(f);
        m_doc = new QDomDocument;
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
        m_rootElement = new QDomElement(m_doc->documentElement());
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param elem - element to be append
     */
    void appendElement(QDomElement& elem)
    {
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName - tag name of element to be append on first layer of the document
     */
    void appendElement(const QString& tagName)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of element
     * \param text      - text of element
     */
    void appendElement(const QString& tagName, const QString& text)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        m_doc->appendChild(elem);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& attr, int value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& attr, float value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& attr, double value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& attr, const QString& value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& text, const QString& attr, int value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& text, const QString& attr, float value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& text, const QString& attr, double value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document on first layer
     * \brief appendElement
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElement(const QString& tagName, const QString& text, const QString& attr, const QString& value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        m_doc->appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node  - node to append on
     * \param child - node to be appended
     */
    void appendElementUnderElement(QDomNode& node, QDomNode& child)
    {
        node.appendChild(child);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param text      - text of element
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& text)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& attr, int value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& attr, float value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& attr, double value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& attr, const QString& value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& text, const QString& attr, int value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& text, const QString& attr, float value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& text, const QString& attr, double value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        node.appendChild(elem);
    }
    /*! Appends element to document under element
     * \brief appendElementUnderElement
     * \param node      - node to append on
     * \param tagName   - tag name of the element
     * \param text      - text of element
     * \param attr      - attribute of the element
     * \param value     - attributes value
     */
    void appendElementUnderElement(QDomNode& node, const QString& tagName, const QString& text, const QString& attr, const QString& value)
    {
        QDomElement elem = m_doc->createElement(createUniqueTagName(tagName));
        elem.setAttribute(attr, value);
        QDomText tElem = m_doc->createTextNode(text);
        elem.appendChild(tElem);
        node.appendChild(elem);
    }
    /*! Creates new element on first layer
     * \brief createElement
     * \param tagName - tag name of the element
     * \return QDomElement
     */
    QDomElement createElement(const QString& tagName)
    {
        return m_doc->createElement(tagName);
    }
    QDomElement getElement(const QString& tagName, const QString& attr, int value)
    {
        QDomNodeList list = m_doc->elementsByTagName(tagName);
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).toElement().attribute(attr).toInt() == value)
            {
                return list.at(i).toElement();
            }
        }
        return QDomElement();
    }
    QDomElement getTileElement(const QDomElement& parent, const QString& tagName, const QString& text, const QString& attr, int value)
    {
        QDomNodeList list = m_doc->elementsByTagName(tagName);
        for(int i = 0; i < list.size(); i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.attribute(attr).toInt() == value && e.parentNode().parentNode() == parent && e.text() == text)
            {
                return e;
            }
        }
        return QDomElement();
    }
    QDomElement getElementUnderRoot(const QString& name, const QString& attr, int attrV)
    {
        QDomElement e = m_rootElement->firstChild().toElement();
        while(!e.isNull())
        {
            if(e.tagName() == name && e.attribute(attr).toInt() == attrV)
            {
                return e;
            }
            e = e.nextSibling().toElement();
        }
        return QDomElement();
    }
    QDomElement getElementUnderElement(const QDomElement& e, const QString& tagName)
    {
        QDomNodeList list = e.childNodes();
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).toElement().tagName() == tagName)
            {
                return list.at(i).toElement();
            }
        }
        return QDomElement();
    }
    /*! Returns element having passed tag name and id value
     * \brief getElementByAttribute
     * \param tagName   - tag name of the element
     * \param value     - value of id
     * \return QDomElement
     */
    QDomNode getElementByAttribute(const QString& tagName, const QString& value)
    {
        QDomNodeList list = m_doc->elementsByTagName(tagName);
        for(int i = 0; i < list.size(); i++)
        {
            if(list.at(i).toElement().attribute("id") == value)
            {
                return list.at(i);
            }
        }
        return QDomNode();
    }
    /*! Returns first element having passed tag name
     * \brief getElementByTagName
     * \param tagName - tag name of the element
     * \return QDomElement
     */
    QDomNode getElementByTagName(const QString& tagName)
    {
        QDomNodeList list = m_doc->elementsByTagName(tagName);
        QDomNode node = list.at(0);
        return node;
    }
    /*! Return node having passed year element and month element as parent
     * \brief getElementPerDate
     * \param year  - element of second parent
     * \param month - element of first parent
     * \return QDomNode
     */
    QDomNode getElementPerDate(const QDomElement& year, const QDomElement& month)
    {
        QDomNodeList list = m_doc->elementsByTagName(month.tagName());
        for(int i = 0; i < list.size(); i++)
        {
            QDomNode node = list.at(i);
            if(node.toElement().attribute("id") == month.attribute("id"))
            {
                if(node.parentNode().toElement().attribute("id") == year.attribute("id"))
                {
                    return node;
                }
            }
        }
        return QDomNode();
    }
    /*! Return node having passed day element, month element and day element as parent
     * \brief getElementPerDate
     * \param year  - element of third parent
     * \param month - element of second parent
     * \param day   - element of first parent
     * \return QDomNode
     */
    QDomNode getElementPerDate(const QDomElement& year, const QDomElement& month, const QDomElement& day)
    {
        QDomNodeList list = m_doc->elementsByTagName(day.tagName());
        for(int i = 0; i < list.size(); i++)
        {
            QDomNode node = list.at(i);
            if(node.toElement().attribute("id") == day.attribute("id"))
            {
                if(node.parentNode().toElement().attribute("id") == month.attribute("id"))
                {
                    if(node.parentNode().parentNode().toElement().attribute("id") == year.attribute("id"))
                    {
                        return node;
                    }
                }
            }
        }
        return QDomNode();
    }
    void removeElement(const QString& attribute, const QString& tagname, const QString& parent)
    {
        QDomNodeList localChildNodes = m_doc->childNodes();
        QDomNodeList localChildNodes1;
        for(int i = 0; i < localChildNodes.length(); i++)
        {
           if(localChildNodes.at(i).nodeName() == parent)
           {
               localChildNodes1 = localChildNodes.at(i).childNodes();
           }
        }
        for(int i = 0; i < localChildNodes1.length(); i++)
        {
           if(localChildNodes1.at(i).nodeName() == tagname)
           {
               localChildNodes = localChildNodes1.at(i).childNodes();
           }
        }
        for(int i = 0; i < localChildNodes.length(); i++)
        {
          QDomNode node = localChildNodes.at(i);

          if(node.toElement().attribute("name") == attribute)
          {
             node.parentNode().removeChild(node);
          }
        }
        saveXML();
    }
    void removeElement(const QDomNode& e)
    {
        e.parentNode().removeChild(e);
    };
    /*! Removes first element with the corrosponding tagname, attribute and value
     * \brief removeElement
     * \param name  - tag name
     * \param attr  - attribute name
     * \param value - attribute value
     * \return Returns if an element got removed
     */
    bool removeElement(const QString& name, const QString& attr, const int value)
    {
        return (!crawlNodeList(m_doc->childNodes(), name, attr, value).isNull());
    }
    /*! Crawls through all nodes of a list including all their children
     * \brief crawlNodeList
     * \param list  - list of nodes
     * \param name  - tag name searched for
     * \param attr  - attribute name searched for
     * \param value - attribute value searched for
     * \return Returns the element that got removed. If no fitting node was found, the function returns an null element.
     */
    QDomElement crawlNodeList(const QDomNodeList& list, const QString& name, const QString& attr, const int value)
    {
        for(int i = 0; i < list.size(); i++)
        {
            QDomElement e = list.at(i).toElement();
            if(e.tagName() == name && e.attributes().contains(attr))
            {
                if(e.attribute(attr).toInt() == value)
                {
                    e.parentNode().removeChild(e);
                    return e;
                }
            }
            if(!e.childNodes().isEmpty())
            {
                QDomElement cE = crawlNodeList(e.childNodes(), name, attr, value);
                if(!cE.isNull())
                {
                    cE.parentNode().removeChild(cE);
                    return cE;
                }
            }
        }
        return QDomElement();
    }
    /*! Saves document to xml
     * \brief saveXML
     */
    void saveXML()
    {
        if(!m_file->open(QIODevice::WriteOnly | QIODevice::Text))
        {
            return;
        }
        QTextStream stream( m_file );
        stream << m_doc->toString();
        m_file->close();
    }
    QDomElement* getRootElement() const
    {
        return m_rootElement;
    }

private:
    bool m_nameConverter = true;
    QFile* m_file;
    QDomDocument* m_doc;
    QDomElement* m_rootElement;
    /*! Initializes document with root element
     * \brief init
     * \param rootTagName - tag name of root element
     */
    void init(const QString& rootTagName)
    {
        *m_rootElement = m_doc->createElement(rootTagName);
        m_doc->appendChild(*m_rootElement);
    }
    /*! Returns wether the searched element is existend
     * \brief find
     * \param tagName - tag name of the element
     * \return bool
     */
    bool find(const QString& tagName)
    {
        if(m_doc->elementsByTagName(tagName).size() == 0)
        {
            return false;
        }
        return true;
    }
    /*! Creates a unique tag name for an element
     * \brief createUniqueTagName
     * \param tagName - tag name of the element
     * \return QString
     */
    const QString createUniqueTagName(const QString& tagName)
    {
        if(find(tagName) && m_nameConverter)
        {
            QString newTagName;
            int duplicate = 2;
            while(true)
            {
                newTagName = tagName;
                newTagName += QString::number(duplicate);
                if(!find(newTagName))
                {
                    return newTagName;
                }
                duplicate++;
            }
        }
        return tagName;
    }

};

#endif // XMLWRITER_H
