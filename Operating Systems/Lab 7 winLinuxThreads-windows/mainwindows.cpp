include <iostream>
#include "windows.h"
#include <vector>
#include <chrono>

int** new_matrix(int n) {
    int** matrix = new int*[n];
    for (int i = 0; i < n; ++i) {
        matrix[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] = rand() % 10;
        }
    }
    return matrix;
}

void simple_mult(int** a, int** b, int** c, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            c[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

void blocksMult(int** a, int** b, int** c, int n, int block, int I, int J) {
    for (int i = I; i < std::min(n, I + block); ++i) {
        for (int j = J; j < std::min(n, J + block); ++j) {
            c[i][j] = 0;
            for (int k = 0; k < n; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

struct Params {
    int** A;
    int** B;
    int** C;
    int n;
    int blockSize;
    int upperLeftI;
    int upperLeftJ;

    Params(int** A,int** B, int** C, int n, int blockSize, int upperLeftI, int upperLeftJ) : A(A), B(B), C(C) {
        this->n = n;
        this->blockSize = blockSize;
        this->upperLeftI = upperLeftI;
        this->upperLeftJ = upperLeftJ;
    }
};

int thread_mult(int** a, int** b, int** c, int n, int block) {
    std::vector<HANDLE> threads;
    for (int I = 0; I < n; I += block) {
        for (int J = 0; J < n; J += block) {
            Params params(a, b, c, n, block, I, J);
            threads.emplace_back(CreateThread(nullptr, 0,
                                              reinterpret_cast<LPTHREAD_START_ROUTINE>(&blocksMult), &params, 0, nullptr));
        }
    }
    auto* thrArr = new HANDLE[threads.size()];
    for (int i = 0; i < threads.size(); ++i) {
        thrArr[i] = threads[i];
    }
    return threads.size();
}

void deleteMatrix(int** matrix) {
    delete[] matrix[0];
    delete[] matrix;
}

void single_thread_mult(int** a, int** b, int** c, int n, int block) {
    for (int I = 0; I < n; I += block) {
        for (int J = 0; J < n; J += block) {
            blocksMult(a, b, c, n, block, I, J);
        }
    }
}

double simpleMult_experement(int n){
    int** a = new_matrix(n);
    int** b = new_matrix(n);
    int** c = new_matrix(n);
    auto start = std::chrono::steady_clock::now();
    simple_mult(a, b, c, n);
    auto end = std::chrono::steady_clock::now();
    std::cout << "simple multiplication result: " <<
    std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "\n";
    deleteMatrix(a);
    deleteMatrix(b);
    deleteMatrix(c);
    }

    double threadMult_experement(int n){
        int** a = new_matrix(n);
        int** b = new_matrix(n);
        int** c = new_matrix(n);
        for (int i = 1; i <= n; i++) {
            auto start = std::chrono::steady_clock::now();
            int thread = thread_mult(a, b, c, n, i);
            auto end = std::chrono::steady_clock::now();
            auto start2 = std::chrono::steady_clock::now();
            single_thread_mult(a, b, c, n, i);
            auto end2 = std::chrono::steady_clock::now();
            std::cout << "Size of block = " << i << ", thread amount = " << thread << ", duration = " <<
                      std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
                      << ", single thread duration = " <<
                      std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2).count() << '\n';
        }
        deleteMatrix(a);
        deleteMatrix(b);
        deleteMatrix(c);
}

int main() {
    simpleMult_experement(50);
    threadMult_experement(50);
std::cout << "\n" << "\n";
    simpleMult_experement(100);
    threadMult_experement(100);
}
