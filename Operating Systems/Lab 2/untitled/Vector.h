#ifndef UNTITLED_VECTOR_H
#define UNTITLED_VECTOR_H

#include "Number.h"


class Vector {
private:
    Number y;
    Number x;
public:
    Vector() {
        x = 0;
        y = 0;
    }

    Vector(Number _x, Number _y) {
        x = _x;
        y = _y;
    }

    Number getX() {
        return this->x;
    }

    Number getY() {
        return this->y;
    }

    Number angle();

    Number radius();

    Vector Summ(Vector a, Vector b);

    void print();

    Vector operator + (Vector V);

    static Vector zero;
    static Vector one;
};
#endif //UNTITLED_VECTOR_H
