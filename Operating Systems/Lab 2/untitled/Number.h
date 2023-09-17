#ifndef UNTITLED_NUMBER_H
#define UNTITLED_NUMBER_H
class Number
{
private:
    double number;
public:
    Number() {
        number = 0;
    }

    Number(double _number) {
        number = _number;
    }
    double getNumber();

    void setNumber(double a);

    static Number Add(Number a, Number b);

    static Number Subtract(Number a, Number b);

    static Number Multiply(Number a, Number b);

    static Number Divide(Number a, Number b);

    static Number Sqrt(Number a);

    static Number Pow(Number a, double b);

    static Number Arctan(Number a);


    Number& operator = (double num) {
        number = num;
        return *this;
    }

    static Number zero;
    static Number one;

    void print();
};

#endif //UNTITLED_NUMBER_H
