#include <iostream>
#include "Number.h"
#include "Vector.h"

int main()
{
    Number a, b = 3;
    a.print();
    std::cout << std::endl;
    b.print();
    std::cout << std::endl;
    Number c = Number::Add(a, b);
    c.print();
    std::cout << std::endl;
    c = Number::Pow(b, 3);
    c.print();
    std::cout << std::endl;
    c = Number::Subtract(c, 3);
    c.print();
    std::cout << std::endl;
    c = Number::Divide(c, b);
    c.print();
    std::cout << std::endl;
    b = Number::Sqrt(b);
    b.print();
    std::cout << std::endl;
    c = Number::Multiply(b, c);
    c.print();
    std::cout << std::endl;
    Number z = Number::zero;
    z.print();
    std::cout << " ";
    z = Number::one;
    z.print();
    std::cout << std::endl;
    Vector V(c, b);
    a = V.angle();
    a.print();
    std::cout << std::endl;
    a = V.radius();
    a.print();
    std::cout << std::endl;
    V.print();
    std::cout << std::endl;
    Vector V0 = Vector::zero;
    V0.print();
    std::cout << std::endl;
    Vector V1 = Vector::one;
    V0 = V + V1;
    V0.print();
}

