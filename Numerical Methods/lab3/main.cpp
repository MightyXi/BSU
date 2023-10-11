#include <iostream>
#include <vector>
#include <stdlib.h>
#include <ctime>
#include <cmath>
#include <chrono>
#include <string>

int size = 1000;
int m = 14;
int k = 2;

std::vector<float> generateVectorB() {
    std::vector<float>  ans(size+1, 0);
    for (size_t i = 0; i < size+1; ++i) {
        ans[i] =i+1;
    }
    return ans;
}

std::vector<float> multiply(std::vector<std::vector<float>> A, std::vector<float> x) {
    std::vector<float> ans(size+1, 0);
    {
        for (int i = 0; i < size+1; i++) {
            float sum = 0;
            for (int j = 0; j < size+1; j++) {
                sum += A[i][j] * x[j];
            }
            ans[i] = sum;
        }
    }
    return ans;
}

std::vector<std::vector<float>> generateMatrix(int size) {
    std::vector<std::vector<float>> A(size+1, std::vector<float>(size+1, 0));
    A[0][0] = m;
    A[0][1] = -(m-1);

    for (int i = 1; i < size; i++){
        A[i][i-1] = -k;
        A[i][i] = m + k + (i - 1);
        A[i][i+1] = -(m + (i-1));
    }

    A[size][size-1] = -k;
    A[size][size] = m + k + size - 1;
        
    return A;
}

std::vector<float> ForwardRunThrough(std::vector<std::vector<float>> &A, std::vector<float>& f)
{
    std::vector<float> z(size+1, 0);
    std::vector<float> b(size+1, 0);

    z[0] = A[0][1] / A[0][0];
    b[0] = f[0] / A[0][0];

    for (int i = 0; i < size-1; i++)
    {
        z[i+1] = b[i]/(A[i][i] - z[i]*A[i][i-1]);
        b[i+1] = (f[i] + A[i][i-1] * b[i])/(A[i][i] - z[i]*A[i][i-1]);
    }
    b[size] = (f[size-1] + A[size-1][size-2] * b[size-1])/(A[size-1][size-1] - z[size-1]*A[size-1][size-2]);


    std::vector<float> ans(size, 0);
    ans[size] = b[size];

    for (int i = size-1; i >= 0; i--)
    {
        ans[i] = z[i] + ans[i+1] + b[i+1];
    }
    
    return ans;
}



void print5(std::vector<float> vector) {
    for (int i = 0; i < 5; i++)
        std::cout << vector[i] << " ";
    std::cout << "\n";
}


float relativeError(std::vector<float> x_, std::vector<float> x) {
    float max_1 = -1;
    for (int i = 0; i < size+1; i++) {
        max_1 = std::max(std::abs(x_[i] - x[i]), max_1);
    }
    float max_2 = -1;
    for (int i = 0; i < size+1; i++) {
        max_2 = std::max(std::abs(x[i]), max_2);
    }
    return max_1 / max_2;
}


int main()
{
    std::vector<std::vector<float>> matrix = generateMatrix(size);
    std::vector<float> x = generateVectorB();
    std::vector<float> b = multiply(matrix, x);
    auto start = std::chrono::steady_clock::now();
    std::vector<float> ans = ForwardRunThrough(matrix, b);
    auto end = std::chrono::steady_clock::now();
    const int time1 = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();


    std::cout << "5 cordinats of solution ";
    print5(ans);
    std::cout << "otnositelnaya pogreshnost " << relativeError(ans, x) << "\n";
    std::cout << "Runtime " << time1 << " ms\n";
    return 0;
}
