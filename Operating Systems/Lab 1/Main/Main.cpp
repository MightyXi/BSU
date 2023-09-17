// Main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

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

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
