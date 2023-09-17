#include "Number.h"
#include "cmath"
#include <iostream>

double Number::getNumber() {
    return number;
}

void Number::setNumber(double a) {
    number = a;
}

Number Number::Add(Number a, Number b)
{
    return a.number + b.number;
}

Number Number::Subtract(Number a, Number b)
{
    return a.number - b.number;
}

Number Number::Multiply(Number a, Number b)
{
    return a.number * b.number;
}

Number Number::Divide(Number a, Number b)
{
    return a.number / b.number;
}

Number Number::Sqrt(Number a) {
    return sqrt(a.number);
}

Number Number::Pow(Number a, double b) {
    return pow(a.number, b);
}

Number Number::Arctan(Number a) {
    return atan(a.number);
}

Number Number::zero = 0;
Number Number::one = 1;

void Number::print() {
    std::cout << number;
}