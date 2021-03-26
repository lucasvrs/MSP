#include "widgetfactory.h"
#include "Widgets/Calculator/calculatorwidget.h"

WidgetFactory::WidgetFactory()
{
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new CalculatorWidget(), "calculator"));
}

QWidget* WidgetFactory::findWidget(const QString& name)
{
    for(auto pair : m_widgetNameMap)
    {
        if(pair.second == name) return pair.first;
    }
    return nullptr;
}
