#ifndef WIDGETFACTORY_H
#define WIDGETFACTORY_H

#include <map>
#include <QString>

class QWidget;

class WidgetFactory
{
public:
    WidgetFactory();
    QWidget* findWidget(const QString& name);
    std::map<QWidget*, QString> m_widgetNameMap;
};

#endif // WIDGETFACTORY_H
