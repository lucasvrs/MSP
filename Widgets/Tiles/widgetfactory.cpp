/*******************************************************************************************************
 *>----------------------------------------------------------------------------------------------------<
 * Written by Luca Sievers
 *>----------------------------------------------------------------------------------------------------<
 ******************************************************************************************************/

#include "widgetfactory.h"
#include "Widgets/Calculator/calculatorwidget.h"
#include "Widgets/Converter/converterwidget.h"
#include "Widgets/Pathfinding/pathfindingwidget.h"
#include "Widgets/ReactionTest/reaction.h"
#include "Widgets/FormulaCollection/formelsammlung.h"
#include "Widgets/MatrixCalculator/matrixrechner.h"
#include "Widgets/VocabularyTrainer/vokabeltrainer.h"
#include "Widgets/ArithmeticGame/kopfrechnenstart.h"
#include "Widgets/LiteratureEras/erawidget.h"
#include "Widgets/ColorPicker/colorpickerwidget.h"
#include "Widgets/Raytracing/raytracingwidget.h"

WidgetFactory::WidgetFactory()
{
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new CalculatorWidget(), "calculator"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new ConverterWidget(), "converter"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new PathfindingWidget(), "pathfinding"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new Reaction(), "reaction"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new Formelsammlung(), "formulacollection"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new Matrixrechner(), "matrixcalculator"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new Vokabeltrainer(), "vocabularytrainer"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new KopfrechnenStart(), "mentalarithmetic"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new EraWidget(), "literatureeras"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new ColorPickerWidget(), "colorpicker"));
    m_widgetNameMap.insert(std::pair<QWidget*, QString>(new RaytracingWidget(), "raytracing"));
}

QWidget* WidgetFactory::findWidget(const QString& name)
{
    for(auto pair : m_widgetNameMap)
    {
        if(pair.second == name) return pair.first;
    }
    return nullptr;
}
