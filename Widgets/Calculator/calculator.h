#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QList>

struct Calculator
{
    using Mptr = double (Calculator::*)(double, double);
    const Mptr m_functions[6] = {&Calculator::add, &Calculator::subtract, &Calculator::multiply,
                                 &Calculator::divide, &Calculator::pow, &Calculator::modulo};
    enum Operator
    {
        Addition,
        Subtraction,
        Multiplication,
        Division,
        Power,
        Modulo,
        Operators
    };
    const QList<QString> opStr = {"+", "-", "*", "/", "^", "mod"};
    const QList<Operator> ops = {Addition, Subtraction, Multiplication, Division, Power, Modulo};
    const QList<int> prio = {1, 1, 2, 2, 3, 3};
    double action(Operator op, double a, double b);
    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);
    double pow(double a, double fac);
    double modulo(double a, double fac);
};

#endif // CALCULATOR_H
