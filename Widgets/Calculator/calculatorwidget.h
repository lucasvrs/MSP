#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>

class QLineEdit;
class QPushButton;
struct Calculator;

class CalculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWidget(QWidget *parent = nullptr);

private:
    double calc(const QString& o, double a, double b);
    QList<QPushButton*> m_actions;
    QLineEdit* m_edit;
    Calculator* m_calc;

signals:
    void newResult(double res);

private slots:
    void addNumber(const QString& n);
    void addOperator(const QString& o);
    void calcResult();
};

#endif // CALCULATORWIDGET_H
