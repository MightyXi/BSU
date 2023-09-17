g++ -c -fpic -o Number/Number.o Number/Number.cpp
ar rvs Number/libNumber.a Number/Number.o

g++ -c -INumber -fpic -o Vector/Vector.o Vector/Vector.cpp
g++ -shared -o Vector/libVector.so Number/libNumber.a Vector/Vector.o

g++ -c -INumber -IVector -o Main/Main.o Main/Main.cpp
g++ -o Main/Main Main/Main.o Vector/libVector.so Number/libNumber.a

./Main/Main
