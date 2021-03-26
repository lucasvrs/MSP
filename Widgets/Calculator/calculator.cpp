#include "calculator.h"

double Calculator::action(Calculator::Operator op, double a, double b)
{
    return (this->*m_functions[op])(a, b);
}

/*! Adds two numbers together
 * \brief Calculator::add
 * \param a - first number
 * \param b - second number
 * \return sum
 */
double Calculator::add(double a, double b)
{
    return a + b;
}

/*! Subtracts one number from the other
 * \brief Calculator::subtract
 * \param a - first number
 * \param b - second number
 * \return sum
 */
double Calculator::subtract(double a, double b)
{
    return a - b;
}

/*! Multiplies one number with the other
 * \brief Calculator::multiply
 * \param a - first number
 * \param b - second number
 * \return product
 */
double Calculator::multiply(double a, double b)
{
    return a * b;
}

/*! Divides one number by the other
 * \brief Calculator::divide
 * \param a - first number
 * \param b - second number
 * \return product
 */
double Calculator::divide(double a, double b)
{
    return a / b;
}

/*! Returns one number to the power of another number
 * \brief Calculator::pow
 * \param a     - base
 * \param fac   - exponent
 * \return product
 */
double Calculator::pow(double a, double fac)
{
    if(fac == 0) return 1;
    if(fac == 1) return a;
    double sum = a;
    for(int i = 1; i < (int)fac; i++)
    {
        sum *= a;
    }
    return sum;
}

/*! Returns modulo of two numbers
 * \brief Calculator::modulo
 * \param a     - number
 * \param fac   - divisor
 * \return rest
 */
double Calculator::modulo(double a, double fac)
{
    return ((int)a % (int)fac);
}
