#include "Vector.h"
#include "Number.h"
#include <iostream>

Number Vector::angle() {
    return Number::Sqrt(Number::Add(Number::Pow(x, 2), Number::Pow(y, 2)));
}

Number  Vector::radius() {
    return Number::Arctan(Number::Divide(y, x));
}


Vector Vector::operator + (Vector V) {
    return Vector(Number::Add(this->x, V.x), Number::Add(this->y, V.y));
}
void Vector::print() {

    std::cout << "(";
    x.print();
    std::cout << ", ";
    y.print();
    std::cout << ")";
}

Vector Vector::zero(0, 0);
Vector Vector::one(1, 1);