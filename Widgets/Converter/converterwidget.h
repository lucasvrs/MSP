#ifndef CONVERTERWIDGET_H
#define CONVERTERWIDGET_H

#include <QWidget>

class QComboBox;
class QLineEdit;

class ConverterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConverterWidget(QWidget *parent = nullptr);

private:
    QComboBox* m_unitBox;
    QComboBox* m_fromBox;
    QComboBox* m_toBox;
    QLineEdit* m_fromEdit;
    QLineEdit* m_toEdit;
    void convertTo();
    void convertFrom();

signals:

private slots:
    double convert(double sourceValue, QString sourceUnit, QString targetUnit, QString selectedUnit);
    void changeUnit();
};

#endif // CONVERTERWIDGET_H
