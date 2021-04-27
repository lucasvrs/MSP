#ifndef HELPWIDGETFACTORY_H
#define HELPWIDGETFACTORY_H

#include "Xml/xmlreader.h"
#include "widgetitem.h"

class HelpWidgetFactory
{
public:
    HelpWidgetFactory();
    QList<WidgetItem*> widgets();
private:
    XMLReader m_reader;


};

#endif // HELPWIDGETFACTORY_H
